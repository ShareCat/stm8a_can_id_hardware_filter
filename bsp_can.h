/**
  ******************************************************************************
  * @file:      bsp_can.h
  * @author:    孙关平
  * @version:   V1.0
  * @date:      2020-11-4
  * @brief:     stm8a CAN硬件ID过滤驱动，支持设置扩展ID或标准ID过滤
  * @attention: 1、stm8a的CAN模块支持硬件过滤ID，设置过滤ID后，只有收到符合要求的ID报文
  *                 才会触发CAN接收中断。当can总线的报文非常多的时候，开启硬件ID过滤
  *                 可以减轻cpu的压力。
  *             2、stm8a的CAN模块共有6组过滤器，CAN_FilterNumber_0到CAN_FilterNumber_5，
  *                 每组过滤器都是64bit大小
  *             3、每组过滤器在CAN_FilterMode_IdList模式下，可以过滤2个扩展ID，因此
  *                 总共可以过滤12个扩展ID
  *             4、每组过滤器在CAN_FilterMode_IdList模式下，可以过滤4个标准ID，因此
  *                 总共可以过滤24个标准ID
  *             5、由于项目原因无法分享整个工程，只能分享过滤ID部分的代码，有问题欢迎提出
  ******************************************************************************
  */


#ifndef __BSP_CAN_H
#define __BSP_CAN_H


#include "./../lib/inc/stm8s_can.h"


//#define CAN_ID_FILTER_EXTEND    /* 注释掉表示标准ID过滤，取消注释表示扩展ID过滤 */

#ifdef CAN_ID_FILTER_EXTEND
    CAN_InitStatus_TypeDef can_gpio_init(uint32_t *filter_id, uint8_t num);
#else
    CAN_InitStatus_TypeDef can_gpio_init(uint16_t *filter_id, uint8_t num);
#endif


#endif /* __BSP_CAN_H */
