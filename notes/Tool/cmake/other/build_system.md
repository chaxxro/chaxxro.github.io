# Buildsystem

基于 CMake 的构建系统被组织为一系列高优先级的 target，每个 target 对应一个可执行文件或库，或者是包含自定义命令的自定义目标

target 之间的依赖关系在构建系统中表示，以确定构建顺序和重新生成规则以响应更改

## 可执行文件

```
add_executable(<name> [WIN32] [MACOSX_BUNDLE]
               [EXCLUDE_FROM_ALL]
               [source1] [source2 ...])
```

如果在 `add_executable` 后使用 `target_sources`，`add_executable` 添加的源文件会被忽略

```
target_sources(<target>
  <INTERFACE|PUBLIC|PRIVATE> [items1...]
  [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])
```

`target_source` 的 `target` 必须在 `target_source` 之前使用 `add_executable` 添加

`item` 是相对于当前目录 `CMAKE_CURRENT_SOURCE_DIR` 的用相对地址表示的源文件

## 库

```
add_library(<name> [STATIC | SHARED | MODULE ｜ OBJECT ｜ INTERFACE]
            [EXCLUDE_FROM_ALL]
            [<source>...])
```

默认生成静态库，但可以通过修改 `BUILD_SHARED_LIBS` 为 `on` 将默认库类型修改为动态库

## 构建规范

```
target_include_directories(<target> [SYSTEM] [AFTER|BEFORE]
  <INTERFACE|PUBLIC|PRIVATE> [items1...]
  [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])

target_compile_definitions(<target>
  <INTERFACE|PUBLIC|PRIVATE> [items1...]
  [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])

target_compile_options(<target> [BEFORE]
  <INTERFACE|PUBLIC|PRIVATE> [items1...]
  [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])
```

`target_include_directories`、`target_compile_definitions` 和 `target_compile_options` 需要在 `add_executable` 或 `add_library` 之后使用

`target_include_directories` 指明构建 `target` 时需要引用的头文件目录，头文件目录默认拼接在现有头文件目录的后面；`PRIVATE` 和 `PUBLIC` 填充 `INCLUDE_DIRECTORIES`，`INTERFACE` 和 `PUBLIC` 填充 `INTERFACE_INCLUDE_DIRECTORIES`；头文件目录地址可以是绝对地址也可以是相对地址

`target_compile_definitions` 指明构建 `target` 时的预编译参数，`PRIVATE` 和 `PUBLIC` 填充 `COMPILE_DEFINTIONS`，`INTERFACE` 和 `PUBLIC` 填充 `INTERFACE_COMPILE_DEFINTIONS`；以 `-D` 开头的预编译参数将被忽略，即 `target_compile_definitions(foo PUBLIC FOO)` 和 `target_compile_definitions(foo PUBLIC -DFOO)` 等效

`target_compile_options` 指明构建 `target` 时的编译选项, `PRIVATE` 和 `PUBLIC` 填充 `COMPILE_OPTIONS`，`INTERFACE` 和 `PUBLIC` 填充 `INTERFACE_COMPILE_DEFINTIONS`

## 目标属性

`INCLUDE_DIRECTORIES` 中的参数将在添加 `-I` 或 `-isystem` 的前缀后按顺序出现在目标属性中

`COMPILE_DEFINITIONS` 中的参数将在添加 `-D` 或 `/D` 的前缀后出现在编译行中

`COMPILE_OPTIONS` 以命令行的形式出现在目标属性中

## 链接

```
target_link_libraries(<target>
                      <PRIVATE|PUBLIC|INTERFACE> <item>...
                     [<PRIVATE|PUBLIC|INTERFACE> <item>...]...)
```

- `PUBLIC`：默认值，`item` 将被链接，当 `target` 被使用时，`item` 会出现在链接命令行中

- `PRIVATE`：`item` 将被链接，当 `target` 被使用时，`item` 不会出现在链接命令行中

- `INTERFACE`：`item` 不会被链接，当 `target` 被使用时，`item` 会出现在链接命令行中

`target` 附属的链接库（使用 `PUBLIC` 和 `INTERFACE`）存储在 `INTERFACE_LINK_LIBRARIES` 中，当直接设置 `INTERFACE_LINK_LIBRARIES` 时，原先的值会被覆盖

`target` 将继承附属链接库的 `PUBLIC` 和 `INTERFACE` 属性