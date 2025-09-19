### 不同动态库的ABI符号冲突

为演示此特定场景，我们创建了以下示例项目。
该项目包含两个共享库（均具有重复的ABI符号），客户端应用程序对这两个动态库进行静态链接。
需要补充几个重要细节：其中一个共享库的ABI函数内部会调用重复的ABI函数。

**Shared Library libfirst.so:**

file: shlibFirst/shlibfirstexports.h
```c
#pragma once

int shlib_function(void); // duplicate ABI function
int shlibfirst_function(void);
```

file: shlibFirst/shlib.c
```c
#include <stdio.h>

int shlib_function(void)
{
	printf("shlibFirst: %s\n", __FUNCTION__);
    return 0;
}

int shlibfirst_function(void)
{
	printf("%s\n", __FUNCTION__);
	return 0;
}
```

file: shlibFirst/build.sh
```bash
gcc -Wall -g -O0 -c shlib.c 
gcc -shared shlib.o -Wl,-soname,libfirst.so.1 -o libfirst.so.1.0.0
ldconfig -n .
ln -s libfirst.so.1 libfirst.so
```

