# update-alternatives

软件多版本管理

```
update-alternatives --install link name path priority
link 为系统中功能相同软件的公共链接目录，比如 /usr/bin/python
name 为命令链接符名称，如 python
path 为你所要使用新命令、新软件的所在目录
priority 为优先级，当命令链接已存在时，需高于当前值，因为当 alternative 为自动模式时,系统默认启用 priority 高的链接

update-alternatives --display name
显示一个命令链接的所有可选命令，即查看一个命令链接组的所有信息

update-alternatives --config name
显示和修改实际指向的候选命令，为在现有的命令链接选择一个作为系统默认

update-alternatives --remove name path
name 与 path 与 install 中的一致
```