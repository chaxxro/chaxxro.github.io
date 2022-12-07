# 唤醒机制

用于主动解除 I/O 复用的阻塞

## 管道

创建一个管道，将管道一端的 fd 放入 `epollfd` 中，需要唤醒时向管道写入数据，工作线程将立即被唤醒

## eventfd

将调用 `eventfd` 函数创建的 fd 绑定到 `epollfd` 中，需要唤醒时向 fd 写入数据，工作线程将立即唤醒

## socketpair

将调用 `socketpair` 函数创建的其中一个 fd 绑定到 `epollfd` 中，需要唤醒时向 fd 写入数据，工作线程将立即唤醒