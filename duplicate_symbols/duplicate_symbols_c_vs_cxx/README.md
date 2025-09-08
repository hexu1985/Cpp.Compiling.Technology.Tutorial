### C和C++中重复符号的对比

**重复的C符号**
C语言对于判断两个或多个符号是否为重复项设定了相当简单的标准。
只要函数、结构体或数据类型的名称相同，这些符号就会被视为相同。

例如，编译以下代码将会失败：

file: c/main.c
```c
#include <stdio.h>

int function_with_duplicated_name(int x)
{
    printf("%s\n", __FUNCTION__);
    return 0;	
}

int function_with_duplicated_name(int x, int y)
{
    printf("%s\n", __FUNCTION__);
    return 0;	
}

int main(int argc, char* argv[])
{
    function_with_duplicated_name(1);
    function_with_duplicated_name(1,2);
    return 0;	
}
```

编译器将产生以下错误信息：

```bash
main.c:9:5: error: conflicting types for ‘function_with_duplicated_name’; have ‘int(int,  int)’
    9 | int function_with_duplicated_name(int x, int y)
      |     ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~
main.c:3:5: note: previous definition of ‘function_with_duplicated_name’ with type ‘int(int)’
    3 | int function_with_duplicated_name(int x)
      |     ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~
main.c: In function ‘main’:
main.c:17:5: error: too few arguments to function ‘function_with_duplicated_name’
   17 |     function_with_duplicated_name(1);
      |     ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~
main.c:9:5: note: declared here
    9 | int function_with_duplicated_name(int x, int y)
      |     ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~
```

**重复的C++符号**

作为一门面向对象的编程语言，C++采用了更为宽松的重复符号判定标准。
在命名空间、类/结构体和简单数据类型层面，使用相同名称仍然是判定重复符号的唯一标准。
然而在函数领域，重复符号的判定不再仅限于函数名称，还会考虑参数列表。

函数（方法）重载机制允许相同类的不同方法使用相同名称，只要这些方法具有不同的输入参数列表（且返回值类型不发生改变）。
这一原则同样适用于特殊情况：两个或多个属于同一命名空间但不属于任何类的函数。
尽管这类函数不隶属于任何类，但C++更灵活的重复判定标准仍然适用——只有当函数名称相同且输入参数列表完全一致时，它们才会被判定为重复符号。

编译以下代码将会成功完成：

file: cxx/main.cpp
```cpp
#include <iostream>
using namespace std;

class CTest
{
public:
    CTest(){ x = 0;};
    ~CTest(){};
    
public:
    int runTest(void){ return x;};
  
private:
    int x;
};

int function_with_duplicated_name(int x)
{
    cout << __FUNCTION__ << "(x)" << endl;
    return 0;	
}

int function_with_duplicated_name(int x, int y)
{
    cout << __FUNCTION__ << "(x,y)" << endl;
    return 0;	
}

int main(int argc, char* argv[])
{
    CTest test;
    int x = test.runTest();
	
    function_with_duplicated_name(x);
    function_with_duplicated_name(x,1);
    return 0;	
}
```

file: cxx/build.sh
```bash
g++ -Wall -g -O0 -c main.cpp
g++ main.o -o clientAppC++
```

运行生成的可执行文件将产生以下输出：

```bash
$ ./clientAppC++
function_with_duplicated_name(x)
function_with_duplicated_name(x,y)
```

然而，若尝试将以下方法的声明添加到 main.cpp 文件中：

file: cxx/main2.cpp
```cpp
int function_with_duplicated_name(int x)
{
    cout << __FUNCTION__ << "(x)" << endl;
    return 0;	
}
```

将会违反C++函数重载的基本规则，从而导致以下构建失败：

```cpp
main2.cpp:23:7: error: ambiguating new declaration of ‘float function_with_duplicated_name(int)’
   23 | float function_with_duplicated_name(int x)
      |       ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~
main2.cpp:17:5: note: old declaration ‘int function_with_duplicated_name(int)’
   17 | int function_with_duplicated_name(int x)
      |     ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~
```


#### 参考资料:
《高级C/C++编译技术》: 9.1 重复的符号定义

