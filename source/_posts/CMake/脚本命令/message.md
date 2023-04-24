---
toc:
  enable: true
  number: false
  max_depth: 3
title: message
date: 2023-04-19 10:34:09
tags: cmake
categories: cmake
---

## 一般形式

```cmake
message([<mode>] "message text" ...)
```

如果同时打印多条信息，多条信息会被拼接成一条信息输出，拼接时不会用空格隔开

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

## 检查模式

cmake 中经常会用 `message` 做一些检查结果的输出提示，类似于下面的例子

```cmake
message(STATUS "Looking for someheader.h")
#... do the checks, set checkSuccess with the result
if(checkSuccess)
  message(STATUS "Looking for someheader.h - found")
else()
  message(STATUS "Looking for someheader.h - not found")
endif()
```

cmake 引入检查模式来简化这种情况

```cmake
message(CHECK_START "message" ...)
message(CHECK_PASS "message" ...)
message(CHECK_FAIL "message" ...)
```

`CHECK_START` 必须要 `CHECK_PASS` 或 `CHECK_FAIL`

嵌套的 `CHECK_START` 可以使用 `CMAKE_MESSAGE_INDENT` 添加缩进

```cmake
message(CHECK_START "Finding my things")
list(APPEND CMAKE_MESSAGE_INDENT "  ")
unset(missingComponents)

message(CHECK_START "Finding partA")
# ... do check, assume we find A
message(CHECK_PASS "found")

message(CHECK_START "Finding partB")
# ... do check, assume we don't find B
list(APPEND missingComponents B)
message(CHECK_FAIL "not found")

list(POP_BACK CMAKE_MESSAGE_INDENT)
if(missingComponents)
  message(CHECK_FAIL "missing components: ${missingComponents}")
else()
  message(CHECK_PASS "all components found")
endif()

-- Finding my things
--   Finding partA
--   Finding partA - found
--   Finding partB
--   Finding partB - not found
-- Finding my things - missing components: B
```

