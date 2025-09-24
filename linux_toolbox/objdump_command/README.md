### objdump命令

objdump可能是功能最全面的二进制分析工具。
按出现时间来看，它比readelf更早问世，两者在许多功能上存在重叠。
objdump的优势在于除了ELF格式外，它还支持约50种其他二进制格式。
此外，其反汇编能力也优于readelf。

接下来将介绍最常使用objdump完成的任务场景。

**解析ELF头信息**
使用`objdump -f`命令行选项可以查看目标文件的头部信息。
ELF头部提供了大量有用数据，特别是可以快速获取二进制文件类型（目标文件/静态库 vs 动态库 vs 可执行文件）以及入口点（.text段的起始地址）等关键信息。

```bash
$ objdump -f driverApp

driverApp：     文件格式 elf64-x86-64
体系结构：i386:x86-64， 标志 0x00000150：
HAS_SYMS, DYNAMIC, D_PAGED
起始地址 0x0000000000001180
$
$ objdump -f libdemo1.so

libdemo1.so：     文件格式 elf64-x86-64
体系结构：i386:x86-64， 标志 0x00000150：
HAS_SYMS, DYNAMIC, D_PAGED
起始地址 0x0000000000000000
$
$ objdump -f sharedLib1Functions.o

sharedLib1Functions.o：     文件格式 elf64-x86-64
体系结构：i386:x86-64， 标志 0x00000011：
HAS_RELOC, HAS_SYMS
起始地址 0x0000000000000000
```

在检查静态库时，`objdump -f`会打印出库内每个目标文件的头部信息。


**列出并检查分段**

`objdump -h`选项用于列出可用的分段。

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

**列出所有符号**

运行 `objdump -t <二进制文件路径>` 产生的输出结果与执行 `nm <二进制文件路径>` 完全等效。

```bash
$ objdump -t framework/libframework.so

framework/libframework.so：     文件格式 elf64-x86-64

SYMBOL TABLE:
0000000000000000 l    df *ABS*	0000000000000000              crtstuff.c
00000000000010a0 l     F .text	0000000000000000              deregister_tm_clones
00000000000010d0 l     F .text	0000000000000000              register_tm_clones
0000000000001110 l     F .text	0000000000000000              __do_global_dtors_aux
0000000000004038 l     O .bss	0000000000000001              completed.0
0000000000003d80 l     O .fini_array	0000000000000000              __do_global_dtors_aux_fini_array_entry
0000000000001150 l     F .text	0000000000000000              frame_dummy
0000000000003d78 l     O .init_array	0000000000000000              __frame_dummy_init_array_entry
0000000000000000 l    df *ABS*	0000000000000000              Factory.cpp
0000000000000000 l    df *ABS*	0000000000000000              Product.cpp
0000000000000000 l    df *ABS*	0000000000000000              crtstuff.c
0000000000002178 l     O .eh_frame	0000000000000000              __FRAME_END__
0000000000000000 l    df *ABS*	0000000000000000
000000000000201c l       .eh_frame_hdr	0000000000000000              __GNU_EH_FRAME_HDR
0000000000001258 l     F .fini	0000000000000000              _fini
0000000000004000 l     O .got.plt	0000000000000000              _GLOBAL_OFFSET_TABLE_
0000000000004038 l     O .data	0000000000000000              __TMC_END__
0000000000004030 l     O .data	0000000000000000              __dso_handle
0000000000003e00 l     O .dynamic	0000000000000000              _DYNAMIC
0000000000001000 l     F .init	0000000000000000              _init
0000000000001228 g     F .text	000000000000002f              _ZN7ProductD0Ev
0000000000001206 g     F .text	0000000000000021              _ZN7ProductD2Ev
0000000000000000  w      *UND*	0000000000000000              __gmon_start__
0000000000000000       F *UND*	0000000000000000              _ZdlPvm@CXXABI_1.3.9
0000000000000000  w      *UND*	0000000000000000              __cxa_finalize
0000000000003dc8  w    O .data.rel.ro	0000000000000028              _ZTV7Product
0000000000000000  w      *UND*	0000000000000000              _ITM_deregisterTMCloneTable
0000000000002010  w    O .rodata	0000000000000009              _ZTS7Product
0000000000000000  w      *UND*	0000000000000000              _ITM_registerTMCloneTable
00000000000011ac g     F .text	000000000000005a              _ZN7Factory6createERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
0000000000000000       O *UND*	0000000000000000              _ZTVN10__cxxabiv117__class_type_infoE@CXXABI_1.3
0000000000003d88  w    O .data.rel.ro	0000000000000030              _ZTV7Factory
0000000000003db8  w    O .data.rel.ro	0000000000000010              _ZTI7Factory
000000000000115a g     F .text	0000000000000021              _ZN7FactoryD1Ev
0000000000003df0  w    O .data.rel.ro	0000000000000010              _ZTI7Product
0000000000000000  w    F *UND*	0000000000000000              __cxa_pure_virtual@CXXABI_1.3
000000000000117c g     F .text	000000000000002f              _ZN7FactoryD0Ev
0000000000002000  w    O .rodata	0000000000000009              _ZTS7Factory
0000000000001206 g     F .text	0000000000000021              _ZN7ProductD1Ev
000000000000115a g     F .text	0000000000000021              _ZN7FactoryD2Ev
```

**仅列出动态符号**

运行 `objdump -T <二进制文件路径>` 产生的输出结果与执行 `nm -D <二进制文件路径>` 完全等效。

```bash
$ objdump -T framework/libframework.so

framework/libframework.so：     文件格式 elf64-x86-64

DYNAMIC SYMBOL TABLE:
0000000000000000  w   D  *UND*	0000000000000000  Base        __gmon_start__
0000000000000000      DF *UND*	0000000000000000 (CXXABI_1.3.9) _ZdlPvm
0000000000000000  w   D  *UND*	0000000000000000  Base        __cxa_finalize
0000000000000000  w   D  *UND*	0000000000000000  Base        _ITM_deregisterTMCloneTable
0000000000000000  w   D  *UND*	0000000000000000  Base        _ITM_registerTMCloneTable
0000000000000000      DO *UND*	0000000000000000 (CXXABI_1.3) _ZTVN10__cxxabiv117__class_type_infoE
0000000000000000  w   DF *UND*	0000000000000000 (CXXABI_1.3) __cxa_pure_virtual
0000000000003dc8  w   DO .data.rel.ro	0000000000000028  Base        _ZTV7Product
000000000000115a g    DF .text	0000000000000021  Base        _ZN7FactoryD1Ev
0000000000003df0  w   DO .data.rel.ro	0000000000000010  Base        _ZTI7Product
000000000000117c g    DF .text	000000000000002f  Base        _ZN7FactoryD0Ev
0000000000002000  w   DO .rodata	0000000000000009  Base        _ZTS7Factory
000000000000115a g    DF .text	0000000000000021  Base        _ZN7FactoryD2Ev
0000000000002010  w   DO .rodata	0000000000000009  Base        _ZTS7Product
00000000000011ac g    DF .text	000000000000005a  Base        _ZN7Factory6createERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
0000000000001228 g    DF .text	000000000000002f  Base        _ZN7ProductD0Ev
0000000000001206 g    DF .text	0000000000000021  Base        _ZN7ProductD2Ev
0000000000003d88  w   DO .data.rel.ro	0000000000000030  Base        _ZTV7Factory
0000000000003db8  w   DO .data.rel.ro	0000000000000010  Base        _ZTI7Factory
0000000000001206 g    DF .text	0000000000000021  Base        _ZN7ProductD1Ev
```

**检查动态节**

运行 `objdump -p <二进制文件路径>` 可检查动态节（适用于查找DT_RPATH和/或DT_RUNPATH设置）。
请注意，在此场景下需要关注显示输出的末尾部分。

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


**检查重定位节**

运行 `objdump -R <二进制文件路径>` 可检查重定位节信息。

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


**检查数据节**

运行 `objdump -s -j <节名称> <二进制文件路径>` 可获取指定分节数据的十六进制转储值。

```bash
$ objdump -s -j .got FactoryMethod

FactoryMethod：     文件格式 elf64-x86-64

Contents of section .got:
 4f10 d04c0000 00000000 00000000 00000000  .L..............
 4f20 00000000 00000000 30200000 00000000  ........0 ......
 4f30 40200000 00000000 50200000 00000000  @ ......P ......
 4f40 60200000 00000000 70200000 00000000  ` ......p ......
 4f50 80200000 00000000 90200000 00000000  . ....... ......
 4f60 a0200000 00000000 b0200000 00000000  . ....... ......
 4f70 c0200000 00000000 d0200000 00000000  . ....... ......
 4f80 e0200000 00000000 f0200000 00000000  . ....... ......
 4f90 00210000 00000000 10210000 00000000  .!.......!......
 4fa0 20210000 00000000 30210000 00000000   !......0!......
 4fb0 40210000 00000000 50210000 00000000  @!......P!......
 4fc0 60210000 00000000 70210000 00000000  `!......p!......
 4fd0 80210000 00000000 00000000 00000000  .!..............
 4fe0 00000000 00000000 00000000 00000000  ................
 4ff0 00000000 00000000 00000000 00000000  ................
```

**列出并检查程序段**

运行 `objdump -p <二进制文件路径>` 可显示ELF二进制程序段信息。

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


#### 参考资料:
《高级C/C++编译技术》: 12.2.3 objdump

