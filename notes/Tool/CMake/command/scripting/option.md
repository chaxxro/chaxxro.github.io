# option

```cmake
option(<variable> "<help_text>" [value])
```

提供开关选项，`value` 可取 `on` 和 `off`，默认 `off`

如果 `variable` 已经设置为普通变量或缓存变量，则该命令不执行任何操作