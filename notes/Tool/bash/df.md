# df

显示目前系统上的文件系统磁盘使用情况统计

```sh
df [选项]... [FILE]...

-a 包含所有的具有 0 Blocks 的文件系统
--block-size={SIZE} 使用 {SIZE} 大小的 Blocks
-h 使用人类可读的格式(预设值是不加这个选项的...)
-i 列出 inode 资讯，不列出已使用 block
-k 以 kb 为单位
-l 限制列出的文件结构
-m 以 mb 为单位
-P 使用 POSIX 输出格式
```