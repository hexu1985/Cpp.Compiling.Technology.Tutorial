### 静态库中的单例

试想以下真实场景：假设您需要设计一个独特的进程级日志工具类。该类应以单一实例形式存在，并对所有功能模块可见。

实现方案通常基于单例设计模式。我们暂时假设该单例类位于专用的静态库中。

为获取日志工具的访问权限，承载功能模块的多个动态库都会链接该特定静态库。
由于该单例类仅作为动态库内部功能（即不属于动态库ABI接口），其符号并未导出。
这些单例类符号属于不参与最终链接的代码区域。

当进程启动且所有动态库加载后，会出现这样的情况：多个动态库共存于同一进程中，每个库都在其"私有区域"拥有单例类。
值得注意的是，由于动态库局部符号区的非竞争特性，您会突然发现单例日志工具类存在多个（和谐共存的）实例。

唯一的问题是：您原本需要的是单一实例，而非多个实例！

为演示这一特定场景，我们创建了包含以下组件的演示项目：

- 一个拥有单例类的静态库
- 两个共享库（各链接该静态库）。每个共享库仅导出一个符号：内部调用单例对象方法的函数。从静态库链接引入的单例类符号均未导出。
- 客户端应用程序（链接静态库以直接访问单例类），同时静态链接两个共享库。

客户端应用与两个共享库会分别调用单例类。正如稍后将看到的，应用程序中将呈现单例类的三个不同实例：

**Static Library libsingleton.a:**

file: staticLib/singleton.h
```cpp
#pragma once

#define TRY_STATIC_VARIABLE_SCENARIO
class Singleton
{
public:
    static Singleton& GetInstance(void);
    
public:
    ~Singleton();
    int DoSomething(void);
    
private:
    Singleton();
    Singleton(Singleton const &);     // purposefully not implemented
    void operator=(Singleton const&); // purposefully not implemented
    
#ifdef TRY_STATIC_VARIABLE_SCENARIO
private:
    static Singleton* m_pInstance;
#endif // TRY_STATIC_VARIABLE_SCENARIO
};
```

file: staticLib/singleton.cpp
```cpp
#include <iostream>
#include "singleton.h"
using namespace std;

#ifdef TRY_STATIC_VARIABLE_SCENARIO
Singleton* Singleton::m_pInstance = NULL;
#endif // TRY_STATIC_VARIABLE_SCENARIO

Singleton::Singleton(void)
{
	
}

Singleton::~Singleton()
{
	
}

Singleton& Singleton::GetInstance(void)
{
#ifdef TRY_STATIC_VARIABLE_SCENARIO
    if(NULL == m_pInstance)
        m_pInstance = new Singleton();
    return *m_pInstance;
#else
    static Singleton singleton;
    return singleton;
#endif
}

int Singleton::DoSomething(void)
{
    cout << "singleton instance address = " << this << endl;
    return 0;
}
```

file: staticLib/build.sh
```bash
# for 64-bit OS must also pass -mcmodel=large compiler flag
g++ -fPIC -Wall -g -O0 -c singleton.cpp
ar -rcs libsingleton.a singleton.o
```

**Shared Library libfirst.so:**

file: shlibFirst/shlibfirstexports.h
```cpp
#pragma once

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

int shlibfirst_function(void);

#ifdef __cplusplus
}
#endif // __cplusplus
```

file: shlibFirst/shlib.cpp
```cpp
#include <iostream>
#include "singleton.h"
using namespace std;

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

int shlibfirst_function(void)
{
    cout << __FUNCTION__ << ":" << endl;
    Singleton& singleton = Singleton::GetInstance();
    singleton.DoSomething();
    return 0;
}

#ifdef __cplusplus
}
#endif // __cplusplus
```

file: shlibFirst/build.sh
```bash
rm -rf *.o
rm -rf lib*
g++ -Wall -g -O0 -fPIC -I../staticLib -c shlib.cpp
g++ -shared shlib.o -L../staticLib -lsingleton     \
    -Wl,--version-script=versionScript             \
    -Wl,-soname,libfirst.so.1 -o libfirst.so.1.0.0
ldconfig -n .
ln -s libfirst.so.1 libfirst.so
```

file: shlibFirst/versionScript
```
{
    global:
         shlibfirst_function;
    local:
         *;
};
```

**Shared Library libsecond.so:**

file: shlibSecond/shlibfirstexports.h
```cpp
#pragma once

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

int shlibsecond_function(void);

#ifdef __cplusplus
}
#endif // __cplusplus
```

file: shlibSecond/shlib.cpp
```cpp
#include <iostream>
#include "singleton.h"
using namespace std;

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef int (*PFUNCTION)(void);

int shlibsecond_function(void)
{
    cout << __FUNCTION__ << ":" << endl;
	
    Singleton& singleton = Singleton::GetInstance();
    singleton.DoSomething();
	
    return 0;
}

#ifdef __cplusplus
}
#endif // __cplusplus
```

file: shlibSecond/build.sh
```bash
rm -rf *.o lib*
g++ -Wall -g -O0 -fPIC -I../shlibFirst -I../staticLib -c shlib.cpp
g++ -shared shlib.o -L../staticLib -lsingleton         \
                    -Wl,--version-script=versionScript \
                    -Wl,-soname,libsecond.so.1         \
                    -o libsecond.so.1.0.0
ldconfig -n .
ln -s libsecond.so.1 libsecond.so
```

file: shlibSecond/versionScript
```
{
    global:
         shlibsecond_function;
    local:
         *;
};
```

**ClientApplication:**

file: clientApp/main.c
```cpp
#include <iostream>
#include <dlfcn.h>
#include "shlibfirstexports.h"
#include "shlibsecondexports.h"
#include "singleton.h"

using namespace std;

int main(int argc, char* argv[])
{
    shlibfirst_function();
    shlibsecond_function();	
    cout << "Accesing singleton directly from the client app" << endl;
    Singleton& singleton = Singleton::GetInstance();
    singleton.DoSomething();
    return 0;
}
```

file: clientApp/build.sh
```bash
g++ -Wall -g -O0 -I../staticLib -I../shlibFirst -I../shlibSecond -c main.cpp
g++ main.o -ldl -L../staticLib -lsingleton \
                -L../shlibFirst -lfirst    \
                -L../shlibSecond -lsecond  \
                -Wl,-R../shlibFirst        \
                -Wl,-R../shlibSecond       \
                -o clientApp
```

运行该客户端应用程序会产生以下输出：
```
$ ./clientApp
shlibfirst_function:
singleton instance address = 0x55be2b8db2c0
shlibsecond_function:
singleton instance address = 0x55be2b8db2e0
Accesing singleton directly from the client app
singleton instance address = 0x55be2b8db300
```

**问题解决方案**

针对这类问题存在多种应对方法。

其中一种方案是适当放宽符号导出标准：允许动态库额外导出单例类符号。
完成导出后，单例符号将不再属于允许存在无数实例的无优先级/非竞争符号类别，而是会被提升至"竞争性ABI符号"类别。
根据既定规则，链接器届时将选择单个符号实例，并将所有引用指向该特定单例类符号。

根本解决方案是将单例类放置在动态库中。
通过这种方式，可彻底消除大多数潜在的不良场景。
既不会违反任何ABI设计规则，新模块的设计也不会面临荒谬的额外要求。


#### 参考资料:
- 《高级C/C++编译技术》: 9.4.4 案例4：两个未导出的动态库符号冲突
- Advanced.C.And.Cpp.Compiling/src/duplicateSymbolsHandlingResearch/05_singletonInStaticLibraryExample/01_staticallyAwareDynamicLinkingScenario

