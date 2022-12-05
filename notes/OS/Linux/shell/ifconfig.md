# ifconfig

查看网卡和 IP 地址信息

默认显示当前激活的网卡列表，以及每个网卡的 IPv4 地址、IPv6 地址、子网掩码、广播地址等

`-s` 显示精简列表

`-a` 显示所有网卡，包括未激活网卡

`ifconfig name up` 激活网卡，`ifconfig name down` 禁用网卡

`ifconfig` 还可以将一个 IP 地址绑定到某个网卡上，或将一个 IP 地址从某个网卡上解绑

```sh
# 绑定地址
ifconfig name add ip_addr
# 解绑地址
ifconfig name del ip_addr
```