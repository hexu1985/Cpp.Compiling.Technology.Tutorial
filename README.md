# C++ Compiling Technology Tutorial

## Table of contents

### [生成可执行程序](build_stages)

- [预处理阶段](build_stages/preprocessing)
- [语法分析阶段](build_stages/linguistic_analysis)
- [汇编阶段/优化阶段](build_stages/assembling_and_optimization)
- [输出目标文件阶段（以及反汇编）](build_stages/object_files_and_disassembling)
- [链接阶段](build_stages/linking)


### [静态库](static_library)

- [创建静态库](static_library/build_a)
- [链接静态库](static_library/link_a)
- [静态库工具ar](static_library/manipulate_a)
- [将静态库转换成动态库](static_library/convert_a_to_so)


### [动态库](dynamic_library)

- [创建动态库](dynamic_library/build_so)
- [控制动态库符号的可见性](dynamic_library/export_symbol_visibility_control)
- [动态库完成链接需要满足的条件](dynamic_library/build_so_no_undefined)
- [通过rpath添加加载动态库文件搜索路径](dynamic_library/load_so_by_rpath)
- [通过runpath添加加载动态库文件搜索路径](dynamic_library/load_so_by_runpath)
- [运行时动态链接](dynamic_library/load_so_by_dlopen)
- [静态编译](dynamic_library/static_build)
- [导入完整归档的情况](dynamic_library/build_so_whole_archive)


### [重复符号处理](duplicate_symbols)

- [C和C++中重复符号的对比](duplicate_symbols/duplicate_symbols_c_vs_cxx)
- [静态库中的重复符号](duplicate_symbols/duplicate_symbols_in_static_libraries)
- [动态库中的重复符号](duplicate_symbols/duplicate_symbols_in_dynamic_libraries)
- [客户二进制文件符号与动态库ABI函数冲突](duplicate_symbols/client_binary_symbol_collides_with_dynamic_library_abi_function)
- [不同动态库的ABI符号冲突](duplicate_symbols/abi_symbols_of_different_dynamic_libraries_collide)
- [动态库ABI符号和另一个动态库局部符号冲突](duplicate_symbols/dynamic_library_abi_symbol_collides_with_another_dynamic_library_local_symbol)
- [两个未导出的动态库符号冲突](duplicate_symbols/duplicate_symbols_of_non_exported_symbol_dynamic_libraries)
- [静态库中的单例](duplicate_symbols/singleton_in_static_library)


### [Linux工具集](linux_toolbox)

- [file命令](linux_toolbox/file_command)
- [size命令](linux_toolbox/size_command)
- [ldd命令](linux_toolbox/ldd_command)
- [nm命令](linux_toolbox/nm_command)
- [objdump命令](linux_toolbox/objdump_command)
- [readelf命令](linux_toolbox/readelf_command)
- [strace命令](linux_toolbox/strace_command)


### [二进制分析](binary_analysis)

- [链接过程调试](binary_analysis/debugging_the_linking)
- [反汇编二进制文件](binary_analysis/disassembling_the_binary_file)
- [判断二进制文件类型](binary_analysis/determining_the_binary_file_type)
- [确定可执行文件入口点](binary_analysis/determining_the_executable_entry_point)
- [确定动态库入口点](binary_analysis/determining_the_dynamic_library_entry_point)
- [列出符号信息](binary_analysis/list_symbols)
- [列出与查看节信息](binary_analysis/list_and_examine_sections)
- [列出与查看段信息](binary_analysis/list_and_examine_segments)
- [反汇编二进制文件](binary_analysis/disassembling_the_binary_file)
- [反汇编正在运行的进程](binary_analysis/disassembling_the_running_process)


