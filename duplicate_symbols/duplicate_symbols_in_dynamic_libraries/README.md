### 动态库中的重复符号

当动态库作为输入添加到链接过程中时，链接器处理重复符号的方式会变得更为复杂且耐人寻味。
首先，链接器会放弃对重复符号的零容忍策略，不会立即宣告链接失败，而是采用一种近似且非理想的方案来解决符号命名冲突。

为具体说明链接器在此特殊场景中的全新处理方式，我们创建了一个简单的演示项目。
该项目包含两个存在重复符号的动态库，以及一个同时链接这两个动态库的客户端应用程序：

**Shared Library libfirst.so:**

file: libFirst/shlibfirstexports.h

```c
#pragma once

int shlibfirst_function(int x);
int shlib_duplicate_function(int x);
```

file: libFirst/shlib.c
```c
#include <stdio.h>

static int local_shlib_duplicate_function(int x)
{
    printf("shlibFirst: %s\n", __FUNCTION__);
    return 0;	
}

int shlibfirst_function(int x)
{
    printf("shlibFirst: %s\n", __FUNCTION__);
    local_shlib_duplicate_function(x);
    return (x+1);
}

int shlib_duplicate_function(int x)
{
    printf("shlibFirst: %s\n", __FUNCTION__);
    local_shlib_duplicate_function(x);
    return (x+2);
}
```

file: libFirst/build.sh
```bash
gcc -Wall -g -O0 -fPIC -c shlib.c
gcc -shared shlib.o -Wl,-soname,libfirst.so.1 -o libfirst.so.1.0.0
ldconfig -n .
ln -s libfirst.so.1 libfirst.so
```

**Shared Library libsecond.so:**

file: libSecond/shlibsecondexports.h
```c
#pragma once

int shlibsecond_function(int x);
int shlib_duplicate_function(int x);
```

file: libSecond/shlib.c
```c
#include <stdio.h>

static int local_shlib_duplicate_function(int x)
{
    printf("shlibSecond: %s\n", __FUNCTION__);
    return 0;	
}

int shlibsecond_function(int x)
{
    printf("shlibSecond: %s\n", __FUNCTION__);
    local_shlib_duplicate_function(x);
    return (x+1);
}

int shlib_duplicate_function(int x)
{
    printf("shlibSecond: %s\n", __FUNCTION__);
    local_shlib_duplicate_function(x);
    return (x+2);
}
```

file: libSecond/build.sh
```bash
gcc -Wall -g -O0 -fPIC -c shlib.c
gcc -shared shlib.o -Wl,-soname,libsecond.so.1 -o libsecond.so.1.0.0
ldconfig -n .
ln -s libsecond.so.1 libsecond.so
```

**ClientApplication:**

file: clientApp/main.c
```c
#include <stdio.h>
#include "shlibfirstexports.h"
#include "shlibsecondexports.h"

int main(int argc, char* argv[])
{
    int nRetValue = 0;
    nRetValue += shlibfirst_function(1);
    nRetValue += shlibsecond_function(2);
    nRetValue += shlib_duplicate_function(3);
    return nRetValue;
}
```

file: clientApp/build.sh
```bash
gcc -Wall -g -O0 -I../libFirst -I../libSecond -c main.c
gcc main.o -Wl,-L../libFirst -Wl,-lfirst   \
           -Wl,-L../libSecond -Wl,-lsecond \
           -Wl,-R../libFirst               \
           -Wl,-R../libSecond              \
           -o clientApp
```

尽管两个共享库存在重复符号，且其中一个重复符号（shlib_duplicate_function）并非本地函数，
但客户端应用程序的构建仍能顺利完成。

然而运行客户端应用程序时，输出的内容有些出乎意料：

```
shlibFirst: shlibfirst_function
shlibFirst: local_shlib_duplicate_function
shlibSecond: shlibsecond_function
shlibSecond: local_shlib_duplicate_function
shlibFirst: shlib_duplicate_function
shlibFirst: local_shlib_duplicate_function
```

显然，链接器通过某种方式解决了重复符号问题——它选择了其中一个符号实例（位于shlibfirst.so中的版本），
并将所有对shlib_duplicate_function的引用都定向到该特定符号实例。

链接器的这一决定显然存在极大争议。在实际应用场景中，不同动态库中同名函数可能承载着截然不同的功能。
例如，假设动态库libcryptography.so、libnetworkaccess.so和libaudioport.so都包含Initialize()方法，
若链接器擅自决定将所有Initialize()调用仅指向其中某个库的初始化例程（而永远不初始化另外两个库），
将会导致严重后果。

显然，这类情况必须谨慎避免。要实现正确链接，首先需要透彻理解链接器的"思考"方式。


#### 参考资料:
《高级C/C++编译技术》: 9.3 在动态库链接过程中处理重复符号

