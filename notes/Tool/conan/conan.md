# conan

C++ 的跨平台包管理工具

## 用户名

```
conan user  name [-r reponame] [-p password]
```

## 软件包

conan 描述软件包格式：名称/版本@用户/渠道

渠道用来描述是稳定版还是测试版等信息

```
boost/1.64.0@conan/stable
boost/1.65.1@conan/stable
boost/1.66.0@conan/stable
boost/1.67.0@conan/stable
boost/1.68.0@conan/stable
boost/1.69.0@conan/stable
boost/1.70.0@conan/stable
```

## 软件源

Conan 的远端是个列表，并有先后顺序，默认在安装软件包的时候会先检查本地缓存，然后依次从软件源中获取软件包

```
# 添加源
conan remote add my-repo http://my-repo.com/xxx

# 使用 insert 来将其作为首个源
conan remote update my-repo http://my-repo.com/xxx --insert=0
# 常用源应当使用 insert 参数使之排到前面

# 展示所有源
conan remote list

# 删除一个源
conan remote remove my-repo
```

## 搜索包

```
conan search boost* -r=conan-center
# 不指定 -r 的情况下，默认搜索本地缓存
```

## 安装依赖

使用 conan 需要一个配置文件 conanfile.txt，用于写明需要直接依赖的包，conan 会自动处理依赖的传递

```
[requires]
zlib/1.2.11@conan/stable

[generators]
cmake
```

## 导入

将动态链接库复制到可执行文件所在文件夹中，这样它们就可以被可执行文件找到，而无需修改路径

```
[imports]
bin, *.dll -> ./bin
# 从库文件的 bin 文件夹，将后缀为 .dll 的文件拷贝到当前项目的 bin 文件夹
```

## 安装

执行命令 `conan install conanfile_path`，该命令会自动安装需要的包，然后在执行 `install` 的路径下生成三个文件：

- conanbuildinfo.txt

- conanbuildinfo.cmake：告诉 cmake 如何引入依赖包

- conaninfo.txt：用来查看包的详细信息

conan 默认下载的是 release 模式的库文件，通过 `-s build_type=Debug` 设置 build_type 为构建类型，这里可选 None, Debug, Release, RelWithDebInfo, MinSizeRel