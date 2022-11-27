# Dockerfile

## 构建镜像

```sh
docker build [OPTIONS] <上下文路径/URL/->
# OPTION说明：
# -f ：指定 Dockerfile 文件名字，默认为当前目录的 Dockerfile 文件；
# -m ：设置构建后内存使用最大值；
# --ulimit ：设置 ulimit；
# -t ：镜像名字和标签，通常使用 name:tag 或 name 格式；
```

当构建的时候，用户会指定构建镜像上下文的路径，`docker build`命令得知这个路径后，会将路径下的所有内容打包，然后上传给 Docker 引擎

`COPY` 这类指令中的源文件的路径都是相对路径，因为 docker 引擎无法获取超出上下文范围的文件

如果目录下有些东西确实不希望构建时传给 Docker 引擎，那么可以用 .gitignore 一样的语法写一个 .dockerignore

`docker build` 还支持从 URL 构建，比如可以直接从 Git repo 中构建

如果所给出的 URL 不是个 Git repo，而是个 tar 压缩包，那么 Docker 引擎会下载这个包，并自动解压缩，以其作为上下文，开始构建

## FROM 指定基础镜像

定制镜像一定是以一个镜像为基础，在其上进行定制

`FROM` 就是指定基础镜像，因此一个 Dockerfile 中 `FROM` 是必备的指令，并且必须是第一条指令

Docker 还存在一个特殊的镜像，名为 scratch，这个镜像是虚拟的概念，并不实际存在，它表示一个空白的镜像

## RUN 执行命令

`RUN` 指令是用来执行命令行命令，格式有两种：

- shell 格式：`RUN <命令>`，就像直接在命令行中输入的命令一样，Dockerfile 支持 Shell 类的行尾添加 `\` 的命令换行方式，以及行首 `#` 进行注释的格式

- exec 格式：`RUN ["可执行文件", "参数1", "参数2"]`，这更像是函数调用中的格式

每一个 `RUN` 的行为，就和手工建立镜像的过程一样：新建立一层，在其上执行这些命令，执行结束后，commit 这一层的修改，构成新的镜像

```
FROM debian:stretch

RUN apt-get update
RUN apt-get install -y gcc libc6-dev make wget
RUN wget -O redis.tar.gz "http://download.redis.io/releases/redis-5.0.3.tar.gz"
RUN mkdir -p /usr/src/redis
RUN tar -xzf redis.tar.gz -C /usr/src/redis --strip-components=1
RUN make -C /usr/src/redis
RUN make -C /usr/src/redis install
```

上面的这种写法创建了 7 层镜像，很多运行时不需要的东西，都被装进了镜像里，比如编译环境、更新的软件包等等

正确的写法应该是

```
FROM debian:stretch

RUN set -x; buildDeps='gcc libc6-dev make wget' \
    && apt-get update \
    && apt-get install -y $buildDeps \
    && wget -O redis.tar.gz "http://download.redis.io/releases/redis-5.0.3.tar.gz" \
    && mkdir -p /usr/src/redis \
    && tar -xzf redis.tar.gz -C /usr/src/redis --strip-components=1 \
    && make -C /usr/src/redis \
    && make -C /usr/src/redis install \
    && rm -rf /var/lib/apt/lists/* \
    && rm redis.tar.gz \
    && rm -r /usr/src/redis \
    && apt-get purge -y --auto-remove $buildDeps
```

## COPY 复制文件

```sh
COPY [--chown=<user>:<group>] [--from=<阶段>] <源路径>... <目标路径>
COPY [--chown=<user>:<group>] [--from=<阶段>] ["<源路径1>",... "<目标路径>"]
# COPY 指令将从构建上下文目录中 <源路径> 的文件/目录复制到新的一层的镜像内的 <目标路径> 位置
# --from=<阶段>中的阶段是必须在 FROM 中定义的，它表示该 copy 操作是从镜像中某个阶段产生的结果中 copy，而不是从宿主机
# --chown=<user>:<group> 选项来改变文件的所属用户及所属组
```

源路径可以是多个，甚至可以是通配符，其通配符规则要满足 Go 的 `filepath.Match` 规则

目标路径可以是容器内的绝对路径，也可以是相对于工作目录的相对路径（工作目录可以用 `WORKDIR` 指令来指定）

如果源路径为文件夹，复制的时候不是直接复制该文件夹，而是将文件夹中的内容复制到目标路径

## ADD 添加文件

`ADD` 命令与 `COPY` 命令基本一致，只是在 `COPY` 命令的基础上增加了两个功能：

1. 支持源文件是一个 URL，此时 docker 引擎会试图去下载这个文件放到目的路径中，下载后的文件权限自动设置为 600

2. 支持自动解压，如果源文件是一个 tar，则会自动进行解压

## CMD 容器启动命令

容器就是进程，那么在启动容器的时候，需要指定所运行的程序及参数

`CMD` 指令就是用于指定默认的容器主进程的启动命令的

- shell 格式：`CMD <命令>`

- exec 格式：`CMD ["可执行文件", "参数1", "参数2"...]`

在运行时可以指定新的命令来替代镜像设置中的这个默认命令

使用 shell 格式的话，实际的命令会被包装为 `sh -c` 的参数的形式进行执行

在指令格式上，一般推荐使用 exec 格式，这类格式在解析时会被解析为 JSON 数组，因此一定要使用双引号 `"`，而不要使用单引号

## ENTRYPOINT 入口点

`ENTRYPOINT` 的目的和 `CMD` 一样，都是在指定容器启动程序及参数

`ENTRYPOINT` 在运行时也可以替代，不过比 `CMD` 要略显繁琐，需要通过 `docker run` 的参数 `--entrypoint` 来指定

当指定了 `ENTRYPOINT` 后，`CMD` 的含义就发生了改变，不再是直接的运行其命令，而是将 `CMD` 的内容作为参数传给 `ENTRYPOINT` 指令

## ENV 设置环境变量

- `ENV <key> <value>`

- `ENV <key1>=<value1> <key2>=<value2>...`

## ARG 构建参数

`ARG <参数名>[=<默认值>]`

构建参数和 `ENV` 的效果一样，都是设置环境变量

所不同的是，`ARG` 所设置的构建环境的环境变量，在将来容器运行时是不会存在这些环境变量的

`ARG` 指令是定义参数名称，以及定义其默认值，该默认值可以在构建命令 `docker build` 中用 `--build-arg <参数名>=<值>` 来覆盖

`ARG` 指令有生效范围，如果在 `FROM` 指令之前指定，那么只能用于 `FROM` 指令前

## VOLUME 定义匿名卷

- `VOLUME ["<路径1>", "<路径2>"...]`

- `VOLUME <路径>`

容器运行时应该尽量保持容器存储层不发生写操作

为了防止运行时用户忘记将动态文件所保存目录挂载为卷，在 Dockerfile 中，可以事先指定某些目录挂载为匿名卷，这样在运行时如果用户不指定挂载，其应用也可以正常运行，不会向容器存储层写入大量数据

## EXPOSE 暴露端口

`EXPOSE <端口1> [<端口2>...]`

`EXPOSE` 指令是声明容器运行时提供服务的端口，在容器运行时并不会因为这个声明应用就会开启这个端口的服务

是帮助镜像使用者理解这个镜像服务的守护端口，以方便配置映射

在运行时使用随机端口映射时，也就是 docker run -P 时，会自动随机映射 EXPOSE 的端口

## WORKDIR 指定工作目录

`WORKDIR <工作目录路径>` 指定工作目录，以后各层的当前目录就被改为指定的目录，如该目录不存在，`WORKDIR` 会帮你建立目录

每一个 `RUN` 都是启动一个容器、执行命令、然后提交存储层文件变更，因此如果需要改变以后各层的工作目录的位置，那么应该使用 `WORKDIR` 指令

如果 `WORKDIR` 指令使用的相对路径，那么所切换的路径与之前的 `WORKDIR` 有关

## USER 指定当前用户

`USER <用户名>[:<用户组>]`

`USER` 指令和 `WORKDIR` 相似，都是改变环境状态并影响以后的层

`WORKDIR` 是改变工作目录，`USER` 则是改变之后层的执行 `RUN`, `CMD` 以及 `ENTRYPOINT` 这类命令的身份

## ONBUILD

`ONBUILD <其它指令>`

`ONBUILD` 是一个特殊的指令，它后面跟的是其它指令，比如 `RUN`, `COPY` 等在当前镜像构建时并不会被执行，只有当以当前镜像为基础镜像，去构建下一级镜像的时候才会被执行

## LABEL 为镜像添加元数据

`LABEL` 指令用来给镜像以键值对的形式添加一些元数据

`LABEL <key>=<value> <key>=<value> <key>=<value> ...`