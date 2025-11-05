### nm命令

nm工具用于列出二进制文件的符号。
输出行在显示符号的同时会标注符号类型。
若二进制文件包含C++代码，默认情况下符号会以修饰形式显示。
以下是几种最常用的参数组合：

**nm <二进制文件路径>**

列出二进制文件的所有符号。
对于共享库而言，这不仅包含.dynamic段的导出符号，还包括所有其他符号。
如果库文件已被strip命令处理过，直接使用nm命令将报告未找到符号。

```bash
$ nm framework/libframework.so
0000000000004038 b completed.0
                 w __cxa_finalize
                 w __cxa_pure_virtual@CXXABI_1.3
00000000000010a0 t deregister_tm_clones
0000000000001110 t __do_global_dtors_aux
0000000000003d80 d __do_global_dtors_aux_fini_array_entry
0000000000004030 d __dso_handle
0000000000003e00 d _DYNAMIC
0000000000001258 t _fini
0000000000001150 t frame_dummy
0000000000003d78 d __frame_dummy_init_array_entry
0000000000002178 r __FRAME_END__
0000000000004000 d _GLOBAL_OFFSET_TABLE_
                 w __gmon_start__
000000000000201c r __GNU_EH_FRAME_HDR
0000000000001000 t _init
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
00000000000010d0 t register_tm_clones
0000000000004038 d __TMC_END__
                 U _ZdlPvm@CXXABI_1.3.9
00000000000011ac T _ZN7Factory6createERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
000000000000117c T _ZN7FactoryD0Ev
000000000000115a T _ZN7FactoryD1Ev
000000000000115a T _ZN7FactoryD2Ev
0000000000001228 T _ZN7ProductD0Ev
0000000000001206 T _ZN7ProductD1Ev
0000000000001206 T _ZN7ProductD2Ev
0000000000003db8 V _ZTI7Factory
0000000000003df0 V _ZTI7Product
0000000000002000 V _ZTS7Factory
0000000000002010 V _ZTS7Product
0000000000003d88 V _ZTV7Factory
0000000000003dc8 V _ZTV7Product
                 U _ZTVN10__cxxabiv117__class_type_infoE@CXXABI_1.3
```

**nm -D <二进制文件路径>** 

仅列出动态段中的符号（即共享库的导出/可见符号）。
```bash
$ nm -D framework/libframework.so
                 w __cxa_finalize
                 w __cxa_pure_virtual@CXXABI_1.3
                 w __gmon_start__
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
                 U _ZdlPvm@CXXABI_1.3.9
00000000000011ac T _ZN7Factory6createERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
000000000000117c T _ZN7FactoryD0Ev
000000000000115a T _ZN7FactoryD1Ev
000000000000115a T _ZN7FactoryD2Ev
0000000000001228 T _ZN7ProductD0Ev
0000000000001206 T _ZN7ProductD1Ev
0000000000001206 T _ZN7ProductD2Ev
0000000000003db8 V _ZTI7Factory
0000000000003df0 V _ZTI7Product
0000000000002000 V _ZTS7Factory
0000000000002010 V _ZTS7Product
0000000000003d88 V _ZTV7Factory
0000000000003dc8 V _ZTV7Product
                 U _ZTVN10__cxxabiv117__class_type_infoE@CXXABI_1.3
```

**nm -C <二进制文件路径>**

以未经修饰格式显示符号。

```bash
$ nm -C framework/libframework.so
0000000000004038 b completed.0
                 w __cxa_finalize
                 w __cxa_pure_virtual@CXXABI_1.3
00000000000010a0 t deregister_tm_clones
0000000000001110 t __do_global_dtors_aux
0000000000003d80 d __do_global_dtors_aux_fini_array_entry
0000000000004030 d __dso_handle
0000000000003e00 d _DYNAMIC
0000000000001258 t _fini
0000000000001150 t frame_dummy
0000000000003d78 d __frame_dummy_init_array_entry
0000000000002178 r __FRAME_END__
0000000000004000 d _GLOBAL_OFFSET_TABLE_
                 w __gmon_start__
000000000000201c r __GNU_EH_FRAME_HDR
0000000000001000 t _init
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
00000000000010d0 t register_tm_clones
0000000000004038 d __TMC_END__
                 U operator delete(void*, unsigned long)@CXXABI_1.3.9
00000000000011ac T Factory::create(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&)
000000000000117c T Factory::~Factory()
000000000000115a T Factory::~Factory()
000000000000115a T Factory::~Factory()
0000000000001228 T Product::~Product()
0000000000001206 T Product::~Product()
0000000000001206 T Product::~Product()
0000000000003db8 V typeinfo for Factory
0000000000003df0 V typeinfo for Product
0000000000002000 V typeinfo name for Factory
0000000000002010 V typeinfo name for Product
0000000000003d88 V vtable for Factory
0000000000003dc8 V vtable for Product
                 U vtable for __cxxabiv1::__class_type_info@CXXABI_1.3
```

**nm -D --no-demangle <二进制文件路径>**

用于打印共享库的动态符号，并严格要求符号保持修饰格式不作解析。

```bash
$ nm -D --no-demangle framework/libframework.so 
                 w __cxa_finalize
                 w __cxa_pure_virtual@CXXABI_1.3
                 w __gmon_start__
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
                 U _ZdlPvm@CXXABI_1.3.9
00000000000011ac T _ZN7Factory6createERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
000000000000117c T _ZN7FactoryD0Ev
000000000000115a T _ZN7FactoryD1Ev
000000000000115a T _ZN7FactoryD2Ev
0000000000001228 T _ZN7ProductD0Ev
0000000000001206 T _ZN7ProductD1Ev
0000000000001206 T _ZN7ProductD2Ev
0000000000003db8 V _ZTI7Factory
0000000000003df0 V _ZTI7Product
0000000000002000 V _ZTS7Factory
0000000000002010 V _ZTS7Product
0000000000003d88 V _ZTV7Factory
0000000000003dc8 V _ZTV7Product
                 U _ZTVN10__cxxabiv117__class_type_infoE@CXXABI_1.3
```

这一选项在检测共享库设计中最常见的错误时极其有用--即设计者忘记在ABI函数声明/定义中添加extern "C"说明符的情况
（而这恰好是客户端二进制文件预期要查找的符号格式）。


**nm -A <库目录路径>/* | grep 符号名称**

可用于在同一目录下的多个二进制文件中搜索特定符号。通过-A参数，该命令会打印出每个包含该符号的库文件名。

```bash
$ nm -A */*.so | grep _ZTI7Factory
framework/libframework.so:0000000000003db8 V _ZTI7Factory
idcard/libidcard.so:                 U _ZTI7Factory
```

**nm -u <二进制文件路径>**

可用于列出库的未定义符号（即该库自身不包含、但预期在运行时由其他已加载动态库提供的符号）。

```bash
$ nm -u libidcard.so
                 U __cxa_atexit@GLIBC_2.2.5
                 w __cxa_finalize@GLIBC_2.2.5
                 w __gmon_start__
                 U __gxx_personality_v0@CXXABI_1.3
                 w _ITM_deregisterTMCloneTable
                 w _ITM_registerTMCloneTable
                 U __stack_chk_fail@GLIBC_2.4
                 U _Unwind_Resume@GCC_3.0
                 U _ZdlPvm@CXXABI_1.3.9
                 U _ZN7FactoryD2Ev
                 U _ZN7ProductD2Ev
                 U _ZNSolsEPFRSoS_E@GLIBCXX_3.4
                 U _ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EOS4_@GLIBCXX_3.4.21
                 U _ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1ERKS4_@GLIBCXX_3.4.21
                 U _ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@GLIBCXX_3.4.21
                 U _ZNSt8ios_base4InitC1Ev@GLIBCXX_3.4
                 U _ZNSt8ios_base4InitD1Ev@GLIBCXX_3.4
                 U _Znwm@GLIBCXX_3.4
                 U _ZSt17__throw_bad_allocv@GLIBCXX_3.4
                 U _ZSt20__throw_length_errorPKc@GLIBCXX_3.4
                 U _ZSt28__throw_bad_array_new_lengthv@GLIBCXX_3.4.29
                 U _ZSt4cout@GLIBCXX_3.4
                 U _ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@GLIBCXX_3.4
                 U _ZStlsIcSt11char_traitsIcESaIcEERSt13basic_ostreamIT_T0_ES7_RKNSt7__cxx1112basic_stringIS4_S5_T1_EE@GLIBCXX_3.4.21
                 U _ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@GLIBCXX_3.4
                 U _ZTI7Factory
                 U _ZTI7Product
                 U _ZTV7Product
                 U _ZTVN10__cxxabiv120__si_class_type_infoE@CXXABI_1.3
```


#### 参考资料:
《高级C/C++编译技术》: 12.2.2 nm
