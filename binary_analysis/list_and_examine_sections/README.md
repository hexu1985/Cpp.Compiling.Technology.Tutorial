### 列出与查看节信息

有多种方法可以获取二进制文件节的信息。最快速基础的查看方式是运行 size 命令。
若需要更结构化、更详细的分析，通常可借助 objdump 或 readelf 等工具（后者专用于 ELF 二进制格式）。
常规操作的第一步通常是列出二进制文件中的所有节，获取整体概览后再对特定节的内容进行详细解析。

#### 列出可用节信息

可通过以下任一方式获取 ELF 二进制文件的节列表：

**使用 readelf 工具**

```bash
$ readelf -S <二进制文件路径>
```

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

**使用 objdump 工具**

```bash
$ objdump -h <二进制文件路径>
```

```bash
$ objdump -h libdemo1.so

libdemo1.so：     文件格式 elf64-x86-64

节：
Idx Name          Size      VMA               LMA               File off  Algn
  0 .note.gnu.property 00000020  00000000000002a8  00000000000002a8  000002a8  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  1 .note.gnu.build-id 00000024  00000000000002c8  00000000000002c8  000002c8  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  2 .gnu.hash     00000024  00000000000002f0  00000000000002f0  000002f0  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  3 .dynsym       000000a8  0000000000000318  0000000000000318  00000318  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  4 .dynstr       00000085  00000000000003c0  00000000000003c0  000003c0  2**0
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  5 .gnu.version  0000000e  0000000000000446  0000000000000446  00000446  2**1
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  6 .gnu.version_r 00000020  0000000000000458  0000000000000458  00000458  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  7 .rela.dyn     000000a8  0000000000000478  0000000000000478  00000478  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  8 .rela.plt     00000018  0000000000000520  0000000000000520  00000520  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  9 .init         0000001b  0000000000001000  0000000000001000  00001000  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 10 .plt          00000020  0000000000001020  0000000000001020  00001020  2**4
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 11 .plt.got      00000010  0000000000001040  0000000000001040  00001040  2**4
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 12 .plt.sec      00000010  0000000000001050  0000000000001050  00001050  2**4
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 13 .text         000000e4  0000000000001060  0000000000001060  00001060  2**4
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 14 .fini         0000000d  0000000000001144  0000000000001144  00001144  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 15 .rodata       00000022  0000000000002000  0000000000002000  00002000  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 16 .eh_frame_hdr 0000002c  0000000000002024  0000000000002024  00002024  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 17 .eh_frame     00000094  0000000000002050  0000000000002050  00002050  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 18 .init_array   00000008  0000000000003e10  0000000000003e10  00002e10  2**3
                  CONTENTS, ALLOC, LOAD, DATA
 19 .fini_array   00000008  0000000000003e18  0000000000003e18  00002e18  2**3
                  CONTENTS, ALLOC, LOAD, DATA
 20 .dynamic      000001c0  0000000000003e20  0000000000003e20  00002e20  2**3
                  CONTENTS, ALLOC, LOAD, DATA
 21 .got          00000020  0000000000003fe0  0000000000003fe0  00002fe0  2**3
                  CONTENTS, ALLOC, LOAD, DATA
 22 .got.plt      00000020  0000000000004000  0000000000004000  00003000  2**3
                  CONTENTS, ALLOC, LOAD, DATA
 23 .data         00000008  0000000000004020  0000000000004020  00003020  2**3
                  CONTENTS, ALLOC, LOAD, DATA
 24 .bss          00000008  0000000000004028  0000000000004028  00003028  2**0
                  ALLOC
 25 .comment      0000002d  0000000000000000  0000000000000000  00003028  2**0
                  CONTENTS, READONLY
 26 .debug_aranges 00000030  0000000000000000  0000000000000000  00003055  2**0
                  CONTENTS, READONLY, DEBUGGING, OCTETS
 27 .debug_info   000000b9  0000000000000000  0000000000000000  00003085  2**0
                  CONTENTS, READONLY, DEBUGGING, OCTETS
 28 .debug_abbrev 00000087  0000000000000000  0000000000000000  0000313e  2**0
                  CONTENTS, READONLY, DEBUGGING, OCTETS
 29 .debug_line   00000059  0000000000000000  0000000000000000  000031c5  2**0
                  CONTENTS, READONLY, DEBUGGING, OCTETS
 30 .debug_str    000000f2  0000000000000000  0000000000000000  0000321e  2**0
                  CONTENTS, READONLY, DEBUGGING, OCTETS
 31 .debug_line_str 00000087  0000000000000000  0000000000000000  00003310  2**0
                  CONTENTS, READONLY, DEBUGGING, OCTETS
```

#### 查看动态节信息

二进制文件（特别是动态库）的动态节包含大量重要信息。
可通过以下任一方式列出该节内容：

**使用 readelf 工具**

```bash
$ readelf -d <二进制文件路径>
```

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

**使用 objdump 工具**

```bash
$ objdump -p <二进制文件路径>
```

```bash
$ objdump -p FactoryMethod

FactoryMethod：     文件格式 elf64-x86-64

程序头：
    PHDR off    0x0000000000000040 vaddr 0x0000000000000040 paddr 0x0000000000000040 align 2**3
         filesz 0x00000000000002d8 memsz 0x00000000000002d8 flags r--
  INTERP off    0x0000000000000318 vaddr 0x0000000000000318 paddr 0x0000000000000318 align 2**0
         filesz 0x000000000000001c memsz 0x000000000000001c flags r--
    LOAD off    0x0000000000000000 vaddr 0x0000000000000000 paddr 0x0000000000000000 align 2**12
         filesz 0x00000000000010e0 memsz 0x00000000000010e0 flags r--
    LOAD off    0x0000000000002000 vaddr 0x0000000000002000 paddr 0x0000000000002000 align 2**12
         filesz 0x0000000000000ae9 memsz 0x0000000000000ae9 flags r-x
    LOAD off    0x0000000000003000 vaddr 0x0000000000003000 paddr 0x0000000000003000 align 2**12
         filesz 0x00000000000004a0 memsz 0x00000000000004a0 flags r--
    LOAD off    0x0000000000003c60 vaddr 0x0000000000004c60 paddr 0x0000000000004c60 align 2**12
         filesz 0x00000000000003b8 memsz 0x00000000000003c0 flags rw-
 DYNAMIC off    0x0000000000003cd0 vaddr 0x0000000000004cd0 paddr 0x0000000000004cd0 align 2**3
         filesz 0x0000000000000240 memsz 0x0000000000000240 flags rw-
    NOTE off    0x0000000000000338 vaddr 0x0000000000000338 paddr 0x0000000000000338 align 2**3
         filesz 0x0000000000000030 memsz 0x0000000000000030 flags r--
    NOTE off    0x0000000000000368 vaddr 0x0000000000000368 paddr 0x0000000000000368 align 2**2
         filesz 0x0000000000000044 memsz 0x0000000000000044 flags r--
0x6474e553 off    0x0000000000000338 vaddr 0x0000000000000338 paddr 0x0000000000000338 align 2**3
         filesz 0x0000000000000030 memsz 0x0000000000000030 flags r--
EH_FRAME off    0x000000000000304c vaddr 0x000000000000304c paddr 0x000000000000304c align 2**2
         filesz 0x00000000000000c4 memsz 0x00000000000000c4 flags r--
   STACK off    0x0000000000000000 vaddr 0x0000000000000000 paddr 0x0000000000000000 align 2**4
         filesz 0x0000000000000000 memsz 0x0000000000000000 flags rw-
   RELRO off    0x0000000000003c60 vaddr 0x0000000000004c60 paddr 0x0000000000004c60 align 2**0
         filesz 0x00000000000003a0 memsz 0x00000000000003a0 flags r--

动态节：
  NEEDED               libidcard.so
  NEEDED               libframework.so
  NEEDED               libstdc++.so.6
  NEEDED               libgcc_s.so.1
  NEEDED               libc.so.6
  RUNPATH              /home/hexu/git/Cpp.Compiling.Technology.Tutorial/linux_toolbox/objdump_command/cxx/build/idcard:/home/hexu/git/Cpp.Compiling.Technology.Tutorial/linux_toolbox/objdump_command/cxx/build/framework
  INIT                 0x0000000000002000
  FINI                 0x0000000000002adc
  INIT_ARRAY           0x0000000000004c60
  INIT_ARRAYSZ         0x0000000000000008
  FINI_ARRAY           0x0000000000004c68
  FINI_ARRAYSZ         0x0000000000000008
  GNU_HASH             0x00000000000003b0
  STRTAB               0x00000000000006e8
  SYMTAB               0x00000000000003e8
  STRSZ                0x00000000000005f9
  SYMENT               0x0000000000000018
  DEBUG                0x0000000000000000
  PLTGOT               0x0000000000004f10
  PLTRELSZ             0x0000000000000210
  PLTREL               0x0000000000000007
  JMPREL               0x0000000000000ed0
  RELA                 0x0000000000000dc8
  RELASZ               0x0000000000000108
  RELAENT              0x0000000000000018
  FLAGS                0x0000000000000008
  FLAGS_1              0x0000000008000001
  VERNEED              0x0000000000000d28
  VERNEEDNUM           0x0000000000000003
  VERSYM               0x0000000000000ce2
  RELACOUNT            0x0000000000000003

版本引用：
  required from libgcc_s.so.1:
    0x0b792650 0x00 08 GCC_3.0
  required from libc.so.6:
    0x0d696914 0x00 07 GLIBC_2.4
    0x069691b4 0x00 06 GLIBC_2.34
    0x09691a75 0x00 04 GLIBC_2.2.5
  required from libstdc++.so.6:
    0x0297f871 0x00 05 GLIBCXX_3.4.21
    0x056bafd3 0x00 03 CXXABI_1.3
    0x08922974 0x00 02 GLIBCXX_3.4
```

从动态节中可提取的信息里，以下几类具有极高价值：

- DT_RPATH 或 DT_RUNPATH 字段的值
- 动态库 SONAME 字段的值
- 所需动态库的列表（DT_NEEDED 字段）


#### 查看重定位节信息

可通过以下方式完成此任务：

**使用 readelf 工具**

```bash
$ readelf -r <二进制文件路径>
```

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

**使用 objdump 工具**

```bash
$ objdump -R <二进制文件路径>
```

```bash
$ objdump -R framework/libframework.so

framework/libframework.so：     文件格式 elf64-x86-64

DYNAMIC RELOCATION RECORDS
OFFSET           TYPE              VALUE
0000000000003d78 R_X86_64_RELATIVE  *ABS*+0x0000000000001150
0000000000003d80 R_X86_64_RELATIVE  *ABS*+0x0000000000001110
0000000000004030 R_X86_64_RELATIVE  *ABS*+0x0000000000004030
0000000000003d90 R_X86_64_64       _ZTI7Factory@@Base
0000000000003da8 R_X86_64_64       __cxa_pure_virtual@CXXABI_1.3
0000000000003db0 R_X86_64_64       __cxa_pure_virtual@CXXABI_1.3
0000000000003de8 R_X86_64_64       __cxa_pure_virtual@CXXABI_1.3
0000000000003db8 R_X86_64_64       _ZTVN10__cxxabiv117__class_type_infoE@CXXABI_1.3+0x0000000000000010
0000000000003df0 R_X86_64_64       _ZTVN10__cxxabiv117__class_type_infoE@CXXABI_1.3+0x0000000000000010
0000000000003dc0 R_X86_64_64       _ZTS7Factory@@Base
0000000000003dd0 R_X86_64_64       _ZTI7Product@@Base
0000000000003df8 R_X86_64_64       _ZTS7Product@@Base
0000000000003fd0 R_X86_64_GLOB_DAT  __gmon_start__@Base
0000000000003fd8 R_X86_64_GLOB_DAT  __cxa_finalize@Base
0000000000003fe0 R_X86_64_GLOB_DAT  _ZTV7Product@@Base
0000000000003fe8 R_X86_64_GLOB_DAT  _ITM_deregisterTMCloneTable@Base
0000000000003ff0 R_X86_64_GLOB_DAT  _ITM_registerTMCloneTable@Base
0000000000003ff8 R_X86_64_GLOB_DAT  _ZTV7Factory@@Base
0000000000004018 R_X86_64_JUMP_SLOT  _ZdlPvm@CXXABI_1.3.9
0000000000004020 R_X86_64_JUMP_SLOT  _ZN7FactoryD1Ev@@Base
0000000000004028 R_X86_64_JUMP_SLOT  _ZN7ProductD1Ev@@Base
```

#### 查看数据节信息

可通过以下方式完成此任务：

**使用 readelf 工具**

```bash
$ readelf -x <节名称> <二进制文件路径>
```

```bash
$ readelf -x .data static_data

Hex dump of section '.data':
  0x00004000 00000000 00000000 08400000 00000000 .........@......
  0x00004010 2a000000 64000000 00000000 00000000 *...d...........
  0x00004020 44617461 20736563 74696f6e 20657861 Data section exa
  0x00004030 6d706c65 00                         mple.
```

**使用 objdump 工具**

```bash
$ objdump -s -j <节名称> <二进制文件路径>
```

```bash
$ objdump -s -j '.data' static_data

static_data:     file format elf64-x86-64

Contents of section .data:
 4000 00000000 00000000 08400000 00000000  .........@......
 4010 2a000000 64000000 00000000 00000000  *...d...........
 4020 44617461 20736563 74696f6e 20657861  Data section exa
 4030 6d706c65 00                          mple.
```


#### 参考资料:
《高级C/C++编译技术》: 13.5 查看节的信息


