# target_include_directories

```cmake
target_include_directories(<target> [SYSTEM] [AFTER|BEFORE]
  <INTERFACE|PUBLIC|PRIVATE> [items1...]
  [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...])
```

指定编译目标的包含目录

包含目录可以是绝对地址，也可以是相对地址，其中相对地址会被自动转换为以当前 CMakeLists.txt 所在目录为基目录的绝对地址