# -

基于Tcmalloc，设计实现的内存池，可以支持高并发，可以解决小块内存不断申请，内存碎片问题
申请低于128K的内存比系统提供的malloc快1.5倍
