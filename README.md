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

