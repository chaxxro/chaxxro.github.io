# CheckIncludeFiles

```cmake
include(CheckIncludeFiles)
CHECK_INCLUDE_FILES("<includes>" <variable> [LANGUAGE <language>])
# LANGUAGE 支持 c 和 cxx
```

不同平台的差异通常使用一个头文件来进行处理，通常为 config.h，其他文件可以 `include` 该 config.h 来进行平台检查

```cpp
// config.h
#define HAVE_MALLOC_H 1
/* #undef HAVE_SYS_MNTTAB_H 1 */
/* #undef HAVE_SYS_MNTENT_H 1 */
#define HAVE_SYS_MOUNT_H 1

#include "config.h"

#ifdef HAVE_MALLOC_H
#include <malloc.h>
#else
#include <stdlib.h>
#endif

void do_something() {
 void *buf=malloc(1024);
}
```

一些使用自动工具的软件，在编译时需要在 `make` 前使用 `./configure` 来自动生成 config.h 文件

CMake 在 /usr/local/share/CMake/Modules 中提供了一些平台检查的 cmake 脚本，使用这些脚本时需要将脚本引入 CMakeLists.txt

```cmake
include(CheckIncludeFiles)
CHECK_INCLUDE_FILES(malloc.h HAVE_MALLOC_H)
CHECK_INCLUDE_FILES("sys/param.h;sys/mount.h" HAVE_SYS_MOUNT_H)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)
```