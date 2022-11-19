# cmake

## 生成构建信息

```
cmake [<options>] <path-to-source>
cmake [<options>] <path-to-existing-build>
cmake [<options>] -S <path-to-source> -B <path-to-build>

# path-to-source 顶级 CMakeLists.txt 与当前地址的相对位置
# path-to-existing-build 编译发生目录，前提是该目录已经生成 CMakeCache.txt

# Options
-S <path-to-source>
-B <path-to-build>
-D <var>[:type]=<value> 为 CMake 添加自定义设置，该设置会覆盖 CMakeCache.txt 中的值，默认类型为 cache
-G <generator-name>
--install-prefix <directory> 必须是绝对位置
```

## 构建

```
cmake --build <dir>             [<options>] [-- <build-tool-options>]
cmake --build --preset <preset> [<options>] [-- <build-tool-options>]

dir 已经生成 CMakeCache.txt 的目录
--clean-first
-preset <preset> 添加编译选项
-jN 并行编译数
```

## 安装

```
cmake --install <dir> [<options>]

dir 已经生成 CMakeCache.txt 的目录
--prefix 覆盖 CMAKE_INSTALL_PREFIX
```