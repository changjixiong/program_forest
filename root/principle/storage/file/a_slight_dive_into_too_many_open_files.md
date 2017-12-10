# 关于too many open files的一点深究

今天在gocn上看到一个问题https://gocn.io/question/1391，题主问为啥运行到打开1000多个文件的时候就会报错，提示too many open files。关于这段代码本身的错误，我已经在回帖中回复了，这里不再赘述。这里我主要想对相关问题稍微做一点深入的讨论，毕竟关于文件和文件描述符相关的问题，几乎是每个程序员都会碰到的问题，然而却很少人真的会去搞清楚问题的背后究竟是什么原理。

假设有这样一段代码

```go
func main() {
  	input := ""
	fmt.Scanln(&input)
	for i := 0; ; i++ {
		_, err := os.OpenFile("data.txt", os.O_RDWR|os.O_CREATE, os.ModePerm)

		if err != nil {
			fmt.Println("OpenFile i:", i, err)
			return
		}
	}
}
```

程序运行起来，在键入回车后会输出：

```shell
OpenFile i: 1021 open data.txt: too many open files
```

如果在网上搜索too many open files，会找到无数的文章，里面会提到如何将系统设定的最大打开文件数从1024修改为一个很大的数字。

不过这里会有一个问题，既然最大限制是1024，为啥这里1021就提示错误了？

在回答这个问题之前，再次运行一下上面那段程序，这次不做任何输入，另外开一个终端找到这个程序的进程ID假设是9527，运行

```shell
ls /proc/9527/fd
```

会看到结果 0 1 2，这3个就是大家不能更熟悉的stdin、stdout、stderr，所以程序在初始化以后就已经打开了3个文件，那么在1024的限制了还能打开1021个，i从0开始计数，于是当i计数到1021的时候，就是在尝试打开第1025个文件，所以失败了。这下是不是将标准输入输出与文件的知识关联起来更好理解了？

至于如何将1024的限制修改为更大，这个网上有太多太多的文章，这里就不在赘述。