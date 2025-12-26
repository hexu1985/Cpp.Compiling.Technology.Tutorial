### 版本脚本语法概述

截至目前代码示例中展示的版本脚本仅涵盖了广泛支持的语法功能中的一个子集。本节旨在简要概述所支持的各种选项。

**版本节点**

版本脚本的基本实体是版本节点，即位于大括号之间、描述特定版本的命名结构，例如：

```
LIBXYZ_1.0.6 {
... <此处包含若干描述符>
};
```

版本节点通常封装了多个关键词，这些关键词控制着版本化过程的不同方面，其具体种类将在下文进行更详细的探讨。

**版本节点命名规则**

节点名称通常被选择来精确描述该节点所代表的完整版本。通常，名称以由点号或下划线分隔的数字结尾。
按照惯例，代表较晚版本的节点应排列在代表较早版本的节点之后。

然而，这仅仅是便于人类理解的一种惯例。链接器并不特别关注版本节点的具体命名方式，也不关心它们在文件中的排列顺序。
唯一严格的要求是各节点名称必须互不相同。

动态库及其客户端二进制文件的情况与此类似。对它们而言，真正重要的是版本节点被添加到版本文件的时间顺序——即在它们构建时具体存在哪些版本。

**符号导出控制**

版本节点的全局（global）与局部（local）修饰符直接控制符号的导出。在global标签下声明的以分号分隔的符号列表将被导出，而local标签下声明的符号则不会导出。

例如：
```
LIBXYZ_1.0.6 {
    global:
        first_function; second_function;
    local:
        *;
};
```

尽管这并非版本控制方案的核心主题，但这种通过符号导出机制实际上是一种完全合理（且在多个方面是最为优雅的）指定导出符号列表的方式。
关于该机制如何运作的示例将在后续章节中提供。


**通配符支持**

版本脚本支持与shell表达式匹配操作相同的通配符集。例如，以下版本脚本将所有名称以"first"或"second"开头的函数声明为全局函数：

```
LIBXYZ_1.0.6 {
    global:
        first*; second*;
    local:
        *;
};
```

此外，local标签下的星号指定所有其他函数（即未被导出的函数）属于局部作用域。
双引号内指定的文件名将按字面意思处理，无论其中是否包含任何通配符。


**链接说明符支持**

版本脚本可用于指定 extern "C"（无名称修饰）或 extern "C++" 链接说明符。

示例：

```
LIBXYZ_1.0.6 {
    global:
        extern "C" {
            first_function;
        }
    local:
        *;
};
```

**命名空间支持**

版本脚本还支持使用命名空间来指定版本化及/或导出符号的归属关系。

```
LIBXYZ_1.0.6 {
    global:
        extern "C++" {
            libxyz_namespace::*
        }
    local:
        *;
};
```

**未命名节点**

未命名节点可用于指定未版本化的符号。此外，其作用也可承载符号导出说明符（全局和/或局部）。

实际上，当控制符号导出是您使用版本脚本机制的唯一动机时，通常会出现仅包含一个未命名节点的版本脚本。


**版本脚本的附加功能：符号可见性控制**

版本脚本机制的一个附加功能是，它也提供了对符号可见性的控制。
列在版本脚本节点全局（global）标签下的符号最终会被导出，而列在局部（local）标签下的符号则不会被导出。

仅为了指定要导出的符号而使用版本脚本机制是完全合法的。
然而，在这种情况下，强烈建议使用未命名的脚本版本节点，如下所示的简单演示。

```bash
$ ls -alg
total 20
drwxrwxr-x 2 hexu 4096 Dec 26 14:15 .
drwxrwxr-x 3 hexu 4096 Dec 26 14:14 ..
-rw-rw-r-- 1 hexu  170 Dec 26 14:11 build.sh
-rw-rw-r-- 1 hexu   53 Dec 26 14:11 exportControlScript
-rw-rw-r-- 1 hexu  126 Dec 26 14:11 scriptVisibilityControl.c
$ cat build.sh
gcc -Wall -fPIC -c scriptVisibilityControl.c
gcc -shared scriptVisibilityControl.o \
    -Wl,--version-script,exportControlScript \
    -o libscriptcontrolsexportdemo.so
$ cat scriptVisibilityControl.c 
int first_function(int x)
{
        return 0;
}

int second_function(int x)
{
        return 0;
}

int third_function(int x)
{
        return 0;
}
$ bash build.sh
$ nm libscriptcontrolsexportdemo.so | grep function
00000000000010f9 T first_function
000000000000110b t second_function
000000000000111d t third_function
```


#### 参考资料:
《高级C/C++编译技术》: 10.2.2 基于符号的版本控制方案

