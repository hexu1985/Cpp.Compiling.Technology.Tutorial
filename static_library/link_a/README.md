### 链接linux静态库

Linux 静态库文件名是根据以下模式标准创建的：

```
静态库文件名 = lib + <库名称> + .a
```

库文件名的中间部分是库的实际名称，用于将库提交到链接器。

例如：

```
gcc main.o -L../lib -lmystaticlib -o app
```

在Linux中使用-L和-l选项来指定构建过程中库文件的路径。这两个选项的正确使用方法是：
- 将完整的库文件路径分成两个部分：目录路径和库文件名。
- 将目录路径添加到-L链接器选项后面，并传递给链接器。
- 将库文件名（链接器名称）添加到-l参数后面，并传递给链接器。

比如，使用命令行来对main.o文件进行编译，并链接../staticLib目录中的静态库libworkingdemo.a，
然后生成示例程序，命令如下所示：

```
$ gcc main.o -L../staticLib -lworkingdemo -o demo
                         ^              ^
                         |              |
                library folder path    library name only
                                       (not the full library filename !)
```

在使用gcc命令行一次性完成编译链接两个过程时，应该在链接器选项之前添加-Wl选项，如下所示：

```
$ gcc -Wall main.cpp -Wl,-L../staticLib -Wl,-lworkingdemo -o demo
```


#### 参考资料:
《高级C/C++编译技术》: 7.2.1 Linux构建过程中库文件定位规则

