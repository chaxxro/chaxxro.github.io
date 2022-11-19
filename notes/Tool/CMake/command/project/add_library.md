# add_library

## 常规库

```cmake
add_library(<name> [STATIC | SHARED | MODULE]
            [EXCLUDE_FROM_ALL]
            [<source>...])
```

默认构建静态库，当 `BUILD_SHARED_LIBS` 为 `on` 时默认构建动态库