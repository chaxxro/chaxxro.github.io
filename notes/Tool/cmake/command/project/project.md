# project

```cmake
project(<PROJECT-NAME> [<language-name>...])

project(<PROJECT-NAME>
        [VERSION <major>[.<minor>[.<patch>[.<tweak>]]]]
        [DESCRIPTION <project-description-string>]
        [HOMEPAGE_URL <url-string>]
        [LANGUAGES <language-name>...])
```

设置项目的名称，并存储在 `PROJECT_NAME` 中

当在顶层 CMakeLists.txt 中调用 `project`，名称将同时被存储在 `CMAKE_PROJECT_NAME` 中

## 选项 `VERSION <version>`

`version` 格式 `<major>[.<minor>[.<patch>[.<tweak>]]]`

同时会设置以下变量：

- `PROJECT_VERSION`，`<PROJECT-NAME>_VERSION`

- `PROJECT_VERSION_MAJOR`，`<PROJECT-NAME>_VERSION_MAJOR`

- `PROJECT_VERSION_MINOR`，`<PROJECT-NAME>_VERSION_MINOR`

- `PROJECT_VERSION_PATCH`，`<PROJECT-NAME>_VERSION_PATCH`

- `PROJECT_VERSION_TWEAK`，`<PROJECT-NAME>_VERSION_TWEAK`

当在顶层 CMakeLists.txt 中调用 `project`，同时会设置 `CMAKE_PROJECT_VERSION`

## 选项 `DESCRIPTION <project-description-string>`

用 `project-description-string` 设置 `PROJECT_DESCRIPTION`、`<PROJECT-NAME>_DESCRIPTION`

当在顶层 CMakeLists.txt 中调用 `project`，同时会设置 `CMAKE_PROJECT_DESCRIPTION`

## 选项 `HOMEPAGE_URL <url-string>`

用 `url-string` 设置 `PROJECT_HOMEPAGE_URL`、`<PROJECT-NAME>_HOMEPAGE_URL`

当在顶层 CMakeLists.txt 中调用 `project`，同时会设置 `CMAKE_PROJECT_HOMEPAGE_URL`

## 选项 `LANGUAGES <language-name>...`

支持 C、CXX、CUDA、OBJC、OBJCXX、Fortran、HIP、ISPC、ASM