---
toc:
  enable: true
  number: false
  max_depth: 3
title: http_util
date: 2024-02-06 15:44:04
tags: Bazel
categories: Bazel
---

引入 `load(@bazel_tools//tools/build_defs/repo:http.bzl, xxx)`

## http_archive

```
http_archive(name, add_prefix, auth_patterns, build_file, build_file_content, canonical_id,
             integrity, netrc, patch_args, patch_cmds, patch_cmds_win, patch_tool, patches,
             remote_patch_strip, remote_patches, repo_mapping, sha256, strip_prefix, type, url, urls,
             workspace_file, workspace_file_content)
```

通过 http 下载压缩仓库并解压

- build_file 用作下载仓库的 BUILD 文件，需要绝对标签（`@//`）

- build_file_content 用作下载仓库的 BUILD 文件内容

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