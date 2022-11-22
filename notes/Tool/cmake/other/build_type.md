# 编译类型

CMake 有多种预置的构建类型

- `Release` 对应 `-O3 -DNDEBUG`

- `Debug` 对应 `-g`

- `MinSizeRel` 对应 `-Os -DNDEBUG`

- `RelWithDebInfo` 对应 `-O2 -g -DNDEBUG`

可以通过 `cmake .. -DCMAKE_BUILD_TYPE=Release` 来设置编译类型

CMake 默认不使用任何的编译参数，但可以设置默认的编译类型

```cmake
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message("Setting build type to 'RelWithDebInfo' as none was specified.")
  set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()
```