### 符号导出控制演示实例

为说明可见性控制机制，我创建了一个演示项目，其中包含两个功能完全相同但可见性设置不同的动态库。
这两个库分别被命名为 libdefaultvisibility.so 和 libcontrolledvisibility.so。
在库文件构建完成后，我们使用 nm 工具对它们的符号进行了分析。


**默认符号可见性情况**

libdefaultvisibility.so 的源代码如下:

```c
#include "sharedLibExports.h"

void mylocalfunction1(void)
{
	printf("function1\n");
}

void mylocalfunction2(void)
{
	printf("function2\n");
}

void mylocalfunction3(void)
{
	printf("function3\n");
}

void printMessage(void)
{
	printf("Running the function exported from the shared library\n");
}
```

对已构建的库二进制文件中的符号进行检查后，并未发现异常情况：所有函数的符号均被导出且可见

```bash
$ nm -D libdefaultvisibility.so
                 w __cxa_finalize@GLIBC_2.2.5
                 w __gmon_start__
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
0000000000001150 T printMessage
                 U puts@GLIBC_2.2.5
0000000000001120 T _Z16mylocalfunction1v
0000000000001130 T _Z16mylocalfunction2v
0000000000001140 T _Z16mylocalfunction3v
```

**受控符号可见性案例**

对于需要控制符号可见性/可导出性的动态库，项目Makefile中已指定了`-fvisibility`编译器标志，如下所示

Makefile增加`-fvisibility`编译器标志

```
#
# Compiler
#
INCLUDES         = $(COMMON_INCLUDES)
DEBUG_CFLAGS     = -Wall -g -O0
RELEASE_CFLAGS   = -Wall -O2
VISIBILITY_FLAGS = -fvisibility=hidden -fvisibility-inlines-hidden   # <<================

ifeq ($(DEBUG), 1)
CFLAGS           = $(DEBUG_CFLAGS) -fPIC $(INCLUDES)
else
CFLAGS           = $(RELEASE_CFLAGS) -fPIC $(INCLUDES)
endif

CFLAGS          += $(VISIBILITY_FLAGS)      # <<================

COMPILE          = g++ $(CFLAGS)

#
# Linker
#
LINK             = g++ -shared
```

当仅使用此特定符号可见性设置构建库时，符号检查结果显示函数符号均未被导出。

```bash
$ nm -D libcontrolledvisibility.so 
                 w __cxa_finalize@GLIBC_2.2.5
                 w __gmon_start__
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
                 U puts@GLIBC_2.2.5
```

接下来，当应用了可见性属性的函数签名修饰后，最终效果是：使用__attribute__ ((visibility("default")))声明的函数变得可见。

```cpp
#include "sharedLibExports.h"

#if 1
#define FOR_EXPORT __attribute__ ((visibility("default")))
#else
#define FOR_EXPORT
#endif

void mylocalfunction1(void)
{
	printf("function1\n");
}

void mylocalfunction2(void)
{
	printf("function2\n");
}

void mylocalfunction3(void)
{
	printf("function3\n");
}

// 
// also supported:
// 		FOR_EXPORT void printMessage(void)
// but this is not supported:
//  	void printMessage FOR_EXPORT (void)
// nor this:
// 		void printMessage(void) FOR_EXPORT
//
// i.e. attribute may be declared anywhere 
// before the function name

void FOR_EXPORT printMessage(void)
{
	printf("Running the function exported from the shared library\n");
}
```

```bash
$ nm -D libcontrolledvisibility.so
                 w __cxa_finalize@GLIBC_2.2.5
                 w __gmon_start__
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
0000000000001150 T printMessage
                 U puts@GLIBC_2.2.5
```

**使用strip工具**

还存在另一种控制符号可见性的方法。这种方法不够精细且不可编程，而是通过运行strip命令行工具来实现。
该方式更为粗暴，它能彻底清除库中所有符号的相关信息，甚至达到让常规符号检查工具无法检测到任何符号的程度——无论这些符号是否位于`.dynamic`段中。

```bash
$ strip --strip-symbol=_Z16mylocalfunction1v libdefaultvisibility.so
$ strip --strip-symbol=_Z16mylocalfunction2v libdefaultvisibility.so
$ strip --strip-symbol=_Z16mylocalfunction3v libdefaultvisibility.so
$ nm libdefaultvisibility.so 
0000000000004010 b completed.0
                 w __cxa_finalize@GLIBC_2.2.5
0000000000001060 t deregister_tm_clones
00000000000010d0 t __do_global_dtors_aux
0000000000003e00 d __do_global_dtors_aux_fini_array_entry
0000000000004008 d __dso_handle
0000000000003e08 d _DYNAMIC
0000000000001160 t _fini
0000000000001110 t frame_dummy
0000000000003df8 d __frame_dummy_init_array_entry
0000000000002160 r __FRAME_END__
0000000000003fe8 d _GLOBAL_OFFSET_TABLE_
                 w __gmon_start__
0000000000002058 r __GNU_EH_FRAME_HDR
0000000000001000 t _init
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
0000000000001150 T printMessage
                 U puts@GLIBC_2.2.5
0000000000001090 t register_tm_clones
0000000000004010 d __TMC_END__
```


#### 参考资料:
《高级C/C++编译技术》: 6.2.3 控制动态库符号的可见性

