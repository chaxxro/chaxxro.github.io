# curl

模拟发送 HTTP 请求

```sh
# 默认行为是将目标页面输出到 shell 窗口
curl url

# 页面保存到本地
curl url > index.html
curl -o index.html url

# 默认使用 GET 方法
# -X 指定具体方法
curl -X GET url
# curl 提供了另外的 -G 或 --get 进行设置使用 GET
# curl 使用 POST 时还需要 -d 指定 POST 数据
curl -X POST -d 'data' url

# -H 设置头部信息，多个头部信息需要多次 -H 设置
```