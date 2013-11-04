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

void rt_init_thread_entry(void* parameter)
{
#ifdef RT_USING_COMPONENTS_INIT
    /* initialization RT-Thread Components */
    rt_components_init();
#endif

#ifdef  RT_USING_FINSH
    finsh_set_device(RT_CONSOLE_DEVICE_NAME);
#endif  /* RT_USING_FINSH */

    /* Filesystem Initialization */
#if defined(RT_USING_DFS) && defined(RT_USING_DFS_ELMFAT)
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
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "uc1701.h"
#include "display_uc1701.h"
#include "font_ascii.h"
#include "font_symbol.h"

ALIGN(RT_ALIGN_SIZE)
static rt_uint8_t thread1_stack[ 512 ];
static struct rt_thread thread1;

static void thread1_entry(void *parameter)
{
	rt_err_t result;
	GPIO_InitTypeDef GPIO_InitStructure;

	/* GPIOD Periph clock enable */
	/*RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);*/
	/*RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);*/
	/*RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);*/

	/* Configure PD0 and PD1 or PD3 and PD7 in output pushpull mode */
	/*GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;*/
	/*GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;*/
	/*GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;*/
	/*GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;*/
	/*GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;*/
	/*GPIO_Init(GPIOC, &GPIO_InitStructure);*/

	/*GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;*/
	/*GPIO_Init(GPIOA, &GPIO_InitStructure);*/

	/*GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;*/
	/*GPIO_Init(GPIOB, &GPIO_InitStructure);*/

	/*GPIOB->BSRRL = GPIO_Pin_6;*/
	/*GPIOE->BSRRL = GPIO_Pin_1;*/

	/*while (1)*/
	/*{*/
		/*GPIO_ResetBits(GPIOB, GPIO_Pin_6);*/
		/*GPIO_SetBits(GPIOE, GPIO_Pin_1);*/
		/*//rt_kprintf("LED1 on\n");*/
		/*rt_thread_delay(RT_TICK_PER_SECOND);*/
		/*GPIO_ResetBits(GPIOE, GPIO_Pin_1);*/
		/*GPIO_SetBits(GPIOB, GPIO_Pin_6);*/
		/*rt_thread_delay(RT_TICK_PER_SECOND * 3);*/
		/*//rt_kprintf("LED2 on\n");*/

	/*}*/
	/*GPIO_SetBits(GPIOA, GPIO_Pin_4);*/
	/*rt_thread_delay(RT_TICK_PER_SECOND);*/
	/*GPIO_SetBits(GPIOC, GPIO_Pin_13);*/
	/*rt_thread_delay(RT_TICK_PER_SECOND);*/
	/*GPIO_SetBits(GPIOB, GPIO_Pin_0);*/
	/*rt_thread_delay(RT_TICK_PER_SECOND);*/
	/*rt_kprintf("Power on\n");*/

	/*UC1701_Init();*/
	DisInit();
	DisNum16x32(12345, 1, 0, 16);
	//DisNumSet(12345, 1, 0, 16, 16, 32, 1);
	//DisCharSet(95, 16, (cFontAscii8x16 + ('%' - 0x20) * (8 >> 3) * 16), 8, 16);
	//DisCharSet(103, 16, (cFontAscii8x16 + ('L' - 0x20) * (8 >> 3) * 16), 8, 16);
	//DisCharSet(111, 16, (cFontAscii8x16 + ('E' - 0x20) * (8 >> 3) * 16), 8, 16);
	//DisCharSet(119, 16, (cFontAscii8x16 + ('L' - 0x20) * (8 >> 3) * 16), 8, 16);
	//DisUnitSet('L', 95, 16);
	uint8_t sUnit[5] = "%VOL";
	DisUnit(sUnit, 95, 32);

	uint8_t sGasName[14] = "C2H12S123O123";
	DisGasName(sGasName, 0, 48);

	uint8_t sStat[7] = "Detect";
	DisStat(sStat, 80, 48);

	DisSymCor(0, 0);
	DisRecRev(0, 0, 12, 9);
	//DisSymWron(0, 10);
	uint8_t sAlar[6] = "ALARM";
	DisSymAlar(sAlar, 52, 0);
	DisSymAlarRev(52,0);
	DisSymFan(86, 0);
	DisSymChar(124, 0);
	//DisSymBat(0, 59, 0);
	//DisSymBat(20, 75, 0);
	//DisSymBat(40, 91, 0);
	DisSymBat(60, 107, 0);
	//DisSymBat(80, 0, 10);
	//DisSymBat(100, 16, 10);
	//DisSymBat(255, 32, 10);
	//DisSymCharLar(48, 10);
	//DisSymFull(81, 10);


	//DisRecFillSet(0, 0, 12, 12);
	//DisCharSet(1, 1, cFontAscii5x10 + ('2' - 0x20) * 10, 5, 10);
	//DisRecFillSet(2, 2, 3, 3);

	const uint8_t cFontCh[] =
	{
		0x04, 0x40, 0x04, 0x44, 0xff, 0xfe, 0x04, 0x40, 0x04, 0x40, 0x04, 0x48,
		0x3f, 0xfc, 0x02, 0x08, 0x02, 0x08, 0x02, 0x08, 0x02, 0x08, 0x02, 0x48,
		0x02, 0x30, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00,
		//0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x80,0x03,0xC0,0x03,0xC0,0x03,0xC0,0x03,0xC0,
		//0x07,0xE0,0x07,0xE0,0x07,0xE0,0x07,0xE0,0x0E,0x70,0x0E,0x70,0x0E,0x70,0x0E,0x70,
		//0x1C,0x38,0x1C,0x38,0x1F,0xF8,0x1F,0xF8,0x3F,0xFC,0x38,0x1C,0x38,0x1C,0x38,0x1C,
		//0x70,0x0E,0x70,0x0E,0x70,0x0E,0x70,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	};
	//UC1701_CharSet(4, 1, cFontCh, 16, 16);
	//UC1701_CharSet(4, 0, cFontCh, 16, 32);
	DisRecSet(0, 0, 127, 63);

	char *lpCh = "H2O";
	while (*lpCh)
	{
		rt_kprintf("xxxxxxx %c\n", *(lpCh++));
	}
	rt_kprintf("Init ok\n");
	/*UC1701_DisAll();*/
}


int rt_application_init(void)
{
    rt_thread_t init_thread;

    rt_err_t result;

    /* init led thread */
    result = rt_thread_init(&led_thread,
                            "led",
                            led_thread_entry,
                            RT_NULL,
                            (rt_uint8_t*)&led_stack[0],
                            sizeof(led_stack),
                            20,
                            5);
    if (result == RT_EOK)
    {
        rt_thread_startup(&led_thread);
    }

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


	BUZZER_Init();

	result = rt_thread_init(&thread1, "thread1", thread1_entry,
								RT_NULL, &thread1_stack[0],
								sizeof(thread1_stack), 9, 10);
	if (result == RT_EOK)
		rt_thread_startup(&thread1);
	else
	{
	return -1;
	}

    return 0;
}

/*@}*/
