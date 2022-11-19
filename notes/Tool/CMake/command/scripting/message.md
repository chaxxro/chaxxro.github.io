# message

```cmake
message([<mode>] "message text" ...)
```

- `FATAL_ERROR` 打印信息后停止 CMake 进程和构建

- `SEND_ERROR` 打印信息后继续 CMake 进程，但停止构建

- `WARNING`

- `AUTHOR_WARNING`

- `DEPRECATION`

- `NOTICE` 默认等级

- `STATUS`

- `VERBOSE`

- `DEBUG`

- `TRACE`

CMake 命令行工具在 stdout 上显示 `STATUS` 至 `TRACE` 的消息，`--log-level` 选项可以设置打印等级

所有其他消息类型都被发送到 stderr

