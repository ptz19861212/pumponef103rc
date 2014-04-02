/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 * 2013-07-12     aozima       update for auto initial.
 */

/**
 * @addtogroup STM32
 */
/*@{*/

#include <board.h>
#include <rtthread.h>

#ifdef  RT_USING_COMPONENTS_INIT
#include <components.h>
#endif  /* RT_USING_COMPONENTS_INIT */

#ifdef RT_USING_DFS
/* dfs filesystem:ELM filesystem init */
#include <dfs_elm.h>
/* dfs Filesystem APIs */
#include <dfs_fs.h>
#endif

#ifdef RT_USING_RTGUI
#include <rtgui/rtgui.h>
#include <rtgui/rtgui_server.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/driver.h>
#include <rtgui/calibration.h>
#endif

#include "led.h"

ALIGN(RT_ALIGN_SIZE)
static rt_uint8_t led_stack[ 512 ];
static struct rt_thread led_thread;
static void led_thread_entry(void* parameter)
{
    unsigned int count=0;

    rt_hw_led_init();

    while (1)
    {
        /* led1 on */
#ifndef RT_USING_FINSH
        rt_kprintf("led on, count : %d\r\n",count);
#endif
        count++;
        rt_hw_led_on(0);
        rt_thread_delay( RT_TICK_PER_SECOND/2 ); /* sleep 0.5 second and switch to other thread */

        /* led1 off */
#ifndef RT_USING_FINSH
        rt_kprintf("led off\r\n");
#endif
        rt_hw_led_off(0);
        rt_thread_delay( RT_TICK_PER_SECOND/2 );
    }
}

#ifdef RT_USING_RTGUI
rt_bool_t cali_setup(void)
{
    rt_kprintf("cali setup entered\n");
    return RT_FALSE;
}

void cali_store(struct calibration_data *data)
{
    rt_kprintf("cali finished (%d, %d), (%d, %d)\n",
               data->min_x,
               data->max_x,
               data->min_y,
               data->max_y);
}
#endif /* RT_USING_RTGUI */


#include "key.h"
#include "state.h"
#include "state_detect.h"
#include "display_uc1701.h"
#include "bsp_buzzer.h"
#include "bsp_vibration.h"
#include "bsp_led.h"
#include "bsp_source.h"
#include "bsp_pump.h"
#include "bsp_charge.h"
void BspInit(void)
{
	// 这个必须放在时钟上面，因为要初始化一个信号量给时间中断用
	StateInit();

	// 这个也要放在时钟上面，因为涉及到时间触发ADC
	ADC_Configuration();
	TIM_General_Configuration();

	LedInit();
	BuzzerInit();
	VibrationInit();
	SourceInit();
	PumpInit();
	ChargeInit();

	KEY_Init();
	// LCD 初始化
	DisInit();

	IWDG_Configuration();
}

void rt_init_thread_entry(void* parameter)
{
	// 板子上面的初始化
	BspInit();

#ifdef RT_USING_COMPONENTS_INIT
    /* initialization RT-Thread Components */
    rt_components_init();
#endif

#ifdef  RT_USING_FINSH
    finsh_set_device(RT_CONSOLE_DEVICE_NAME);
#endif  /* RT_USING_FINSH */

    /* Filesystem Initialization */
#if defined(RT_USING_DFS) && defined(RT_USING_DFS_ELMFAT)
//    /* mount spi flash fat as root directory */
//    if (dfs_mount("spi0", "/", "elm", 0, 0) == 0)
//    {
//        rt_kprintf("SPI File System initialized!\n");
//
//        /* mount sd card fat partition 1 as SD directory */
//        if (dfs_mount("sd0", "/SD", "elm", 0, 0) == 0)
//            rt_kprintf("SD File System initialized!\n");
//        else
//            rt_kprintf("SD File System init failed!\n");
//    }
//    else
//    {
//    	rt_kprintf("SPI File System init failed!\n");
//    }

    /* mount sd card fat partition 1 as root directory */
    if (dfs_mount("sd0", "/", "elm", 0, 0) == 0)
    {
        rt_kprintf("File System initialized!\n");
    }
    else
        rt_kprintf("File System initialzation failed!\n");
#endif  /* RT_USING_DFS */

#ifdef RT_USING_RTGUI
    {
        extern void rt_hw_lcd_init();
        extern void rtgui_touch_hw_init(void);

        rt_device_t lcd;

        /* init lcd */
        rt_hw_lcd_init();

        /* init touch panel */
        rtgui_touch_hw_init();

        /* re-init device driver */
        rt_device_init_all();

        /* find lcd device */
        lcd = rt_device_find("lcd");

        /* set lcd device as rtgui graphic driver */
        rtgui_graphic_set_device(lcd);

#ifndef RT_USING_COMPONENTS_INIT
        /* init rtgui system server */
        rtgui_system_server_init();
#endif

        calibration_set_restore(cali_setup);
        calibration_set_after(cali_store);
        calibration_init();
    }
#endif /* #ifdef RT_USING_RTGUI */
}

#include "stm32f10x.h"
//#include "stm32f10x_rcc.h"
//#include "stm32f10x_gpio.h"
//#include "menu_desktop.h"
#include "menu_frame.h"
#include "config_bsp.h"

ALIGN(RT_ALIGN_SIZE)
static rt_uint8_t thread1_stack[ 512 ];
static struct rt_thread thread1;

static void thread1_entry(void *parameter)
{
	rt_err_t result;





	//DEBUG_Printf("display menu desktop ...\n");
	//DisMenuDesk();
	//DEBUG_Printf("display menu desktop done\n");
	//Menufun();
}


/**
 * @brief   待机桌面显示
 */
//void DisMenuDesk(void)
//{
//	//GPIO_InitTypeDef GPIO_InitStructure;
//
//	/* GPIOD Periph clock enable */
//	/*RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);*/
//	/*RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);*/
//	/*RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);*/
//
//	/* Configure PD0 and PD1 or PD3 and PD7 in output pushpull mode */
//	/*GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;*/
//	/*GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;*/
//	/*GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;*/
//	/*GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;*/
//	/*GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;*/
//	/*GPIO_Init(GPIOC, &GPIO_InitStructure);*/
//
//	/*GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;*/
//	/*GPIO_Init(GPIOA, &GPIO_InitStructure);*/
//
//	/*GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;*/
//	/*GPIO_Init(GPIOB, &GPIO_InitStructure);*/
//
//	/*GPIOB->BSRRL = GPIO_Pin_6;*/
//	/*GPIOE->BSRRL = GPIO_Pin_1;*/
//
//	/*while (1)*/
//	/*{*/
//		/*GPIO_ResetBits(GPIOB, GPIO_Pin_6);*/
//		/*GPIO_SetBits(GPIOE, GPIO_Pin_1);*/
//		/*//rt_kprintf("LED1 on\n");*/
//		/*rt_thread_delay(RT_TICK_PER_SECOND);*/
//		/*GPIO_ResetBits(GPIOE, GPIO_Pin_1);*/
//		/*GPIO_SetBits(GPIOB, GPIO_Pin_6);*/
//		/*rt_thread_delay(RT_TICK_PER_SECOND * 3);*/
//		/*//rt_kprintf("LED2 on\n");*/
//
//	/*}*/
//	/*GPIO_SetBits(GPIOA, GPIO_Pin_4);*/
//	/*rt_thread_delay(RT_TICK_PER_SECOND);*/
//	/*GPIO_SetBits(GPIOC, GPIO_Pin_13);*/
//	/*rt_thread_delay(RT_TICK_PER_SECOND);*/
//	/*GPIO_SetBits(GPIOB, GPIO_Pin_0);*/
//	/*rt_thread_delay(RT_TICK_PER_SECOND);*/
//	/*rt_kprintf("Power on\n");*/
//
//	/*UC1701_Init();*/
//
//	DisClr();
//	DisNum16x32(12345, 1, 0, 16);
//	//DisNumSet(12345, 1, 0, 16, 16, 32, 1);
//	//DisCharSet(95, 16, (cFontAscii8x16 + ('%' - 0x20) * (8 >> 3) * 16), 8, 16);
//	//DisCharSet(103, 16, (cFontAscii8x16 + ('L' - 0x20) * (8 >> 3) * 16), 8, 16);
//	//DisCharSet(111, 16, (cFontAscii8x16 + ('E' - 0x20) * (8 >> 3) * 16), 8, 16);
//	//DisCharSet(119, 16, (cFontAscii8x16 + ('L' - 0x20) * (8 >> 3) * 16), 8, 16);
//	//DisUnitSet('L', 95, 16);
//	uint8_t sUnit[5] = "%VOL";
//	DisUnit(sUnit, 95, 32);
//
//	uint8_t sGasName[14] = "C2H12S123O123";
//	DisGasName(sGasName, 0, 48);
//
//	uint8_t sStat[7] = "Detect";
//	DisStat(sStat, 80, 48);
//
//	DisSymCor(0, 0);
//	DisRecRev(0, 0, 12, 9);
//	//DisSymWron(0, 10);
//	uint8_t sAlar[6] = "ALARM";
//	DisSymAlar(sAlar, 52, 0);
//	DisSymAlarRev(52,0);
//	DisSymFan(86, 0);
//	DisSymChar(124, 0);
//	//DisSymBat(0, 59, 0);
//	//DisSymBat(20, 75, 0);
//	//DisSymBat(40, 91, 0);
//	DisSymBat(60, 107, 0);
//	//DisSymBat(80, 0, 10);
//	//DisSymBat(100, 16, 10);
//	//DisSymBat(255, 32, 10);
//	//DisSymCharLar(48, 10);
//	//DisSymFull(81, 10);
//
//
//	//DisRecFillSet(0, 0, 12, 12);
//	//DisCharSet(1, 1, cFontAscii5x10 + ('2' - 0x20) * 10, 5, 10);
//	//DisRecFillSet(2, 2, 3, 3);
//
//	const uint8_t cFontCh[] =
//	{
//		0x04, 0x40, 0x04, 0x44, 0xff, 0xfe, 0x04, 0x40, 0x04, 0x40, 0x04, 0x48,
//		0x3f, 0xfc, 0x02, 0x08, 0x02, 0x08, 0x02, 0x08, 0x02, 0x08, 0x02, 0x48,
//		0x02, 0x30, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00,
//		//0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x80,0x03,0xC0,0x03,0xC0,0x03,0xC0,0x03,0xC0,
//		//0x07,0xE0,0x07,0xE0,0x07,0xE0,0x07,0xE0,0x0E,0x70,0x0E,0x70,0x0E,0x70,0x0E,0x70,
//		//0x1C,0x38,0x1C,0x38,0x1F,0xF8,0x1F,0xF8,0x3F,0xFC,0x38,0x1C,0x38,0x1C,0x38,0x1C,
//		//0x70,0x0E,0x70,0x0E,0x70,0x0E,0x70,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	};
//	//UC1701_CharSet(4, 1, cFontCh, 16, 16);
//	//UC1701_CharSet(4, 0, cFontCh, 16, 32);
//	DisRecSet(0, 0, 127, 63);
//
//	char *lpCh = "H2O";
//	while (*lpCh)
//	{
//		rt_kprintf("xxxxxxx %c\n", *(lpCh++));
//	}
//	rt_kprintf("Init ok\n");
//	/*UC1701_DisAll();*/
//}


//#include "dfs_posix.h"
//ALIGN(RT_ALIGN_SIZE)
//static rt_uint8_t thread2_stack[ 2048 ];
//static struct rt_thread thread2;
//static void thread2_entry(void *parameter)
//{
//	rt_err_t result;
//	int fd, size;
//	DIR *dirp;
//	struct dirent *d;
//	char s[] = "Thread Program File WR:-";
//	char writes [120];
//	static int count = 0;
//	int index;
//
//	char reads[120];
//	int length;
//
//	//memset(reads, 0, sizeof(reads));
//
//	for (index = 0; index < sizeof(s); index++)
//	{
//		writes[index] = s[index];
//	}
//
//
//
//	while (1)
//	{
//		rt_thread_delay(RT_TICK_PER_SECOND);
//
//		int ret;
//		ret = mkdir("/sdcard0", 0x777);
//
//
//		/*
//		struct stat buf;
//		stat("/1234.txt", &buf);
//		rt_kprintf("/1234.txt stat mode: %d \n", buf.st_mode);
//		rt_kprintf("/1234.txt stat size: %d \n", buf.st_size);
//		*/
//
//		/*
//		if (rename("/12345.txt", "/1234.txt") < 0)
//		{
//			rt_kprintf("rename error!\n");
//		}
//		*/
//
//
//		/*rt_kprintf("\n==================================\n");
//
//		sprintf(writes + sizeof(s) - 1, "%08X", count);
//		count++;
//		rt_kprintf("will write: %s \n", writes);
//
//
//		rt_kprintf("Will open /1234.txt for write\n");
//		fd = open("/1234.txt", O_WRONLY | O_TRUNC, 0);
//
//		if (fd < 0)
//		{
//			rt_kprintf("open /1234 for write failed\n");
//			continue;
//		}
//		else
//		{
//			rt_kprintf("open fd = %d for write\n", fd);
//			length = write(fd, writes, strlen(writes));
//			//length = write(fd, s, sizeof(s));
//			//length = write(fd, writes, sizeof(writes));
//
//			if (length != strlen(writes))
//			{
//				rt_kprintf("write failed!\n");
//				close(fd);
//
//				continue;
//			}
//			rt_kprintf("write success!\n");
//
//			close(fd);
//		}
//
//
//
//		rt_kprintf("------------------------------\n");
//		rt_kprintf("Will open /1234.txt for read\n");
//		fd = open("/1234.txt", O_RDONLY, 0);
//
//		if (fd < 0)
//		{
//			rt_kprintf("open /1234 for read failed");
//			continue;
//		}
//		else
//		{
//			rt_kprintf("open fd = %d for read\n", fd);
//
//			length = read(fd, reads, sizeof(reads) - 1);
//			rt_kprintf("read length = %d\n", length);
//
//			reads[length] = 0;
//
//
//			rt_kprintf("read: %s\n", reads);
//
//			close(fd);
//		}
//		*/
//
//
//
//
//		rt_kprintf("Will find / \n");
//		dirp = opendir("/");
//		if (dirp == RT_NULL)
//		{
//			rt_kprintf("open direct error! \n");
//		}
//		else
//		{
//			while ((d = readdir(dirp)) != RT_NULL)
//			{
//				rt_kprintf("found %s \n", d->d_name);
//			}
//		}
//
//		closedir(dirp);
//
//
//
//	}
//}
//
//ALIGN(RT_ALIGN_SIZE)
//static rt_uint8_t thread3_stack[ 2048 ];
//static struct rt_thread thread3;
//volatile uint32_t dma_end = 1;
//static void thread3_entry(void *parameter)
//{
//	rt_err_t result;
//
//	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
//
//	NVIC_InitTypeDef NVIC_InitStructure;
//	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel6_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
//
//	uint32_t dma_bufsize = 9;
//	uint32_t dma_src[] = {123, 456, 789, 1123, 1456, 1789, 2123, 2456, 2789};
//	uint32_t dma_dst[dma_bufsize];
//
//	DMA_InitTypeDef DMA_InitStructure;
//	DMA_DeInit(DMA1_Channel6);
//	DMA_InitStructure.DMA_PeripheralBaseAddr = (rt_uint32_t)dma_src;
//	DMA_InitStructure.DMA_MemoryBaseAddr = (rt_uint32_t)dma_dst;
//	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
//	DMA_InitStructure.DMA_BufferSize = dma_bufsize;
//	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
//	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
//	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
//	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
//	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
//	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
//	DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;
//	DMA_Init(DMA1_Channel6, &DMA_InitStructure);
//
//	DMA_ITConfig(DMA1_Channel6, DMA_IT_TC, ENABLE);
//	DMA_Cmd(DMA1_Channel6, ENABLE);
//
//	while (dma_end != 0)
//	{
//
//	}
//
//	uint32_t i = 0;
//	for (; i < dma_bufsize; i++)
//	{
//		rt_kprintf("DMA1_Channel6 = %d\n", dma_dst[i]);
//	}
//
//
//}
//
//void DMA1_Channel6_IRQHandler(void)
//{
//  /* Test on DMA1 Channel6 Transfer Complete interrupt */
//  if(DMA_GetITStatus(DMA1_IT_TC6))
//  {
//    /* Get Current Data Counter value after complete transfer */
//    dma_end = DMA_GetCurrDataCounter(DMA1_Channel6);
//    /* Clear DMA1 Channel6 Half Transfer, Transfer Complete and Global interrupt pending bits */
//    DMA_ClearITPendingBit(DMA1_IT_GL6);
//  }
//}

#include "my_define.h"
#include <stdint.h>
#include "bubble_sort.h"
ALIGN(RT_ALIGN_SIZE)
static rt_uint8_t thread_adc_stack[ 2048 ];
static struct rt_thread thread_adc;
//volatile uint32_t dma_end = 1;
static void thread_adc_entry(void *parameter)
{
	rt_err_t result;

//	uint16_t lgas, lbat, lv1, lv2;
//	uint16_t *lRef1, *lRef2;

	static uint16_t sAdcGas[2];
	uint16_t *lpAdcBuf;
	uint32_t lAdcBufSize;
	uint16_t lAdcGas, lAdcBat, lAdcCharge, lAdcTmp;
	my_err_t lErr;
	S_Gas* lpGas;
	S_Device* lpDev;

	// 获得气体结构体指针
	StateGasPointGet(&lpGas);
	// 获得设备结构体指针
	StateDevicePointGet(&lpDev);

	// 设置滑动求平均的数组地址和长度
	AverageMoveSetU16(sAdcGas,
						sizeof(sAdcGas) / sizeof(sAdcGas[0]));

	while (1)
	{
		AdcWait();
		AdcSuspend();

		// 获得气体adc数组的地址和长度
		lErr = AdcBufGet(0, &lpAdcBuf, &lAdcBufSize);
		// 获得这个时候对应的参考电压的adc数组的地址
		//AdcRefBufGet(&lRef1);

//		lv1 = *lRef1;
//		lgas = *lBuf1;
//		rt_kprintf("lv1 = %d  lgas = %d \n", lv1, lgas);
//		rt_kprintf("lv1 = %d  lgas = %d \t", lv1, lgas);

//		rt_kprintf("old %d %d %d %d %d %d %d %d %d \n",
//				*(lBuf1 + 60), *(lBuf1 + 61), *(lBuf1 + 62),
//				*(lBuf1 + 63), *(lBuf1 + 64), *(lBuf1 + 65),
//				*(lBuf1 + 66), *(lBuf1 + 67), *(lBuf1 + 68));
//		rt_kprintf("gas = %d\t", *lpAdcBuf);

		// 对气体adc数组进行冒泡排序
		BubbleSortU16(lpAdcBuf, lAdcBufSize);

//		rt_kprintf("new %d %d %d %d %d %d %d %d %d \n",
//				*(lBuf1 + 60), *(lBuf1 + 61), *(lBuf1 + 62),
//				*(lBuf1 + 63), *(lBuf1 + 64), *(lBuf1 + 65),
//				*(lBuf1 + 66), *(lBuf1 + 67), *(lBuf1 + 68));
//		BubbleSortU16(lRef1, 128);
//		rt_kprintf("avg = %d ref = %d \n", AverageU16(lBuf1 + 32, 64),
//					AverageU16(lRef1 + 32, 64));

		// 从数组的 1/4 处开始处理 1/2 数目的平均值
		lAdcTmp = AverageU16(lpAdcBuf + (lAdcBufSize >> 2), (lAdcBufSize >> 1));

//		rt_kprintf("gas = %d\t", lAdcTmp);

		// 对气体adc求滑动平均
		lAdcGas = AverageMoveU16(lAdcTmp);
		lpGas->pTemp->Point.Adc = lAdcGas;

//		rt_kprintf("size = %d\t tmp = %d\t gas = %d\n", lAdcBufSize, lAdcTmp,
//					lAdcGas);

		// bat adc
		lErr = AdcBufGet(1, &lpAdcBuf, &lAdcBufSize);
		lAdcTmp = AverageU16(lpAdcBuf, lAdcBufSize);
		lpDev->pTemp->Bat.Point.Adc = lAdcTmp;

//		rt_kprintf("bat = %d\t", lAdcTmp);

//		rt_kprintf("bat = %d\t", *lpAdcBuf);

		// charge adc
		lErr = AdcBufGet(2, &lpAdcBuf, &lAdcBufSize);
		lAdcTmp = AverageU16(lpAdcBuf, lAdcBufSize);
		lpDev->pTemp->Charge.Adc = lAdcTmp;

//		rt_kprintf("charge = %d\n", *lpAdcBuf);



//		lErr = AdcBufGet(1, &lBuf2, &lSize);
//		AdcRefBufGet(&lRef2);
//		lv2 = *lRef2;
//		lbat = *lBuf2;
//		rt_kprintf("lv2 = %d  lbat = %d \n", lv2, lbat);
//
		AdcResume();
//
//		GPIO_SetBits(GPIOA, GPIO_Pin_1);


	}
}

ALIGN(RT_ALIGN_SIZE)
static rt_uint8_t thread_state_stack[ 2048 ];
static struct rt_thread thread_state;

static void thread_state_entry(void *parameter)
{
	rt_err_t result;

	StateTrans();
}

//ALIGN(RT_ALIGN_SIZE)
//static rt_uint8_t thread_key_stack[ 512 ];
//static struct rt_thread thread_key;
//
//static void thread_key_entry(void *parameter)
//{
//	rt_err_t result;
//
//	static uint8_t sKkey = 0;
//	while (1)
//	{
//		KEY_Get();
//	}
//}


int rt_application_init(void)
{
    rt_thread_t init_thread;

    rt_err_t result;

    /* init led thread */
//    result = rt_thread_init(&led_thread,
//                            "led",
//                            led_thread_entry,
//                            RT_NULL,
//                            (rt_uint8_t*)&led_stack[0],
//                            sizeof(led_stack),
//                            20,
//                            5);
//    if (result == RT_EOK)
//    {
//        rt_thread_startup(&led_thread);
//    }

#if (RT_THREAD_PRIORITY_MAX == 32)
    init_thread = rt_thread_create("init",
                                   rt_init_thread_entry, RT_NULL,
                                   2048, 8, 20);
#else
    init_thread = rt_thread_create("init",
                                   rt_init_thread_entry, RT_NULL,
                                   2048, 80, 20);
#endif

    if (init_thread != RT_NULL)
        rt_thread_startup(init_thread);




	result = rt_thread_init(&thread1, "thread1", thread1_entry,
								RT_NULL, &thread1_stack[0],
								sizeof(thread1_stack), 9, 10);
	if (result == RT_EOK)
		rt_thread_startup(&thread1);
	else
	{
		return -1;
	}

/*	result = rt_thread_init(&thread2, "thread2", thread2_entry,
								RT_NULL, &thread2_stack[0],
								sizeof(thread2_stack), 9, 10);
	if (result == RT_EOK)
		rt_thread_startup(&thread2);
	else
	{
		return -1;
	}*/

//	result = rt_thread_init(&thread3, "thread3", thread3_entry,
//									RT_NULL, &thread3_stack[0],
//									sizeof(thread3_stack), 9, 10);
//	if (result == RT_EOK)
//		rt_thread_startup(&thread3);
//	else
//	{
//		return -1;
//	}

	result = rt_thread_init(&thread_adc, "thread_adc", thread_adc_entry,
									RT_NULL, &thread_adc_stack[0],
									sizeof(thread_adc_stack), 9, 10);
	if (result == RT_EOK)
		rt_thread_startup(&thread_adc);
	else
	{
		return -1;
	}

	result = rt_thread_init(&thread_state, "thread_state", thread_state_entry,
								RT_NULL, &thread_state_stack[0],
								sizeof(thread_state_stack), 10, 30);
	if (result == RT_EOK)
		rt_thread_startup(&thread_state);
	else
	{
		return -1;
	}

//	result = rt_thread_init(&thread_key, "thread_key", thread_key_entry,
//								RT_NULL, &thread_key_stack[0],
//								sizeof(thread_key_stack), 9, 10);
//	if (result == RT_EOK)
//		rt_thread_startup(&thread_key);
//	else
//	{
//		return -1;
//	}

    return 0;



}

/*@}*/
