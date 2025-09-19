### 客户二进制文件符号与动态库ABI函数冲突

以下项目专为演示此特定场景而创建。
它包含一个静态库、一个动态库，以及同时链接这两者的客户端应用程序（该动态库采用静态链接方式）。
这些库具有重名符号：

**Static Library libstaticlib.a:**

file: staticLib/staticlibexports.h
```c
#pragma once

int staticlib_first_function(int x);
int staticlib_second_function(int x);

int shared_static_duplicate_function(int x);
```

file: staticLib/staticlib.c
```c
#include <stdio.h>
#include "staticlibexports.h"

int staticlib_first_function(int x)
{
    printf("%s\n", __FUNCTION__);
    return (x+1);
}

int staticlib_second_function(int x)
{
    printf("%s\n", __FUNCTION__);
    return (x+2);
}

int shared_static_duplicate_function(int x)
{
	printf("staticlib: %s\n", __FUNCTION__);
	return 0;
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

int shared_static_duplicate_function(int x);
```

file: sharedLib/shlib.c
```c
#include <stdio.h>
#include "staticlibexports.h"

int shlib_function(void)
{
	printf("sharedLib: %s\n", __FUNCTION__);
    return 0;
}

int shared_static_duplicate_function(int x)
{
	printf("sharedLib: %s\n", __FUNCTION__);
	return 0;
}
```

file: sharedLib/build.sh
```bash
gcc -Wall -g -O0 -I../staticLib -c shlib.c 
gcc -shared shlib.o -Wl,-soname,libshlib.so.1 -o libshlib.so.1.0.0
```

**ClientApplication:**

file: clientApp/main.c
```c
#include <stdio.h>
#include "staticlibexports.h"
#include "shlibexports.h"

int main(int argc, char* argv[])
{
    int nRetValue = 0;
    nRetValue += staticlib_first_function(1);
    nRetValue += staticlib_second_function(2);

    shlib_function();    
    shared_static_duplicate_function(1);
    printf("nRetValue = %d\n", nRetValue);
    return nRetValue;
}
```

file: clientApp/build.sh
```c
gcc -Wall -g -O0 -I../staticLib -I../sharedLib -c main.c
gcc main.o -Wl,-L../staticLib -lstaticlib \
           -Wl,-L../sharedLib -lshlib     \
           -Wl,-R../sharedLib         \
           -o clientApp
```

客户端应用程序构建成功，并产生以下输出：

```bash
staticlib_first_function
staticlib_second_function
sharedLib: shlib_function
staticlib: shared_static_duplicate_function
nRetValue = 6
```

显然，链接器选择了静态库中的符号，因为它属于更高优先级的代码区域。
按照如下方式修改构建顺序：

file: clientApp/buildDifferentLinkingOrder.sh
```bash
gcc -Wall -g -O0 -I../staticLib -I../sharedLib -c main.c
gcc main.o -Wl,-L../sharedLib -lshlib     \
           -Wl,-L../staticLib -lstaticlib \
           -Wl,-R../sharedLib             \
           -o clientAppDifferentLinkingOrder
```

请注意，这种改动并不会改变最后的输出结果：
```bash
./clientAppDifferentLinkingOrder
staticlib_first_function
staticlib_second_function
sharedLib: shlib_function
staticlib: shared_static_duplicate_function
nRetValue = 6
```

#### 参考资料:
- 《高级C/C++编译技术》: 9.4.1 案例1：客户二进制文件符号与动态库ABI函数冲突
- Advanced.C.And.Cpp.Compiling/src/duplicateSymbolsHandlingResearch/02_staticLibDuplicatesShlibABISymbol

