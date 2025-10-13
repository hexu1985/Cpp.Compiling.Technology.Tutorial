### 列出符号信息

以下是在尝试列出可执行文件与库的符号时可采用的几种方法：

**nm 工具**

**readelf 工具**
具体而言：

通过运行以下命令可获取所有可见符号的列表：

```bash
$ readelf --symbols <二进制文件路径>
```

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

若只需获取专用于动态链接的导出符号列表，可执行以下命令：

```bash
$ readelf --dyn-syms <二进制文件路径>
```

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

**objdump 工具**

具体而言：

通过运行以下命令可获取所有可见符号的列表：

```bash
$ objdump -t <二进制文件路径>
```

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

若只需获取专用于动态链接的导出符号列表，可执行以下命令：

```bash
$ objdump -T <二进制文件路径>
```

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

#### 参考资料:
《高级C/C++编译技术》: 13.4 列出符号信息


