# eclipse的wifi程序，调用ubunt端生成的.a文件

### 存在的问题
* 通信速度慢，才0.05M/s
* 无法加入 test_rk3288 网络
* 加入 Relaper-H3C-2.4G 时,pbuf_free 有时会报错 "Assertion "pbuf_free: p->ref > 0" failed at line 760 in ../lwip/core/pbuf.c"
* 加入 Relaper-H3C-2.4G 时，有时会报错 "pbuf alloc failed"

### lwip库的修改 
* lwip/core/tcp_out.c 262 pbuf_alloc(2+layer...)  增加2
* lwip/core/tcp_out.c 1076  pbuf_alloc(2+PBUF_TRANSPORT, optlen, PBUF_RAM))  增加2
* lwip/core/tcp_out.c 1825  pbuf_alloc(2+PBUF_IP..)  增加2
* ipip/core/ipv4/etharp.c 1114   pbuf_alloc(30+PBUF_LINK...) 增加 30

### 测试
1. 8字符连续发送半天，看数据是否有误
2. 4000降低连续发送半天，看数据是否有误
