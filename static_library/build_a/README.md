### 在Linux中创建静态库

在Linux中打包工具被简单地称作ar，我们可以从GCC工具链中找到这个工具。

下面所展示的一个简单例子演示了根据两个源代码文件来创建静态库的过程：

```shell
$ gcc -c first.c second.c
$ ar rcs libstaticlib.a first.o second.o 
```

按照 Linux 约定，静态库名称以前缀 `lib` 开头，文件扩展名为 `.a`。
除了可以将目标文件打包进一个归档文件（静态库）中，`ar`工具还可以执行其他几项任务：
- 从库中移除一个或多个对象文件。
- 替换库中的一个或多个对象文件。
- 从库中提取一个或多个对象文件。


#### 参考资料:
《高级C/C++编译技术》: 5.1.1 创建Linux静态库
