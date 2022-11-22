# find_package

为了方便在项目中引入外部依赖包，cmake 官方预定义了许多寻找依赖包的 Module，存储在 `CMAKE_MODULE_PATH` 中及 `path_of_cmake/share/cmake-<version>/Modules` 目录下，每个以 `Find<LibaryName>.cmake` 命名，可以直接用 `find_pakcage` 进行引用，完成对 `xxx_include_dir` 和 `xxx_library` 赋值

```cmake
find_package(<PackageName> [version] [EXACT] [QUIET] [MODULE]
             [REQUIRED] [[COMPONENTS] [components...]]
             [OPTIONAL_COMPONENTS components...]
             [NO_POLICY_SCOPE])
```

- `QUIET` 选项用于禁用消息型信息

- `REQUIRED` 选项用于标记包必须找到

每一个模块都会定义 `LibraryName_FOUND` 标识包是否找到，`LibraryName_Library` 表示库，`Library_Include_Dir` 表示头文件