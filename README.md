# stm8a_can_id_hardware_filter
---
### stm8a_can_id_hardware_filter（stm8a CAN ID硬件过滤）

1、stm8a的CAN模块支持硬件过滤ID，设置过滤ID后，只有收到符合要求的ID报文才会触发CAN接收中断。当can总线的报文非常多的时候，开启硬件ID过滤可以减轻cpu的压力。
2、stm8a的CAN模块共有6组过滤器，CAN_FilterNumber_0到CAN_FilterNumber_5，每组过滤器都是64bit大小。
3、每组过滤器在CAN_FilterMode_IdList模式下，可以过滤2个扩展ID，因此总共可以过滤12个扩展ID。
4、每组过滤器在CAN_FilterMode_IdList模式下，可以过滤4个标准ID，因此总共可以过滤24个标准ID。
5、由于项目原因无法分享整个工程，只能分享过滤ID部分的代码，有问题欢迎提出。