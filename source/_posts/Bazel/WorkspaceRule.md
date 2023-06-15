---
toc:
  enable: true
  number: false
  max_depth: 3
title: WorkspaceRule
date: 2023-06-14 14:39:09
tags: Bazel
categories: Bazel
---

WORKSPACE 文件中的 rule 主要是为了引入外部依赖，其主要分为原生 rule 和 Starlark rule

## bind

原生 rule

```bazel
bind(name, actual, compatible_with, deprecation, distribs, features, licenses, restricted_to, tags, testonly, visibility)
```

`bind` 用于给 target 在 `//external` 包中创建一个别名

`//external` 不是常规的包，可以把它看成一个包含所有绑定目标的虚拟包

```bazel
bind(
    name = "javacc-latest",
    actual = "//third_party/javacc-v2",
)
# 使用 bind 后可以用 //external:javacc-latest 来替代 //third_party/javacc-v2

# 引入外部包
bind(
    name = "openssl",
    actual = "@my-ssl//src:openssl-lib",
)
```

`bind` 是不推荐使用的

## local_repository

原生 rule

```bazel
local_repository(name, path, repo_mapping)
```

引入一个本地目录中的 Bazel 仓库

```bazel
local_repository(
    name = "my-ssl",
    path = "/home/user/ssl",
)
# 之后使用 /home/user/ssl 中的 target 时可以用 @my-ssl//src:openssl-lib 表示
```

## new_local_repository

原生 rule

```bazel
new_local_repository(name, build_file, build_file_content, path, repo_mapping, workspace_file, workspace_file_content)
```

引入一个本地目录中的非 Bazel 仓库或文件

```bazel
# WORKSPACE
new_local_repository(
    name = "my-ssl",
    path = "/home/user/ssl",
    build_file = "BUILD.my-ssl",
)
# BUILD.my-ssl
java_library(
    name = "openssl",
    srcs = glob(['*.java'])
    visibility = ["//visibility:public"],
)

# WORKSPACE
new_local_repository(
    name = "piano",
    path = "/home/username/Downloads/piano.jar",
    build_file = "BUILD.piano",
)
# BUILD.plano
java_import(
    name = "play-music",
    jars = ["piano.jar"],
    visibility = ["//visibility:public"],
)
```

## git_repository

Starlark rule，需要 `load(@bazel_tools//tools/build_defs/repo:git.bzl)`

```bazel
git_repository(name, branch, commit, init_submodules, patch_args, patch_cmds, patch_cmds_win,
               patch_tool, patches, recursive_init_submodules, remote, shallow_since, strip_prefix,
               tag, verbose)
```

克隆一个外部 Bazel 仓库

## new_git_repository

Starlark rule，需要 `load(@bazel_tools//tools/build_defs/repo:git.bzl)`

```bazel
new_git_repository(name, branch, build_file, build_file_content, commit, init_submodules,
                   patch_args, patch_cmds, patch_cmds_win, patch_tool, patches,
                   recursive_init_submodules, remote, shallow_since, strip_prefix, tag, verbose,
                   workspace_file, workspace_file_content)
```

克隆一个外部非 Bazel 仓库

## http_archive

Starlark rule，需要 `load(@bazel_tools//tools/build_defs/repo:http.bzl)`

```bazel
http_archive(name, auth_patterns, build_file, build_file_content, canonical_id, netrc, patch_args,
             patch_cmds, patch_cmds_win, patch_tool, patches, sha256, strip_prefix, type, url, urls,
             workspace_file, workspace_file_content)
```

下载一个压缩的 Bazel 仓库，对其解压后引入该仓库

```bazel
# WORKSPACE
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
http_archive(
    name = "my_ssl",
    urls = ["http://example.com/openssl.zip"],
    sha256 = "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855",
    build_file = "@//:openssl.BUILD",
)
#openssl.BUILD
cc_library(
    name = "openssl-lib",
    srcs = ["src/openssl.cc"],
    hdrs = ["src/openssl.h"],
)
# 使用 @my_ssl//:openssl-lib
```

## http_file

Starlark rule，需要 `load(@bazel_tools//tools/build_defs/repo:http.bzl)`

```bazel
http_file(name, auth_patterns, canonical_id, downloaded_file_path, executable, netrc, sha256, urls)
```

通过 URL 下载文件并引入仓库

```bazel
# WORKSPACE
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_file")

http_file(
    name = "my_deb",
    urls = ["http://example.com/package.deb"],
    sha256 = "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855",
)
# 使用 @my_deb//file
```