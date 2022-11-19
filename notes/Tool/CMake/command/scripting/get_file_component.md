# get_file_component

获取完整文件名的特定部分

```cmake
get_filename_component(<var> <FileName> <mode> [CACHE])
```

- `DIRECTORY`：文件夹名

- `NAME`：不带文件夹名的文件名

- `EXT`：最长后缀名

- `NAME_WE`：既没有目录也没有最长扩展名的文件名

- `LAST_EXT`：最后一个后缀名

- `NAME_WLE`：既没有目录也没有最后一个扩展名的文件名

- `ABSOLUTE`：完整文件路径