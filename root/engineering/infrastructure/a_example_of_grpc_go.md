# 一个gRPC-go范例程序

grpc-go的介绍：

```
The Go implementation of gRPC: A high performance, open source, general RPC framework that puts mobile and HTTP/2 first.
```

github地址

https://github.com/grpc/grpc-go

注意看readme中的安装方式 go get -u google.golang.org/grpc，此处可能需要全局科学上网。

google提供的范例

https://github.com/grpc/grpc-go/tree/master/examples

写个测试程序试试，完整的代码见[https://github.com/changjixiong/goNotes/tree/master/grpcnotes](https://github.com/changjixiong/goNotes/tree/master/grpcnotes) 。

创建子目录hello，在目录hello中创建一个hello.proto文件，对着exmaples中的helloworld依葫芦画瓢:

```protobuf
syntax = "proto3";

package hello;

service Hello {
  rpc SayHello (HelloRequest) returns (HelloReply) {}
}

message HelloRequest {
  int32 num = 1;
}

message HelloReply {
  string message = 1;
}
```

在目录grpcnotes下执行protoc -I hello/ hello/hello.proto --go_out=plugins=grpc:hello

生成hello.pb.go文件

按同样的步骤在创建一个world。

创建子目录echo，在目录echo中创建一个echo.proto文件，对着exmaples/route_guide/routeguide/route_guide.proto文件抄一个stream模式的定义:

```protobuf
syntax = "proto3";

package echo;

service Echo {
  rpc SayEcho (EchoRequest) returns (EchoReply) {}
  rpc SayEchoS(stream EchoRequest) returns (stream EchoReply) {}
}

message EchoRequest {
  int32 num = 1;
}

message EchoReply {
  string message = 1;
}
```

在目录grpcnotes下执行protoc -I echo/ echo/echo.proto --go_out=plugins=grpc:echo

生成echo.pb.go文件。

按照exmaples/helloworld/greeter_server/main.go的例子抄一个，由于这里有3个protobuf对象，所以代码略有不同：

```go
s := grpc.NewServer(
		grpc.KeepaliveParams(keepalive.ServerParameters{}),
		grpc.MaxConcurrentStreams(10000))
	pb.RegisterHelloServer(s, &serverHello{})
	pb2.RegisterWorldServer(s, &serverWorld{})
	pb3.RegisterEchoServer(s, &serverEcho{})
	// Register reflection service on gRPC server.
	reflection.Register(s)
```

client参考exmaples/helloworld/greeter_client/main.go，增加了并发调用，参数风格参考ab测试

编译服务器程序命名为grpcserver，编译客户端程序命名为grpcclient。

运行 ./grpcserver

运行 ./grpcclient -c 1000 -n 100000

输出

```shell
550 sendokNum: 100 recvokNum 100 sendErrNum: 0 recvErrNum: 0 emptyNum: 0
400 sendokNum: 100 recvokNum 100 sendErrNum: 0 recvErrNum: 0 emptyNum: 0
500 sendokNum: 100 recvokNum 100 sendErrNum: 0 recvErrNum: 0 emptyNum: 0
50 sendokNum: 100 recvokNum 100 sendErrNum: 0 recvErrNum: 0 emptyNum: 0
900 sendokNum: 100 recvokNum 100 sendErrNum: 0 recvErrNum: 0 emptyNum: 0
150 sendokNum: 100 recvokNum 100 sendErrNum: 0 recvErrNum: 0 emptyNum: 0
300 sendokNum: 100 recvokNum 100 sendErrNum: 0 recvErrNum: 0 emptyNum: 0
200 sendokNum: 100 recvokNum 100 sendErrNum: 0 recvErrNum: 0 emptyNum: 0
650 sendokNum: 100 recvokNum 100 sendErrNum: 0 recvErrNum: 0 emptyNum: 0
250 sendokNum: 100 recvokNum 100 sendErrNum: 0 recvErrNum: 0 emptyNum: 0
750 sendokNum: 100 recvokNum 100 sendErrNum: 0 recvErrNum: 0 emptyNum: 0
600 sendokNum: 100 recvokNum 100 sendErrNum: 0 recvErrNum: 0 emptyNum: 0
800 sendokNum: 100 recvokNum 100 sendErrNum: 0 recvErrNum: 0 emptyNum: 0
350 sendokNum: 100 recvokNum 100 sendErrNum: 0 recvErrNum: 0 emptyNum: 0
0 sendokNum: 100 recvokNum 100 sendErrNum: 0 recvErrNum: 0 emptyNum: 0
850 sendokNum: 100 recvokNum 100 sendErrNum: 0 recvErrNum: 0 emptyNum: 0
950 sendokNum: 100 recvokNum 100 sendErrNum: 0 recvErrNum: 0 emptyNum: 0
450 sendokNum: 100 recvokNum 100 sendErrNum: 0 recvErrNum: 0 emptyNum: 0
100 sendokNum: 100 recvokNum 100 sendErrNum: 0 recvErrNum: 0 emptyNum: 0
700 sendokNum: 100 recvokNum 100 sendErrNum: 0 recvErrNum: 0 emptyNum: 0
cost: 3.96848528s
```

