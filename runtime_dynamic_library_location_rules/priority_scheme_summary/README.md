### 优先级规则总结

总的来说，优先级规则存在以下两种运行模式：

**当指定了 RUNPATH 字段时（即 DT_RUNPATH 非空）**

1. LD_LIBRARY_PATH 环境变量
2. runpath（DT_RUNPATH 字段）
3. ld.so.cache 缓存
4. 默认库路径（/lib 和 /usr/lib）

**当不存在 RUNPATH 时（即 DT_RUNPATH 为空字符串）**

1. 已加载二进制文件的 RPATH，以及依次加载它的所有二进制文件（直至可执行文件或动态库）的 RPATH
2. LD_LIBRARY_PATH 环境变量
3. ld.so.cache 缓存
4. 默认库路径（/lib 和 /usr/lib）


#### 参考资料:
《高级C/C++编译技术》: 7.3.1 Linux运行时动态库文件的定位规则
