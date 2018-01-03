# start-a-nsq

nsqlookupd -tcp-address=0.0.0.0:4160 -http-address=0.0.0.0:4161

nsqd -data-path=/data/logs/nsqlog -broadcast-address=127.0.0.1 -tcp-address=0.0.0.0:4150 -http-address=0.0.0.0:4151 -verbose=true -lookupd-tcp-address=127.0.0.1:4160

nsqadmin -http-address=0.0.0.0:4171 -lookupd-http-address=127.0.0.1:4161

http://IP:4171/