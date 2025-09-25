### readelf命令

readelf命令行工具提供了与objdump工具几乎完全重复的功能。

readelf与objdump最显著的区别在于：
- readelf仅支持ELF二进制格式，而objdump可分析约50种不同二进制格式（包括Windows PE/COFF格式）；
- readelf不依赖于二进制文件描述库--所有GNU目标文件解析工具都依赖该库，因此能对ELF文件内容进行独立解析。

**解析ELF文件头**

使用`readelf -h`命令选项可以查看目标文件的头部信息。
文件头包含大量实用信息，特别是可以快速获取以下内容：
二进制文件类型（目标文件/静态库、动态库或可执行文件）以及入口点（.text节的起始地址）相关信息。

```bash
$ readelf -h driverApp
ELF 头：
  Magic：   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00
  类别:                              ELF64
  数据:                              2 补码，小端序 (little endian)
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI 版本:                          0
  类型:                              DYN (Position-Independent Executable file)
  系统架构:                          Advanced Micro Devices X86-64
  版本:                              0x1
  入口点地址：               0x1180
  程序头起点：          64 (bytes into file)
  Start of section headers:          17672 (bytes into file)
  标志：             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           56 (bytes)
  Number of program headers:         13
  Size of section headers:           64 (bytes)
  Number of section headers:         37
  Section header string table index: 36
```

```bash
$ readelf -h libdemo1.so
ELF 头：
  Magic：   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00
  类别:                              ELF64
  数据:                              2 补码，小端序 (little endian)
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI 版本:                          0
  类型:                              DYN (共享目标文件)
  系统架构:                          Advanced Micro Devices X86-64
  版本:                              0x1
  入口点地址：               0x0
  程序头起点：          64 (bytes into file)
  Start of section headers:          14592 (bytes into file)
  标志：             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           56 (bytes)
  Number of program headers:         11
  Size of section headers:           64 (bytes)
  Number of section headers:         36
  Section header string table index: 35
```

```bash
$ readelf -h sharedLib1Functions.o
ELF 头：
  Magic：   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00
  类别:                              ELF64
  数据:                              2 补码，小端序 (little endian)
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI 版本:                          0
  类型:                              REL (可重定位文件)
  系统架构:                          Advanced Micro Devices X86-64
  版本:                              0x1
  入口点地址：               0x0
  程序头起点：          0 (bytes into file)
  Start of section headers:          2488 (bytes into file)
  标志：             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           0 (bytes)
  Number of program headers:         0
  Size of section headers:           64 (bytes)
  Number of section headers:         23
  Section header string table index: 22
```

在检查静态库时，`readelf -h` 会打印出库内每个目标文件的头部信息。

**列出与查看节信息**

使用 `readelf -S` 选项可以列出可用的节。

```bash
$ LANG=c readelf -S libdemo1.so 
There are 36 section headers, starting at offset 0x3900:

Section Headers:
  [Nr] Name              Type             Address           Offset
       Size              EntSize          Flags  Link  Info  Align
  [ 0]                   NULL             0000000000000000  00000000
       0000000000000000  0000000000000000           0     0     0
  [ 1] .note.gnu.pr[...] NOTE             00000000000002a8  000002a8
       0000000000000020  0000000000000000   A       0     0     8
  [ 2] .note.gnu.bu[...] NOTE             00000000000002c8  000002c8
       0000000000000024  0000000000000000   A       0     0     4
  [ 3] .gnu.hash         GNU_HASH         00000000000002f0  000002f0
       0000000000000024  0000000000000000   A       4     0     8
  [ 4] .dynsym           DYNSYM           0000000000000318  00000318
       00000000000000a8  0000000000000018   A       5     1     8
  [ 5] .dynstr           STRTAB           00000000000003c0  000003c0
       0000000000000085  0000000000000000   A       0     0     1
  [ 6] .gnu.version      VERSYM           0000000000000446  00000446
       000000000000000e  0000000000000002   A       4     0     2
  [ 7] .gnu.version_r    VERNEED          0000000000000458  00000458
       0000000000000020  0000000000000000   A       5     1     8
  [ 8] .rela.dyn         RELA             0000000000000478  00000478
       00000000000000a8  0000000000000018   A       4     0     8
  [ 9] .rela.plt         RELA             0000000000000520  00000520
       0000000000000018  0000000000000018  AI       4    23     8
  [10] .init             PROGBITS         0000000000001000  00001000
       000000000000001b  0000000000000000  AX       0     0     4
  [11] .plt              PROGBITS         0000000000001020  00001020
       0000000000000020  0000000000000010  AX       0     0     16
  [12] .plt.got          PROGBITS         0000000000001040  00001040
       0000000000000010  0000000000000010  AX       0     0     16
  [13] .plt.sec          PROGBITS         0000000000001050  00001050
       0000000000000010  0000000000000010  AX       0     0     16
  [14] .text             PROGBITS         0000000000001060  00001060
       00000000000000e4  0000000000000000  AX       0     0     16
  [15] .fini             PROGBITS         0000000000001144  00001144
       000000000000000d  0000000000000000  AX       0     0     4
  [16] .rodata           PROGBITS         0000000000002000  00002000
       0000000000000022  0000000000000000   A       0     0     8
  [17] .eh_frame_hdr     PROGBITS         0000000000002024  00002024
       000000000000002c  0000000000000000   A       0     0     4
  [18] .eh_frame         PROGBITS         0000000000002050  00002050
       0000000000000094  0000000000000000   A       0     0     8
  [19] .init_array       INIT_ARRAY       0000000000003e10  00002e10
       0000000000000008  0000000000000008  WA       0     0     8
  [20] .fini_array       FINI_ARRAY       0000000000003e18  00002e18
       0000000000000008  0000000000000008  WA       0     0     8
  [21] .dynamic          DYNAMIC          0000000000003e20  00002e20
       00000000000001c0  0000000000000010  WA       5     0     8
  [22] .got              PROGBITS         0000000000003fe0  00002fe0
       0000000000000020  0000000000000008  WA       0     0     8
  [23] .got.plt          PROGBITS         0000000000004000  00003000
       0000000000000020  0000000000000008  WA       0     0     8
  [24] .data             PROGBITS         0000000000004020  00003020
       0000000000000008  0000000000000000  WA       0     0     8
  [25] .bss              NOBITS           0000000000004028  00003028
       0000000000000008  0000000000000000  WA       0     0     1
  [26] .comment          PROGBITS         0000000000000000  00003028
       000000000000002d  0000000000000001  MS       0     0     1
  [27] .debug_aranges    PROGBITS         0000000000000000  00003055
       0000000000000030  0000000000000000           0     0     1
  [28] .debug_info       PROGBITS         0000000000000000  00003085
       00000000000000b9  0000000000000000           0     0     1
  [29] .debug_abbrev     PROGBITS         0000000000000000  0000313e
       0000000000000087  0000000000000000           0     0     1
  [30] .debug_line       PROGBITS         0000000000000000  000031c5
       0000000000000059  0000000000000000           0     0     1
  [31] .debug_str        PROGBITS         0000000000000000  0000321e
       00000000000000f2  0000000000000001  MS       0     0     1
  [32] .debug_line_str   PROGBITS         0000000000000000  00003310
       0000000000000087  0000000000000001  MS       0     0     1
  [33] .symtab           SYMTAB           0000000000000000  00003398
       0000000000000270  0000000000000018          34    20     8
  [34] .strtab           STRTAB           0000000000000000  00003608
       0000000000000196  0000000000000000           0     0     1
  [35] .shstrtab         STRTAB           0000000000000000  0000379e
       000000000000015d  0000000000000000           0     0     1
Key to Flags:
  W (write), A (alloc), X (execute), M (merge), S (strings), I (info),
  L (link order), O (extra OS processing required), G (group), T (TLS),
  C (compressed), x (unknown), o (OS specific), E (exclude),
  D (mbind), l (large), p (processor specific)
```

**列出所有符号**

运行 `readelf --symbols` 命令产生的输出，与执行 `nm <二进制文件路径>` 命令完全等效。

```bash
$ LANG=c readelf --symbols libdemo1.so

Symbol table '.dynsym' contains 7 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND
     1: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_deregisterT[...]
     2: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND [...]@GLIBC_2.2.5 (2)
     3: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND __gmon_start__
     4: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_registerTMC[...]
     5: 0000000000000000     0 FUNC    WEAK   DEFAULT  UND [...]@GLIBC_2.2.5 (2)
     6: 0000000000001119    43 FUNC    GLOBAL DEFAULT   14 sharedLib1Function

Symbol table '.symtab' contains 26 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND
     1: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS crtstuff.c
     2: 0000000000001060     0 FUNC    LOCAL  DEFAULT   14 deregister_tm_clones
     3: 0000000000001090     0 FUNC    LOCAL  DEFAULT   14 register_tm_clones
     4: 00000000000010d0     0 FUNC    LOCAL  DEFAULT   14 __do_global_dtors_aux
     5: 0000000000004028     1 OBJECT  LOCAL  DEFAULT   25 completed.0
     6: 0000000000003e18     0 OBJECT  LOCAL  DEFAULT   20 __do_global_dtor[...]
     7: 0000000000001110     0 FUNC    LOCAL  DEFAULT   14 frame_dummy
     8: 0000000000003e10     0 OBJECT  LOCAL  DEFAULT   19 __frame_dummy_in[...]
     9: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS sharedLib1Functions.c
    10: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS crtstuff.c
    11: 00000000000020e0     0 OBJECT  LOCAL  DEFAULT   18 __FRAME_END__
    12: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS
    13: 0000000000001144     0 FUNC    LOCAL  DEFAULT   15 _fini
    14: 0000000000004020     0 OBJECT  LOCAL  DEFAULT   24 __dso_handle
    15: 0000000000003e20     0 OBJECT  LOCAL  DEFAULT   21 _DYNAMIC
    16: 0000000000002024     0 NOTYPE  LOCAL  DEFAULT   17 __GNU_EH_FRAME_HDR
    17: 0000000000004028     0 OBJECT  LOCAL  DEFAULT   24 __TMC_END__
    18: 0000000000004000     0 OBJECT  LOCAL  DEFAULT   23 _GLOBAL_OFFSET_TABLE_
    19: 0000000000001000     0 FUNC    LOCAL  DEFAULT   10 _init
    20: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_deregisterT[...]
    21: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND printf@GLIBC_2.2.5
    22: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND __gmon_start__
    23: 0000000000001119    43 FUNC    GLOBAL DEFAULT   14 sharedLib1Function
    24: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_registerTMC[...]
    25: 0000000000000000     0 FUNC    WEAK   DEFAULT  UND __cxa_finalize@G[...]
```

**仅列出动态符号**

运行 `readelf --dyn-syms` 命令产生的输出，与执行 `nm -D <二进制文件路径>` 命令完全等效。

```bash
$ LANG=c readelf --dyn-syms libdemo1.so 

Symbol table '.dynsym' contains 7 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND 
     1: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_deregisterT[...]
     2: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND [...]@GLIBC_2.2.5 (2)
     3: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND __gmon_start__
     4: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_registerTMC[...]
     5: 0000000000000000     0 FUNC    WEAK   DEFAULT  UND [...]@GLIBC_2.2.5 (2)
     6: 0000000000001119    43 FUNC    GLOBAL DEFAULT   14 sharedLib1Function
```


**检查动态节**

运行 `readelf -d` 命令可以检查动态节，该功能对于查找 DT_RPATH 和/或 DT_RUNPATH 设置非常有用。

```bash
$ readelf -d driverApp

Dynamic section at offset 0x2d60 contains 29 entries:
  标记        类型                         名称/值
 0x0000000000000001 (NEEDED)             共享库：[libdemo1.so]
 0x0000000000000001 (NEEDED)             共享库：[libc.so.6]
 0x000000000000001d (RUNPATH)            Library runpath: [../sharedLib1:../sharedLib2]
 0x000000000000000c (INIT)               0x1000
 0x000000000000000d (FINI)               0x16ac
 0x0000000000000019 (INIT_ARRAY)         0x3d50
 0x000000000000001b (INIT_ARRAYSZ)       8 (bytes)
 0x000000000000001a (FINI_ARRAY)         0x3d58
 0x000000000000001c (FINI_ARRAYSZ)       8 (bytes)
 0x000000006ffffef5 (GNU_HASH)           0x3b0
 0x0000000000000005 (STRTAB)             0x558
 0x0000000000000006 (SYMTAB)             0x3d8
 0x000000000000000a (STRSZ)              268 (bytes)
 0x000000000000000b (SYMENT)             24 (bytes)
 0x0000000000000015 (DEBUG)              0x0
 0x0000000000000003 (PLTGOT)             0x3f70
 0x0000000000000002 (PLTRELSZ)           240 (bytes)
 0x0000000000000014 (PLTREL)             RELA
 0x0000000000000017 (JMPREL)             0x778
 0x0000000000000007 (RELA)               0x6b8
 0x0000000000000008 (RELASZ)             192 (bytes)
 0x0000000000000009 (RELAENT)            24 (bytes)
 0x000000000000001e (FLAGS)              BIND_NOW
 0x000000006ffffffb (FLAGS_1)            标志： NOW PIE
 0x000000006ffffffe (VERNEED)            0x688
 0x000000006fffffff (VERNEEDNUM)         1
 0x000000006ffffff0 (VERSYM)             0x664
 0x000000006ffffff9 (RELACOUNT)          3
 0x0000000000000000 (NULL)               0x0
```

**检查重定位节**

运行 `readelf -r` 命令可以检查重定位段。

```bash
$ readelf -r libdemo1.so

重定位节 '.rela.dyn' at offset 0x478 contains 7 entries:
  偏移量          信息           类型           符号值        符号名称 + 加数
000000003e10  000000000008 R_X86_64_RELATIVE                    1110
000000003e18  000000000008 R_X86_64_RELATIVE                    10d0
000000004020  000000000008 R_X86_64_RELATIVE                    4020
000000003fe0  000100000006 R_X86_64_GLOB_DAT 0000000000000000 _ITM_deregisterTM[...] + 0
000000003fe8  000300000006 R_X86_64_GLOB_DAT 0000000000000000 __gmon_start__ + 0
000000003ff0  000400000006 R_X86_64_GLOB_DAT 0000000000000000 _ITM_registerTMCl[...] + 0
000000003ff8  000500000006 R_X86_64_GLOB_DAT 0000000000000000 __cxa_finalize@GLIBC_2.2.5 + 0

重定位节 '.rela.plt' at offset 0x520 contains 1 entry:
  偏移量          信息           类型           符号值        符号名称 + 加数
000000004018  000200000007 R_X86_64_JUMP_SLO 0000000000000000 printf@GLIBC_2.2.5 + 0
```

**检查节中的数据**

运行 `readelf -x` 命令可生成该节所承载值的十六进制转储。

```bash
$ readelf -x .got driverApp

“.got”节的十六进制输出：
 NOTE: This section has relocations against it, but these have NOT been applied to this dump.
  0x00003f70 603d0000 00000000 00000000 00000000 `=..............
  0x00003f80 00000000 00000000 30100000 00000000 ........0.......
  0x00003f90 40100000 00000000 50100000 00000000 @.......P.......
  0x00003fa0 60100000 00000000 70100000 00000000 `.......p.......
  0x00003fb0 80100000 00000000 90100000 00000000 ................
  0x00003fc0 a0100000 00000000 b0100000 00000000 ................
  0x00003fd0 c0100000 00000000 00000000 00000000 ................
  0x00003fe0 00000000 00000000 00000000 00000000 ................
  0x00003ff0 00000000 00000000 00000000 00000000 ................
```

**列出并查看段**

运行 `readelf --segments` 命令可显示有关 ELF 二进制文件程序的段信息。

```bash
$ readelf --segments libdemo1.so

Elf 文件类型为 DYN (共享目标文件)
Entry point 0x0
There are 11 program headers, starting at offset 64

程序头：
  Type           Offset             VirtAddr           PhysAddr
                 FileSiz            MemSiz              Flags  Align
  LOAD           0x0000000000000000 0x0000000000000000 0x0000000000000000
                 0x0000000000000538 0x0000000000000538  R      0x1000
  LOAD           0x0000000000001000 0x0000000000001000 0x0000000000001000
                 0x0000000000000151 0x0000000000000151  R E    0x1000
  LOAD           0x0000000000002000 0x0000000000002000 0x0000000000002000
                 0x00000000000000e4 0x00000000000000e4  R      0x1000
  LOAD           0x0000000000002e10 0x0000000000003e10 0x0000000000003e10
                 0x0000000000000218 0x0000000000000220  RW     0x1000
  DYNAMIC        0x0000000000002e20 0x0000000000003e20 0x0000000000003e20
                 0x00000000000001c0 0x00000000000001c0  RW     0x8
  NOTE           0x00000000000002a8 0x00000000000002a8 0x00000000000002a8
                 0x0000000000000020 0x0000000000000020  R      0x8
  NOTE           0x00000000000002c8 0x00000000000002c8 0x00000000000002c8
                 0x0000000000000024 0x0000000000000024  R      0x4
  GNU_PROPERTY   0x00000000000002a8 0x00000000000002a8 0x00000000000002a8
                 0x0000000000000020 0x0000000000000020  R      0x8
  GNU_EH_FRAME   0x0000000000002024 0x0000000000002024 0x0000000000002024
                 0x000000000000002c 0x000000000000002c  R      0x4
  GNU_STACK      0x0000000000000000 0x0000000000000000 0x0000000000000000
                 0x0000000000000000 0x0000000000000000  RW     0x10
  GNU_RELRO      0x0000000000002e10 0x0000000000003e10 0x0000000000003e10
                 0x00000000000001f0 0x00000000000001f0  R      0x1

 Section to Segment mapping:
  段节...
   00     .note.gnu.property .note.gnu.build-id .gnu.hash .dynsym .dynstr .gnu.version .gnu.version_r .rela.dyn .rela.plt
   01     .init .plt .plt.got .plt.sec .text .fini
   02     .rodata .eh_frame_hdr .eh_frame
   03     .init_array .fini_array .dynamic .got .got.plt .data .bss
   04     .dynamic
   05     .note.gnu.property
   06     .note.gnu.build-id
   07     .note.gnu.property
   08     .eh_frame_hdr
   09
   10     .init_array .fini_array .dynamic .got
```

**检测调试版本**

readelf命令能够很好地支持显示二进制文件中包含的各种调试专用信息。

要快速判断二进制文件是否为调试版本，可通过以下方法：
若为调试版本，运行`readelf --debug-dump`配合任意可用选项时，标准输出将显示若干行内容；反之若非调试版本，则仅输出空行。

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
《高级C/C++编译技术》: 12.2.4 readelf


