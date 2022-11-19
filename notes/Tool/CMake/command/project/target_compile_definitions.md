# target_compile_definitions

```cmake
target_compile_definitions(<target>
  <INTERFACE|PUBLIC|PRIVATE> [items1...]
  [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])

add_compile_definitions(target MACRO_FEATURE_A)
# 等同于 add_compile_options(target -DMACRO_FEATURE_A)
```

为构建添加预处理命令，控制源文件中宏的展开