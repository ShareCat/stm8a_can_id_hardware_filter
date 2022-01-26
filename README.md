# stm8a_can_id_hardware_filter
---
### stm8a_can_id_hardware_filter（stm8a CAN ID硬件过滤）

- stm8a的CAN模块支持硬件过滤ID，设置过滤ID后，只有收到符合要求的ID报文才会触发CAN接收中断。当can总线的报文非常多的时候，开启硬件ID过滤可以减轻cpu的压力。

- stm8a的CAN模块共有6组过滤器，CAN_FilterNumber_0到CAN_FilterNumber_5，每组过滤器都是64bit大小。

- 每组过滤器在CAN_FilterMode_IdList模式下，可以过滤2个扩展ID，因此总共可以过滤12个扩展ID。

- 每组过滤器在CAN_FilterMode_IdList模式下，可以过滤4个标准ID，因此总共可以过滤24个标准ID。

- 由于项目原因无法分享整个工程，只能分享过滤ID部分的代码，有问题欢迎提出。

### Demo
```cpp
/**
 * @brief  can_init
 * @param  None
 * @retval None
 */
void can_init(void)
{
#ifdef CAN_ID_FILTER_EXTEND
    uint32_t test_id_list[] = {0x436, 0x4c9, 0X09c, 0x17d, 0x1f1, 0x140, 0x1e5, 0x53b, 0x120, 0x430};
    can_gpio_init(test_id_list, sizeof(test_id_list) / sizeof(uint32_t));
#else
    uint16_t test_id_list[] = {0x436, 0x4c9, 0X09c, 0x17d, 0x1f1, 0x140, 0x1e5, 0x53b, 0x120, 0x430};
    can_gpio_init(test_id_list, sizeof(test_id_list) / sizeof(uint16_t));
#endif
}
```
