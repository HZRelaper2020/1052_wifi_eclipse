# eclipse的wifi程序，调用ubunt端生成的.a文件

### lwip库的修改 
* lwip/core/tcp_out.c 262 pbuf_alloc(2+layer...)  增加2
* lwip/core/tcp_out.c 1076  pbuf_alloc(2+PBUF_TRANSPORT, optlen, PBUF_RAM))  增加2
* lwip/core/tcp_out.c 1825  pbuf_alloc(2+PBUF_IP..)  增加2
* ipip/core/ipv4/etharp.c 1114   pbuf_alloc(30+PBUF_LINK...) 增加 30

### 测试
1. 8字符连续发送半天，看数据是否有误
2. 4000降低连续发送半天，看数据是否有误
