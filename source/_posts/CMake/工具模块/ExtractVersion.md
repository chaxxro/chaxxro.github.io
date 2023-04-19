---
toc:
  enable: true
  number: false
  max_depth: 3
title: ExtractVersion
date: 2023-04-19 19:43:22
tags: cmake
categories: cmake
---

```cmake
# ExtractVersion.cmake
function(extract_version)
    file(READ "version.h" file_contents)
    
    string(REGEX MATCH "VER_MAJOR ([0-9]+)" _ "${file_contents}")
    if(NOT CMAKE_MATCH_COUNT EQUAL 1)
        message(FATAL_ERROR "Could not extract major version number from version.h")
    endif()
    set(ver_major ${CMAKE_MATCH_1})

    string(REGEX MATCH "VER_MINOR ([0-9]+)" _ "${file_contents}")
    if(NOT CMAKE_MATCH_COUNT EQUAL 1)
        message(FATAL_ERROR "Could not extract minor version number from version.h")
    endif()
    set(ver_minor ${CMAKE_MATCH_1})

    string(REGEX MATCH "VER_PATCH ([0-9]+)" _ "${file_contents}")
    if(NOT CMAKE_MATCH_COUNT EQUAL 1)
        message(FATAL_ERROR "Could not extract patch version number from version.h")
    endif()
    set(ver_patch ${CMAKE_MATCH_1})

    set(VERSION_MAJOR ${ver_major} PARENT_SCOPE)
    set(VERSION_MINOR ${ver_minor} PARENT_SCOPE)
    set(VERSION_PATCH ${ver_patch} PARENT_SCOPE)
    set(VERSION "${ver_major}.${ver_minor}.${ver_patch}" PARENT_SCOPE)
endfunction()
```

```cpp
#define VER_MAJOR 1
#define VER_MINOR 10
#define VER_PATCH 0
```