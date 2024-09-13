### 静态库工具ar

与静态库相关的绝大多数任务都可以使用 ar 归档实用程序执行。
通过使用 ar，你不仅可以将目标文件合并到静态库中，还可以列出其内容、删除单个目标文件、
或将它们替换为较新的版本。

以下简单示例说明了使用 ar 工具的常见阶段。

假设你有几个源文件（first.c、second.c、third.c 和 fourth.c）和一个可供客户端使用的导出头文件
二进制文件（如以下 5 个示例所示）

first.c
```c
#include "mystaticlibexports.h"
int first_function(int x)
{
 return (x+1);
}
```

second.c
```c
#include "mystaticlibexports.h"
int fourth_function(int x)
{
 return (x+4);
}
```

third.c
```c
#include "mystaticlibexports.h"
int second_function(int x)
{
 return (x+2);
}
```

fourth.c
```c
#include "mystaticlibexports.h"
int third_function(int x)
{
 return (x+3);
}
```

mystaticlibexports.h
```c
#pragma once
int first_function(int x);
int second_function(int x);
int third_function(int x);
int fourth_function(int x);
```

假设你已经编译好了每个源文件, 并生成了相应的目标文件:

```
$ gcc -Wall -c first.c second.c third.c fourth.c
```

以下说明处理静态库的各个阶段：

**创建静态库**

执行`ar -rcs <library name> <list of object files>`命令可以将指定的目标文件合并到一个静态库中。

```
$ ar -rcs libmystaticlib.a first.o second.o third.o fourth.o
$ ls -alg
total 52
drwxrwxr-x 2 hexu 4096 Apr  3 17:11 .
drwxrwxr-x 3 hexu 4096 Apr  3 17:10 ..
-rw-rw-r-- 1 hexu   78 Apr  3 17:09 first.c
-rw-rw-r-- 1 hexu 1240 Apr  3 17:11 first.o
-rw-rw-r-- 1 hexu   79 Apr  3 17:09 fourth.c
-rw-rw-r-- 1 hexu 1248 Apr  3 17:11 fourth.o
-rw-rw-r-- 1 hexu 5366 Apr  3 17:11 libmystaticlib.a
-rw-rw-r-- 1 hexu  124 Apr  3 17:09 mystaticlibexports.h
-rw-rw-r-- 1 hexu   79 Apr  3 17:09 second.c
-rw-rw-r-- 1 hexu 1248 Apr  3 17:11 second.o
-rw-rw-r-- 1 hexu   78 Apr  3 17:09 third.c
-rw-rw-r-- 1 hexu 1240 Apr  3 17:11 third.o
```

**列出静态库目标文件**

执行`ar -t <library name>`命令可以将存储在静态库中的目标文件列表打印出来。
```
$ ar -t libmystaticlib.a
first.o
second.o
third.o
fourth.o
```

**从静态库中删除目标文件**

从静态库中删除目标文件的方式是执行`ar -d <library name> <object file to remove>`命令。
例如，从库中删除first.o：
```
$ ar -t libmystaticlib.a
first.o
second.o
third.o
fourth.o
$ ar -d libmystaticlib.a first.o
$ ar -t libmystaticlib.a 
second.o
third.o
fourth.o
```

**将新的目标文件添加到静态库**

执行`ar -r <library name> <object file to append>`命令可以将新的目标文件添加到静态库中。
例如，基于3中示例的结果，将修改后的first.c编译出的first.o重新添加到静态库中。

```
$ ar -t libmystaticlib.a 
second.o
third.o
fourth.o
$ ar -r libmystaticlib.a first.o
$ ar -t libmystaticlib.a
second.o
third.o
fourth.o
first.o
```

需要注意的是，静态库中存放的目标文件的顺序发生了改变。新的文件实际上被添加到了归档文件的末尾。

**重建目标文件的顺序**

执行`ar -m -b <object file before> <library name> <object file to move>`命令可以调整静态库中目标文件的顺序。
例如，基于4中示例的结果，让first.o的位置调整到second.o前面，从而保持与原来顺序一致。

```
$ ar -t libmystaticlib.a
second.o
third.o
fourth.o
first.o
$ ar -m -b second.o libmystaticlib.a first.o 
$ ar -t libmystaticlib.a
first.o
second.o
third.o
fourth.o
```

#### 参考资料:

-《高级C/C++编译技术》: 12.5 静态库工具
