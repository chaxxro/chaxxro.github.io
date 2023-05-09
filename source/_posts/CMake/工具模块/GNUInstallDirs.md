---
toc:
  enable: true
  number: false
  max_depth: 3
title: GNUInstallDirs
date: 2023-05-06 19:51:17
tags: cmake
categories: cmake
---

```
# 引入模块
include(GNUInstallDirs)
```

定义了一些 GNU 标准安装目录

- `CMAKE_INSTALL_<dir>` 相对地址

- `CMAKE_INSTALL_FULL_<dir>` 绝对地址，如果还是相对地址则是相对于 `CMAKE_INSTALL_PREFIX`

`dir` 包括

- `BINDIR` -- bin

- `SBINDIR` -- sbin

- `LIBEXEDIR` -- libexec

- `SYSCONFDIR` -- etc

- `SHAREDSTATEDIR` -- com

- `LOCALSTATDIR` -- var

- `RUNSTATEDIR` -- LOCALSTATEDIR/run

- `LIBDIR` -- lib/lib64

- `INCLUDEDIR` -- include

- `OLDINCLUDEDIR` -- /usr/include

- `DATAROOTDIR` -- share

- `DATADIR` -- DATAROOTDIR

- `INFODIR` -- DATAROOTDIR/info

- `LOCALDIR` -- datarootdir/local

- `MANDIR` -- datarootdir/man

- `DOCDIR` -- datarootdir/doc/PROJECT_NAME