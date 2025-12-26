### 将动态库转换为可执行文件

动态库与可执行文件之间的区别在于后者具备启动例程，这使得内核能够实际开始执行。
而在所有其他方面，特别是与静态库相比，动态库和可执行文件似乎本质相同，即均为已解析所有引用的二进制文件。

鉴于两者如此相似而差异甚微，是否可能将动态库转换为可执行文件呢？这个问题的答案是肯定的。
至少在Linux系统上完全可行。事实上，实现C运行时库的库文件（libc.so）本身就是真正可执行的。
当在shell窗口中键入其文件名调用时，你会得到如下所示的响应。

```bash
$ /lib/x86_64-linux-gnu/libc.so.6
GNU C Library (Ubuntu GLIBC 2.39-0ubuntu8.6) stable release version 2.39.
Copyright (C) 2024 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.
There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.
Compiled by GNU CC version 13.3.0.
libc ABIs: UNIQUE IFUNC ABSOLUTE
Minimum supported kernel: 3.2.0
For bug reporting instructions, please see:
<https://bugs.launchpad.net/ubuntu/+source/glibc/+bugs>.
```

接下来的自然问题是：如何实现一个库，使其同时可执行？以下方法可以实现：

- **在动态库中实现 main 函数**——即原型为 `int main(int argc, char* argv[])` 的函数。
- **将标准 `main()` 函数声明为库的入口点**。通过向链接器传递 `-e` 标志来完成此任务：
- `gcc -shared -Wl,-e,main -o <库文件名>`
- **将 `main()` 函数改为不返回的函数**。这可以通过在 `main()` 函数的最后一行插入 `_exit(0)` 调用来实现。
- **指定解释器为动态链接器**。以下代码可实现：

    ```c
    #ifdef __LP64__
    const char service_interp[] __attribute__((section(".interp"))) =
        "/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2";
    #else
    const char service_interp[] __attribute__((section(".interp"))) =
        "/lib/ld-linux.so.2";
    #endif
    ```

- **在编译库时禁用优化**（使用 `-O0` 编译器标志）。

一个简单的演示项目被创建来阐述这一想法。为了证明动态库真正具备双重特性
（即，尽管现在它可以作为可执行文件运行，但仍能作为常规动态库使用），
该演示项目不仅包含演示动态库，还包含一个可执行文件，该文件动态加载该库并调用其 `printMessage()` 函数。

下面展示了可执行共享库项目的细节：


file: executableSharedLib.c
```c
#include "sharedLibExports.h"
#include <unistd.h> // needed for the _exit() function

// Must define the interpretor to be the dynamic linker
#ifdef __LP64__
const char service_interp[] __attribute__((section(".interp"))) = "/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2"; 
#else
const char service_interp[] __attribute__((section(".interp"))) = "/lib/ld-linux.so.2"; 
#endif

void printMessage(void)
{
	printf("Running the function exported from the shared library\n");
}

int main(int argc, char* argv[])
{
	printf("Shared library %s() function\n", __FUNCTION__);
	
	// must make the entry point function to be a 'no-return' function type
	_exit(0);
}
```

file: build.sh

```bash
g++ -Wall -O0 -fPIC -I./exports/ -c src/executableSharedLib.c -o src/executableSharedLib.o
g++ -shared -Wl,-e,main ./src/executableSharedLib.o -lpthread -lm -ldl -o libexecutablesharedlib.so
mkdir -p ../deploy
cp libexecutablesharedlib.so ../deploy
```

下面代码展示了演示应用程序的细节，其目的是证明我们的共享库在变为可执行文件后，并未丧失其原有功能：

file: main.c
```c
#include <stdio.h>
#include "sharedLibExports.h"

int main(int argc, char* argv[])
{
	printMessage();
	return 0;
}
```

file: build.sh

```bash
g++ -Wall -O2 -I../sharedLib/exports/ -c src/main.c -o src/main.o
g++  ./src/main.o -lpthread -lm -ldl -L../deploy -lexecutablesharedlib -Wl,-Bdynamic -Wl,-R../deploy -o demoApp
```

当您尝试使用时，会出现如下所示的结果。

```bash
$ tree .
.
├── deploy
│   └── libexecutablesharedlib.so
├── Makefile
├── sharedLib
│   ├── build.sh
│   ├── exports
│   │   └── sharedLibExports.h
│   ├── libexecutablesharedlib.so
│   ├── Makefile
│   └── src
│       ├── executableSharedLib.c
│       └── executableSharedLib.o
├── simpleBuildSteps.txt
└── testApp
    ├── build.sh
    ├── demoApp
    ├── Makefile
    └── src
        ├── main.c
        └── main.o

7 directories, 14 files
$ ./deploy/libexecutablesharedlib.so
Shared library main() function
$ cd testApp
$ ./demoApp
Running the function exported from the shared library
```


#### 参考资料:
《高级C/C++编译技术》: 11.2.2 其他主题


