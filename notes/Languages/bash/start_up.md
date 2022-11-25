# bash 执行环境

## 启动

1. bash 去检查 /etc/profile 文件是否存在，如果存在就读取并执行这个文件中的命令

2. bash 去检查 ~/.bash_profile、~/.bash_login、~/.profile 文件是否存在，如果存在就读取第一个并执行这个文件中的命令

3. 当 bash 是以 login 方式登录的时候，在 bash 退出时，会额外读取并执行 ~/.bash_logout 文件中的命令

4. 当 bash 是以交互方式登录时，bash 会读取并执行 ~/.bashrc 中的命令

## login shell

用户成功登陆后使用的是 login shell

当通过终端、SSH 或使用 `su -` 命令来切换账号时都会使用 login shell

## 交互式 shell

通过 login shell 开启的 shell

通过 shell 开启了一个新 shell 或者通过程序开启一个新 shell