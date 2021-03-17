/**
  ******************************************************************************
  * @file:      bsp_can.c
  * @author:    孙关平
  * @version:   V1.0
  * @date:      2020-11-4
  * @brief:     stm8a CAN硬件ID过滤驱动，支持设置扩展ID或标准ID过滤
  * @attention: 1、stm8a的CAN模块支持硬件过滤ID，设置过滤ID后，只有收到符合要求的ID报文
  *                 才会触发CAN接收中断。
  *             2、stm8a的CAN模块共有6组过滤器，CAN_FilterNumber_0到CAN_FilterNumber_5，
  *                 每组过滤器都是64bit大小
  *             3、每组过滤器在CAN_FilterMode_IdList模式下，可以过滤2个扩展ID，因此
  *                 总共可以过滤12个扩展ID
  *             4、每组过滤器在CAN_FilterMode_IdList模式下，可以过滤4个标准ID，因此
  *                 总共可以过滤24个标准ID
  *             5、由于项目原因无法分享整个工程，只能分享过滤ID部分的代码，有问题欢迎提出
  ******************************************************************************
  */


#include "./bsp_can.h"


/**
  * @brief  关闭所有过滤器
  * @param  无
  * @retval 无
  * @attention
  */
void can_id_filter_all_disable(void)
{
    CAN_FilterNumber_TypeDef CAN_FilterNumber;
    FunctionalState CAN_FilterActivation;
    CAN_FilterMode_TypeDef CAN_FilterMode;
    CAN_FilterScale_TypeDef CAN_FilterScale;
    uint8_t CAN_FilterID1;
    uint8_t CAN_FilterID2;
    uint8_t CAN_FilterID3;
    uint8_t CAN_FilterID4;
    uint8_t CAN_FilterIDMask1;
    uint8_t CAN_FilterIDMask2;
    uint8_t CAN_FilterIDMask3;
    uint8_t CAN_FilterIDMask4;

    //printf("can_id_filter_all_disable \r\n");

    CAN_FilterNumber = CAN_FilterNumber_0;//指定了待初始化的过滤器0
    CAN_FilterActivation = ENABLE;
    CAN_FilterMode = CAN_FilterMode_IdMask;//指定了过滤器将被初始化到的模式为标识符屏蔽位模式
    CAN_FilterScale = CAN_FilterScale_32Bit;//给出了过滤器位宽1个32位过滤器
    CAN_FilterID1 = 0;
    CAN_FilterID2 = 0;
    CAN_FilterID3 = 0;
    CAN_FilterID4 = 0;
    CAN_FilterIDMask1 = 0;
    CAN_FilterIDMask2 = 0;
    CAN_FilterIDMask3 = 0;
    CAN_FilterIDMask4 = 0;
    CAN_FilterInit(CAN_FilterNumber, CAN_FilterActivation, CAN_FilterMode,
                   CAN_FilterScale, CAN_FilterID1, CAN_FilterID2, CAN_FilterID3,
                   CAN_FilterID4, CAN_FilterIDMask1, CAN_FilterIDMask2,
                   CAN_FilterIDMask3, CAN_FilterIDMask4);
    CAN_FilterNumber = CAN_FilterNumber_1;//指定了待初始化的过滤器1
    CAN_FilterInit(CAN_FilterNumber, CAN_FilterActivation, CAN_FilterMode,
                   CAN_FilterScale, CAN_FilterID1, CAN_FilterID2, CAN_FilterID3,
                   CAN_FilterID4, CAN_FilterIDMask1, CAN_FilterIDMask2,
                   CAN_FilterIDMask3, CAN_FilterIDMask4);
    CAN_FilterNumber = CAN_FilterNumber_2;//指定了待初始化的过滤器2
    CAN_FilterInit(CAN_FilterNumber, CAN_FilterActivation, CAN_FilterMode,
                   CAN_FilterScale, CAN_FilterID1, CAN_FilterID2, CAN_FilterID3,
                   CAN_FilterID4, CAN_FilterIDMask1, CAN_FilterIDMask2,
                   CAN_FilterIDMask3, CAN_FilterIDMask4);
    CAN_FilterNumber = CAN_FilterNumber_3;//指定了待初始化的过滤器3
    CAN_FilterInit(CAN_FilterNumber, CAN_FilterActivation, CAN_FilterMode,
                   CAN_FilterScale, CAN_FilterID1, CAN_FilterID2, CAN_FilterID3,
                   CAN_FilterID4, CAN_FilterIDMask1, CAN_FilterIDMask2,
                   CAN_FilterIDMask3, CAN_FilterIDMask4);
    CAN_FilterNumber = CAN_FilterNumber_4;//指定了待初始化的过滤器4
    CAN_FilterInit(CAN_FilterNumber, CAN_FilterActivation, CAN_FilterMode,
                   CAN_FilterScale, CAN_FilterID1, CAN_FilterID2, CAN_FilterID3,
                   CAN_FilterID4, CAN_FilterIDMask1, CAN_FilterIDMask2,
                   CAN_FilterIDMask3, CAN_FilterIDMask4);
    CAN_FilterNumber = CAN_FilterNumber_5;//指定了待初始化的过滤器5
    CAN_FilterInit(CAN_FilterNumber, CAN_FilterActivation, CAN_FilterMode,
                   CAN_FilterScale, CAN_FilterID1, CAN_FilterID2, CAN_FilterID3,
                   CAN_FilterID4, CAN_FilterIDMask1, CAN_FilterIDMask2,
                   CAN_FilterIDMask3, CAN_FilterIDMask4);
}

#ifdef CAN_ID_FILTER_EXTEND
/**
  * @brief  对扩展id（用32bit来存储29bit ID）进行设置过滤，如果num传入为0表示关闭过滤
  * @param  无
  * @retval 无
  * @attention
  */
void can_ext_id_filter(uint32_t *id, uint8_t num)
{
    /* 滤波器参数设置 */
    CAN_FilterNumber_TypeDef CAN_FilterNumber;
    FunctionalState CAN_FilterActivation;
    CAN_FilterMode_TypeDef CAN_FilterMode;
    CAN_FilterScale_TypeDef CAN_FilterScale;
    uint8_t CAN_FilterID1;
    uint8_t CAN_FilterID2;
    uint8_t CAN_FilterID3;
    uint8_t CAN_FilterID4;
    uint8_t CAN_FilterIDMask1;
    uint8_t CAN_FilterIDMask2;
    uint8_t CAN_FilterIDMask3;
    uint8_t CAN_FilterIDMask4;
    uint8_t i;
    uint8_t group;
    uint32_t temp;
    uint32_t temp_id[2 * (CAN_FilterNumber_5 + 1)];

    /* 共有6组过滤器，CAN_FilterNumber_0到CAN_FilterNumber_5，每组过滤器
    在CAN_FilterMode_IdList模式下，可以过滤2个扩展ID，因此总共可以过滤12个扩展ID */
    if (num > (2 * (CAN_FilterNumber_5 + 1))) return;

    if (0 == id) return;

    if (0 == num) { /* 关闭所有过滤 */
        can_id_filter_all_disable();
    } else {        /* 开启过滤，根据需求开启过滤器0到过滤器5 */
        memset((void *)temp_id, 0x00, sizeof(temp_id));

        if (num % 2 == 0) {
            group = num / 2;
            memcpy((void *)temp_id, (void *)id, num * 4);
        } else {
            group = num / 2 + 1;
            memcpy((void *)temp_id, (void *)id, (num + 1) * 4);
        }

        for (i = 0; i < group; i++) {
            CAN_FilterNumber = (CAN_FilterNumber_TypeDef)i; /* 指定了待初始化的过滤器0 */
            CAN_FilterActivation = ENABLE;
            //CAN_FilterMode = CAN_FilterMode_IdMask; /* 指定了过滤器将被初始化到的模式为标识符屏蔽位模式 */
            CAN_FilterMode = CAN_FilterMode_IdList;
            CAN_FilterScale = CAN_FilterScale_32Bit;/* 给出了过滤器位宽1个32位过滤器 */
            printf("can id[0x%lx] ", temp_id[i * 2]);
            temp = 0x11e00000 & (temp_id[i * 2] << 3);
            temp = temp | 0x00080000;   /* IDE = 1 表示扩展的id */
            temp_id[i * 2] = 0x0003fffe & (temp_id[i * 2] << 1);
            temp = temp | temp_id[i * 2];
            printf("using filter[%d] = %08lx \r\n", i, temp);
            CAN_FilterID1 = (uint8_t)(temp >> 24);
            CAN_FilterID2 = (uint8_t)(temp >> 16);
            CAN_FilterID3 = (uint8_t)(temp >> 8);
            CAN_FilterID4 = (uint8_t)temp;

            printf("can id[0x%lx] ", temp_id[i * 2 + 1]);
            temp = 0x11e00000 & (temp_id[i * 2 + 1] << 3);
            temp = temp | 0x00080000;   /* IDE = 1 表示扩展的id */
            temp_id[i * 2 + 1] = 0x0003fffe & (temp_id[i * 2 + 1] << 1);
            temp = temp | temp_id[i * 2 + 1];
            printf("using filter[%d] = %08lx \r\n", i, temp);
            CAN_FilterIDMask1 = (uint8_t)(temp >> 24);
            CAN_FilterIDMask2 = (uint8_t)(temp >> 16);
            CAN_FilterIDMask3 = (uint8_t)(temp >> 8);
            CAN_FilterIDMask4 = (uint8_t)temp;

            CAN_FilterInit(CAN_FilterNumber, CAN_FilterActivation, CAN_FilterMode,
                           CAN_FilterScale, CAN_FilterID1, CAN_FilterID2, CAN_FilterID3,
                           CAN_FilterID4, CAN_FilterIDMask1, CAN_FilterIDMask2,
                           CAN_FilterIDMask3, CAN_FilterIDMask4);
        }
    }
}
#else
/**
  * @brief  对标准id（用16bit来存储11bit ID）进行设置过滤，如果num传入为0表示关闭过滤
  * @param  无
  * @retval 无
  * @attention
  */
void can_std_id_filter(uint16_t *id, uint8_t num)
{
    /* 滤波器参数设置 */
    CAN_FilterNumber_TypeDef CAN_FilterNumber;
    FunctionalState CAN_FilterActivation;
    CAN_FilterMode_TypeDef CAN_FilterMode;
    CAN_FilterScale_TypeDef CAN_FilterScale;
    uint8_t CAN_FilterID1;
    uint8_t CAN_FilterID2;
    uint8_t CAN_FilterID3;
    uint8_t CAN_FilterID4;
    uint8_t CAN_FilterIDMask1;
    uint8_t CAN_FilterIDMask2;
    uint8_t CAN_FilterIDMask3;
    uint8_t CAN_FilterIDMask4;
    uint8_t i;
    uint8_t group;
    uint16_t temp_id[4 * (CAN_FilterNumber_5 + 1)];

    /* 共有6组过滤器，CAN_FilterNumber_0到CAN_FilterNumber_5，每组过滤器
    在CAN_FilterMode_IdList模式下，可以过滤4个标准ID，因此总共可以过滤24个标准ID */
    if (num > (4 * (CAN_FilterNumber_5 + 1))) return;

    if (0 == id) return;

    if (0 == num) { /* 关闭所有过滤 */
        can_id_filter_all_disable();
    } else {        /* 开启过滤，根据需求开启过滤器0到过滤器5 */
        memset((void *)temp_id, 0x00, sizeof(temp_id));

        if (num % 4 == 0) {
            group = num / 4;
        } else {
            group = num / 4 + 1;
        }

        memcpy((void *)temp_id, (void *)id, 2 * num);

        for (i = 0; i < group; i++) {
            CAN_FilterNumber = (CAN_FilterNumber_TypeDef)i; /* 指定了待初始化的过滤器0 */
            CAN_FilterActivation = ENABLE;
            //CAN_FilterMode = CAN_FilterMode_IdMask; /* 指定了过滤器将被初始化到的模式为标识符屏蔽位模式 */
            CAN_FilterMode = CAN_FilterMode_IdList;
            CAN_FilterScale = CAN_FilterScale_16Bit;/* 给出了过滤器位宽1个16位过滤器 */
            printf("using filter[%d]: id[0x%x] id[0x%x] id[0x%x] id[0x%x] \r\n",
                   i, temp_id[i * 4], temp_id[i * 4 + 1], temp_id[i * 4 + 2], temp_id[i * 4 + 3]);
            CAN_FilterID1 = (uint8_t)(temp_id[i * 4] >> 3);
            CAN_FilterID2 = (uint8_t)temp_id[i * 4] << 5;
            CAN_FilterID3 = (uint8_t)(temp_id[i * 4 + 1] >> 3);
            CAN_FilterID4 = (uint8_t)temp_id[i * 4 + 1] << 5;
            CAN_FilterIDMask1 = (uint8_t)(temp_id[i * 4 + 2] >> 3);
            CAN_FilterIDMask2 = (uint8_t)temp_id[i * 4 + 2] << 5;
            CAN_FilterIDMask3 = (uint8_t)(temp_id[i * 4 + 3] >> 3);
            CAN_FilterIDMask4 = (uint8_t)temp_id[i * 4 + 3] << 5;

            CAN_FilterInit(CAN_FilterNumber, CAN_FilterActivation, CAN_FilterMode,
                           CAN_FilterScale, CAN_FilterID1, CAN_FilterID2, CAN_FilterID3,
                           CAN_FilterID4, CAN_FilterIDMask1, CAN_FilterIDMask2,
                           CAN_FilterIDMask3, CAN_FilterIDMask4);
        }
    }
}
#endif

/**
  * @brief  初始化can，并对id进行设置过滤，如果num传入为0表示关闭过滤
  * @param  无
  * @retval 无
  * @attention
  */
#ifdef CAN_ID_FILTER_EXTEND
    CAN_InitStatus_TypeDef can_gpio_init(uint32_t *filter_id, uint8_t num)
#else
    CAN_InitStatus_TypeDef can_gpio_init(uint16_t *filter_id, uint8_t num)
#endif
{
    CAN_InitStatus_TypeDef status = CAN_InitStatus_Failed;

    /* 初始化CAN参数 */
    CAN_MasterCtrl_TypeDef CAN_MasterCtrl;
    CAN_Mode_TypeDef CAN_Mode;
    CAN_SynJumpWidth_TypeDef CAN_SynJumpWidth;
    CAN_BitSeg1_TypeDef CAN_BitSeg1;
    CAN_BitSeg2_TypeDef CAN_BitSeg2;
    uint8_t CAN_Prescaler;

    /* CAN 初始化默认值 ------------------------------------------------------ */
    CAN_DeInit();

    /* CAN 初始化参数配置 -----------------------------------------------------*/
    CAN_MasterCtrl = CAN_MasterCtrl_AllDisabled;
    CAN_Mode = CAN_Mode_Normal;             /* 设置工作在正常模式 */
    //CAN_Mode = CAN_Mode_LoopBack;           /* 设置工作在回环模式，可用于测试 */
    CAN_SynJumpWidth = CAN_SynJumpWidth_1TimeQuantum;
    CAN_BitSeg1 = CAN_BitSeg1_8TimeQuantum; /* 第1段里占8个时间单元 */
    CAN_BitSeg2 = CAN_BitSeg2_7TimeQuantum; /* 第2段里占7个时间单元 */

    /* 波特率 24Mhz/6/(1 + 8 + 7) = 250k */
    //CAN_Prescaler = 6;                      /* 波特率分频率  定义时间单元的时间长度 */

    /* 波特率 24Mhz/3/(1 + 8 + 7) = 500k */
    CAN_Prescaler = 3;                      /* 波特率分频率  定义时间单元的时间长度 */

    status = CAN_Init(CAN_MasterCtrl, CAN_Mode, CAN_SynJumpWidth, CAN_BitSeg1, \
                      CAN_BitSeg2, CAN_Prescaler);    /* 设置CAN模式 */

#ifdef CAN_ID_FILTER_EXTEND
    /* 设置过滤CAN 扩展ID -----------------------------------------------------*/
    can_ext_id_filter(filter_id, num);
#else
    /* 设置过滤CAN 标准ID -----------------------------------------------------*/
    can_std_id_filter(filter_id, num);
#endif

    /* Enable Fifo message pending interrupt*/
    /* Message reception is done by CAN_RX ISR*/
    CAN_ITConfig(CAN_IT_FMP, ENABLE);
    return status;
}


/*********************************************END OF FILE**********************/
