---
toc:
  enable: true
  number: false
  max_depth: 3
title: install
date: 2023-04-18 17:28:48
tags: cmake
categories: cmake
---

用于指定在 `make install` 时运行的规则，可以用来安装目标二进制、动态库、静态库以及文件、目录、脚本等

通过调用 `add_subdirectory` 添加的子目录中的安装规则与父目录中的规则冲突时，以按声明的顺序运行

`CMAKE_INSTALL_PREFIX` 是 `install` 时的相对地址前缀，默认 /usr/local/

```cmake
# 安装目标文件
install(TARGETS targets... [EXPORT <export-name>]
        [RUNTIME_DEPENDENCIES args...|RUNTIME_DEPENDENCY_SET <set-name>]
        [
         [ARCHIVE|LIBRARY|RUNTIME|OBJECTS|FRAMEWORK|BUNDLE|
          PRIVATE_HEADER|PUBLIC_HEADER|RESOURCE]
         [DESTINATION <dir>]
         [PERMISSIONS permissions...]
         [CONFIGURATIONS [Debug|Release|...]]
         [COMPONENT <component>]
         [NAMELINK_COMPONENT <component>]
         [OPTIONAL] [EXCLUDE_FROM_ALL]
         [NAMELINK_ONLY|NAMELINK_SKIP]
        ] [...]
        [INCLUDES DESTINATION [<dir> ...]]
)
# 可以是可执行二进制、动态库、静态库、头文件
# ARCHIVE 静态库，默认安装位置 CMAKE_INSTALL_LIBDIR
# LIBRARY 动态库，默认安装位置 CMAKE_INSTALL_LIBDIR
# RUNTIME 可执行文件，默认安装位置 CMAKE_INSTALL_BINDIR
# PUBLIC_HEADER 与库关联的 PUBLIC 头文件，默认安装位置 CMAKE_INSTALL_INCLUDEDIR

# DESTINATION 如果路径以 / 开头，那么指的是绝对路径，
# 否则是 ${CMAKE_INSTALL_PREFIX}/<DESTINATION>
install(TARGETS myExe mySharedLib myStaticLib
        RUNTIME DESTINATION bin           # 安装到 ${CMAKE_INSTALL_PREFIX}/bin
        LIBRARY DESTINATION lib           # 安装到${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION lib/static    # 安装到${CMAKE_INSTALL_PREFIX}/lib/static
)   


# 安装普通文件
install(<FILES|PROGRAMS> files...
        TYPE <type> | DESTINATION <dir>
        [PERMISSIONS permissions...]
        [CONFIGURATIONS [Debug|Release|...]]
        [COMPONENT <component>]
        [RENAME <name>] [OPTIONAL] [EXCLUDE_FROM_ALL])
# 默认 644 权限
install(FILES mylib.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/myproj)

# 安装目录
install(DIRECTORY dirs...
        TYPE <type> | DESTINATION <dir>
        [FILE_PERMISSIONS permissions...]
        [DIRECTORY_PERMISSIONS permissions...]
        [USE_SOURCE_PERMISSIONS] [OPTIONAL] [MESSAGE_NEVER]
        [CONFIGURATIONS [Debug|Release|...]]
        [COMPONENT <component>] [EXCLUDE_FROM_ALL]
        [FILES_MATCHING]
        [[PATTERN <pattern> | REGEX <regex>]
         [EXCLUDE] [PERMISSIONS permissions...]] [...])
)
# 如果 dir 不以 / 结尾，那么这个目录将被安装到目标路径下
# 如果 dir 以 / 结尾，代表将这个目录中的内容安装到目标路径，但不包括这个目录本身
install(DIRECTORY src/ DESTINATION include/myproj
        FILES_MATCHING PATTERN "*.h")
```