### 列出与查看段信息

该任务可通过以下工具完成：

**readelf 工具**

```bash
$ readelf --segments <二进制文件路径>
```

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

**objdump 工具**

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


#### 参考资料:
《高级C/C++编译技术》: 13.5 查看段的信息


