# 开始一个consul

## 启动一个consul节点

下载二进制https://www.consul.io/downloads.html

启动节点 参考https://www.consul.io/docs/agent/basics.html

Running an Agent

```
$ consul agent -data-dir=/tmp/consul
```

-data-dir=<value>  Path to a data directory to store agent state.

这里我设置为-data-dir=./agent_state

运行起来日志输出，其中一段

Client Addr: [127.0.0.1] (HTTP: 8500, HTTPS: -1, DNS: 8600)

这样只能在同一台机器使用，其他机器无法访问。

修改Client Addr参考https://www.consul.io/docs/agent/options.html

[`-client`](https://www.consul.io/docs/agent/options.html#_client) - The address to which Consul will bind client interfaces, including the HTTP and DNS servers. By default, this is "127.0.0.1", allowing only loopback connections. In Consul 1.0 and later this can be set to a space-separated list of addresses to bind to, or a [go-sockaddr](https://godoc.org/github.com/hashicorp/go-sockaddr/template) template that can potentially resolve to multiple addresses.

运行

./consul agent -server -data-dir=./agent_state -client=0.0.0.0 -ui -bootstrap

然后可以在浏览器中看到相关内容

http://ServerIP:8500/ui/#/dc1/services