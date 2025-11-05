### Linux 库文件名携带版本信息

Linux 动态库文件名的最后部分代表库的版本信息：

```
library filename = lib + <library name> + .so + <library version information>
库文件名 = lib + <库名称> + .so + <库版本信息>
```

库版本信息通常采用以下格式：

```
dynamic library version information = <M>.<m>.<p>
库版本信息 = <主版本号>.<次版本号>.<补丁号>
```

其中主版本号（M）由一位或多位数字表示，次版本号（m）由一位或多位数字表示，补丁号（p）则由一位或多位数字表示，用于标识库的补丁（即微小变更）版本。


#### 参考资料:
《高级C/C++编译技术》: 10.2.1 基于soname的版本控制方案

