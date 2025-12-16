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
- [符号导出控制演示实例](dynamic_library/the_symbol_export_control_demo_example)
- [动态库完成链接需要满足的条件](dynamic_library/build_so_no_undefined)
- [运行时动态链接](dynamic_library/load_so_by_dlopen)
- [静态编译](dynamic_library/static_build)
- [导入完整归档的情况](dynamic_library/build_so_whole_archive)


### [Linux运行时动态库文件的定位规则](runtime_dynamic_library_location_rules)

- [预加载库](runtime_dynamic_library_location_rules/preloaded_libraries)
- [通过rpath添加加载动态库文件搜索路径](runtime_dynamic_library_location_rules/load_so_by_rpath)
- [LD_LIBRARY_PATH 环境变量](runtime_dynamic_library_location_rules/environment_variable)
- [通过runpath添加加载动态库文件搜索路径](runtime_dynamic_library_location_rules/load_so_by_runpath)
- [ldconfig 缓存](runtime_dynamic_library_location_rules/ldconfig_cache)
- [默认库路径（/lib 与 /usr/lib）](runtime_dynamic_library_location_rules/the_default_library_paths)
- [优先级规则总结](runtime_dynamic_library_location_rules/priority_scheme_summary)


### [重复符号处理](duplicate_symbols)

- [C和C++中重复符号的对比](duplicate_symbols/duplicate_symbols_c_vs_cxx)
- [静态库中的重复符号](duplicate_symbols/duplicate_symbols_in_static_libraries)
- [动态库中的重复符号](duplicate_symbols/duplicate_symbols_in_dynamic_libraries)
- [客户二进制文件符号与动态库ABI函数冲突](duplicate_symbols/client_binary_symbol_collides_with_dynamic_library_abi_function)
- [不同动态库的ABI符号冲突](duplicate_symbols/abi_symbols_of_different_dynamic_libraries_collide)
- [动态库ABI符号和另一个动态库局部符号冲突](duplicate_symbols/dynamic_library_abi_symbol_collides_with_another_dynamic_library_local_symbol)
- [两个未导出的动态库符号冲突](duplicate_symbols/duplicate_symbols_of_non_exported_symbol_dynamic_libraries)
- [静态库中的单例](duplicate_symbols/singleton_in_static_library)


### [基于soname的版本控制方案](soname_based_versioning_scheme)

- [库文件名携带版本信息](soname_based_versioning_scheme/library_filename_carries_the_version_information)
- [常规动态库升级实践](soname_based_versioning_scheme/the_usual_dynamic_library_upgrade_practices)
- [SONAME实现的技术细节](soname_based_versioning_scheme/technicalities_of_the_soname_implementation)


### [基于符号的版本控制方案](symbol_versioning_scheme)

- [基本实现要素](symbol_versioning_scheme/basic_implementation_ingredients)
- [示例项目分析：第1阶段（初始版本）](symbol_versioning_scheme/phase_1_initial_version)
- [示例项目分析：第2阶段（增改次版本号）](symbol_versioning_scheme/phase_2_minor_version_changes)


### [二进制分析工具集](binary_analysis_toolbox)

- [file命令](binary_analysis_toolbox/file_command)
- [size命令](binary_analysis_toolbox/size_command)
- [ldd命令](binary_analysis_toolbox/ldd_command)
- [nm命令](binary_analysis_toolbox/nm_command)
- [objdump命令](binary_analysis_toolbox/objdump_command)
- [readelf命令](binary_analysis_toolbox/readelf_command)
- [strace命令](binary_analysis_toolbox/strace_command)


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
- [判断是否为调试构建](binary_analysis/identifying_the_debug_build)
- [列出加载时依赖项](binary_analysis/listing_load_time_dependencies)
- [查看运行时动态链接的库文件](binary_analysis/listing_dynamically_linked_libraries)



