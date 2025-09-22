### 两个未导出的动态库符号冲突

尽管符号名称可能存在重复，但这些符号不会进入链接器的符号列表，也不会引发任何冲突。
它们的影响严格局限于所属动态库的范畴之内。

为说明这一特定场景，现创建以下演示项目：该项目包含一个静态库、一个共享库以及同时链接这两个库的客户端应用程序。
动态库采用静态链接。

每个二进制文件都包含局部函数，其名称与其他模块中的局部函数名称重复。
此外，客户端应用程序的局部函数与共享库中某个函数的名称完全相同，而该共享库函数的符号已被去除（通过strip命令）。

**Static Library libstaticlib.a:**

file: staticLib/staticlibexports.h
```c
#pragma once

int staticlib_function(int x);
```

file: staticLib/staticlib.c
```c
#include <stdio.h>
#include "staticlibexports.h"

static int local_function(int x)
{
    printf("staticLib: %s\n", __FUNCTION__);
    return 0;	
}

int staticlib_function(int x)
{
    printf("%s\n", __FUNCTION__);
    local_function(x);
    return (x+1);
}

```

file: staticLib/build.sh
```bash
gcc -Wall -g -O0 -c staticlib.c 
ar -rcs libstaticlib.a staticlib.o
```

**Shared Library libshlib.so:**

file: sharedLib/shlibexports.h
```c
#pragma once

int shlib_function(void);
```

file: sharedLib/shlib.c
```c
#include <stdio.h>
#include "staticlibexports.h"

static int local_function(int x)
{
    printf("sharedLib: %s\n", __FUNCTION__);
    return 0;
}

static int local_function_strippedoff(int x)
{
	printf("sharedLib: %s\n", __FUNCTION__);
	return 0;
}

int shlib_function(void)
{
	printf("sharedLib: %s\n", __FUNCTION__);
	local_function(1);
	local_function_strippedoff(1);
    return 0;
}
```

file: sharedLib/build.sh
```bash
gcc -Wall -g -O0 -I../staticLib -c shlib.c 
gcc -shared shlib.o -Wl,-soname,libshlib.so.1 -o libshlib.so.1.0.0
strip -N local_function_strippedoff libshlib.so.1.0.0
ldconfig -n .
ln -s libshlib.so.1 libshlib.so
```

**Client Application:**

file: clientApp/main.c
```c
#include <stdio.h>
#include "staticlibexports.h"
#include "shlibexports.h"

static int local_function(int x)
{
    printf("clientApp: %s\n", __FUNCTION__);
    return 0;	
}

static int local_function_strippedoff(int x)
{
    printf("clientApp: %s\n", __FUNCTION__);
    return 0;		
}

int main(int argc, char* argv[])
{
    shlib_function();
    staticlib_function(1);
    local_function(1);
    local_function_strippedoff(1);
    return 0;
}
```

file: clientApp/build.sh
```bash
gcc -Wall -g -O0 -I../staticLib -I../sharedLib -c main.c
gcc main.o -Wl,-L../staticLib -lstaticlib \
           -Wl,-L../sharedLib -lshlib     \
           -Wl,-R../sharedLib         \
           -o clientApp
```

客户端应用程序构建成功，并产生以下输出：

```bash
$ ./clientApp
sharedLib: shlib_function
sharedLib: local_function
sharedLib: local_function_strippedoff
staticlib_function
staticLib: local_function
clientApp: local_function
clientApp: local_function_strippedoff
```

显然，链接器并未检测到任何重复符号问题。
所有局部和已去除符号都在其特定模块内部完成解析，且未与其他模块中同名的局部和已去除符号产生冲突。


#### 参考资料:
- 《高级C/C++编译技术》: 9.4.4 案例4：两个未导出的动态库符号冲突
- Advanced.C.And.Cpp.Compiling/src/duplicateSymbolsHandlingResearch/04_duplicatedLocalOrStrippedOffSymbols

