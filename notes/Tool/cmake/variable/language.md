# 语言变量

变量名|描述|
-|-|
CMAKE_\<LANG\>_COMPILER_ID|Clang、GNU、Intel、MSVC 中的一个
CMAKE_CXX_STANDARD|C++ 语言标准，支持 98、11、14、17、20、23
CMAKE_CXX_STANDARD_REQUIRED|是否必须支持 C++ 语言标准
CMAKE_C_FLAGS|C 编译选项，也可以通过 `ADD_COMPILE_OPTIONS` 添加，作用于所有编译类型
CMAKE_CXX_FLAGS|C++ 编译选项，也可以通过指令 `ADD_COMPILE_OPTIONS` 添加，作用于所有编译类型