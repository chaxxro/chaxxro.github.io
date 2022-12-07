# 分层设计

根据离业务的远近关系，一般分为 Session 层、Connection 层、Channel 层和 Socket 层

Session 层属于业务层，Connection 层、Channel 层、Socket 层属于网络层

## Session 层

用于记录各种业务状态数据和处理各种业务逻辑

在业务逻辑处理完毕后，如果需要进行网络通信，则依赖 Connection 层进行数据的收发

Session 层对象不控制 Connection 层对象的生命周期，因为虽然 Session 层会主动销毁 Connection 层对象，但 Connection 层对象本身也会因为网络出错等原因被销毁进而引发 Session 层对象销毁

Session 层可以使用 `std::weak_ptr` 引用 Connection 层对象

可以根据业务场景将 Session 层进一步拆分成多层，使每层都专注于自己的业务逻辑

## Connection 层

每一路客户端连接都对应一个 Connection 层对象，用于记录连接的各种状态信息，包括连接状态、数据收发缓冲区、数据流量信息、本端和对端地址信息等

Connection 层对象还需要提供各种网络事件的处理接口

Connection 层对象控制 Channel 层对象生命周期

## Channel 层

Channel 层持有一个 socket，是实际进行数据收发的地方，因而一个 Channel 对象会记录当前需要监听的各种网络事件状态，同时提供这些事件状态的查询和增删改接口

Channel 层和 Socket 层可以合并

## Socket 层

对常用 socket 函数进行封装