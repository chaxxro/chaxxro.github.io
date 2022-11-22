# API

## OOP API

### 使用

- 初始化需要 `(argc, argv)`

```cpp
struct getopt : public std::map<std::string, std::string>
{
    using super = std::map< std::string, std::string >;

    getopt( int argc, const char **argv );
    getopt( const std::vector<std::string> &args );

    size_t size() const;
    bool has( const std::string &op ) const;
    std::string str() const;
    std::string cmdline() const;
};
```

### 存储方式

1. 先按参数数组的下标存储参数值

2. 按分割符分割后按 k-v 存储

```cpp
// ./a.out --file=/a/b/c --depth=123
// 存储结果
// 0       ---> ./a.out
// 1       ---> --file=/a/b/c
// 2       ---> --depth=123
// --depth ---> 123
// --file  ---> /a/b/c
```

### 构造函数

```cpp
// delimiters 是一系列分隔符，而不是分隔符是一个字符串
inline size_t split( std::vector<std::string> &tokens, const std::string &self, const std::string &delimiters ) {
    std::string str;
    tokens.clear();
    for( auto &ch : self ) {
        if( delimiters.find_first_of( ch ) != std::string::npos ) {
            if( str.size() ) tokens.push_back( str ), str = "";
            tokens.push_back( std::string() + ch );
        } else str += ch;
    }
    return str.empty() ? tokens.size() : ( tokens.push_back( str ), tokens.size() );
};

getopt( int argc, const char **argv ) : super() {
    // reconstruct vector
    std::vector<std::string> args( argc, std::string() );
    for( int i = 0; i < argc; ++i ) {
        args[ i ] = argv[ i ];
    }
    // create key=value and key= args as well
    for( auto &it : args ) {
        std::vector<std::string> tokens;
        // 对于每个参数，调用 split 按 = 进行分割
        auto size = getopt_utils::split( tokens, it, "=" );

        // 标准形式 abc=edf
        if( size == 3 && tokens[1] == "=" )
            (*this)[ tokens[0] ] = tokens[2];
        else
        // 特殊形式 abc=
        if( size == 2 && tokens[1] == "=" )
            (*this)[ tokens[0] ] = true;
        else
        // 特殊形式 abc
        if( size == 1 && tokens[0] != argv[0] )
            (*this)[ tokens[0] ] = true;
    }
    // recreate args
    while( argc-- ) {
        (*this)[ std::to_string(argc) ] = std::string( argv[argc] );
    }
}
```

## 函数式 API

### 使用

- 初始化不需要 `(argc, argv)`，而是自动检索输入参数

- 第一个参数是默认选项值，然后是所有选项标识符，标识符之间有优先级

```cpp
template< typename T >
inline T getarg( const T &defaults, const char *argv ) {
    static struct getopt map( getopt_utils::cmdline() );
    return map.has( argv ) ? getopt_utils::as<T>(map[ argv ]) : defaults;
}

// 实例化 const char*
inline const char * getarg( const char *defaults, const char *argv ) {
    static struct getopt map( getopt_utils::cmdline() );
    return map.has( argv ) ? getopt_utils::as<const char *>(map[ argv ]) : defaults;
}

template< typename T, typename... Args >
inline T getarg( const T &defaults, const char *arg0, Args... argv ) {
    T t = getarg<T>( defaults, arg0 );
    // 递归搜索 key
    return t == defaults ? getarg<T>( defaults, argv... ) : t;
}

// 实例化 const char*
template< typename... Args >
inline const char * getarg( const char *defaults, const char *arg0, Args... argv ) {
    const char *t = getarg( defaults, arg0 );
    return t == defaults ? getarg( defaults, argv... ) : t;
}
```

### 实现

函数式 API 是通过封装 OOP API 实现的

自动获取 `(argc, argv)` 是通过 /proc/pid/cmdline 文件中记录的 `(argc, argv)`，参数以 `\0` 分割

```cpp
inline std::vector<std::string> cmdline() {
    std::vector<std::string> args;
    std::string arg;
    pid_t pid = getpid();

    char fname[32] = {};
    // 自动读取命令行参数
    sprintf(fname, "/proc/%d/cmdline", pid);
    std::ifstream ifs(fname);
    if( ifs.good() ) {
        std::stringstream ss;
        ifs >> ss.rdbuf();
        arg = ss.str();
    }
    for( auto end = arg.size(), i = end - end; i < end; ++i ) {
        auto st = i;
        while (i < arg.size() && arg[i] != '\0') ++i;
        args.push_back( arg.substr(st, i - st) );
    }
    return args;
}
```