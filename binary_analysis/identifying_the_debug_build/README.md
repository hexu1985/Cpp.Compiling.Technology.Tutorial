### 判断是否为调试构建

似乎识别二进制文件是否为调试版本（即使用`-g`选项编译）最可靠的方法是依赖readelf工具。
具体来说，运行：

```bash
$ readelf --debug-dump=line <二进制文件路径>
```

如果该二进制文件是调试版本，该命令将提供非空输出。反之若非调试版本，则仅输出空行。

```bash
$ readelf --debug-dump=line libdemo1.so
.debug_line 节的调试内容转储：

  偏移：                       0x0
  长度：                      85
  DWARF 版本：                5
  Address size (bytes):        8
  Segment selector (bytes):    0
  导言长度：        51
  最小指令长度：              1
  每个指令中最大操作码数：       1
  “is_stmt”的初始值：       1
  行基数：                      -5
  行范围：                      14
  操作码基数：                  13

 操作码:
  Opcode 1 has 0 args
  Opcode 2 has 1 arg
  Opcode 3 has 1 arg
  Opcode 4 has 1 arg
  Opcode 5 has 1 arg
  Opcode 6 has 0 args
  Opcode 7 has 0 args
  Opcode 8 has 0 args
  Opcode 9 has 1 arg
  Opcode 10 has 0 args
  Opcode 11 has 0 args
  Opcode 12 has 1 arg

 The Directory Table (offset 0x22, lines 2, columns 1):
  Entry	Name
  0	(indirect line string, offset: 0x16): /home/hexu/git/Cpp.Compiling.Technology.Tutorial/linux_toolbox/readelf_command/c/sharedLib1
  1	(indirect line string, offset: 0x72): /usr/include

 The File Name Table (offset 0x30, lines 3, columns 2):
  Entry	Dir	Name
  0	0	(indirect line string, offset: 0x0): sharedLib1Functions.c
  1	0	(indirect line string, offset: 0x0): sharedLib1Functions.c
  2	1	(indirect line string, offset: 0x7f): stdio.h

 行号语句：
  [0x0000003f]  将列设定为 1
  [0x00000041]  扩充操作码 2： 设置地址为 0x1119
  [0x0000004c]  Special opcode 8: advance Address by 0 to 0x1119 and Line by 3 to 4
  [0x0000004d]  将列设定为 2
  [0x0000004f]  Special opcode 216: advance Address by 15 to 0x1128 and Line by 1 to 5
  [0x00000050]  将列设定为 1
  [0x00000052]  Advance PC by constant 17 to 0x1139
  [0x00000053]  Special opcode 118: advance Address by 8 to 0x1141 and Line by 1 to 6
  [0x00000054]  Advance PC by 3 to 0x1144
  [0x00000056]  扩充操作码 1： 序列结束
```

当二进制文件包含调试信息时，可通过管道将readelf输出重定向至wc命令来限制信息喷涌，这是一种快速实用的方法：

```bash
$ readelf --debug-dump=line <二进制文件路径> | wc -l
```

或者，也可以使用以下简易脚本，以清晰简洁的文本格式显示 readelf 的检测结果。该脚本要求将二进制文件的路径作为输入参数传入。

file：isDebugVersion.sh

```bash
if readelf --debug-dump=line $1 > /dev/null; then echo "$1 is built for debug"; fi
```

#### 参考资料:
《高级C/C++编译技术》: 12.2.4 readelf，13.8 判断是否为调试构建

