/**
 * @file    flash.c
 * @brief   FLASH 编程
 * @author  ptz
 * @email   ptz19861212@163.com
 * @version 0.0.1
 * @date    2013-12-11 14:59:17 星期三 
 * @history (1).2013-12-11 14:59:17 星期三 create
 */
/* Copyright (C)
 * 
 * My own license
 * All right reserved
 * 
 */

#include "flash_in.h"

//void FlashProgramTest(void)
//{
//	uint32_t lAddrStart, lAddrEnd, lPageNum;
//
//	lAddrStart = CONFIG_FLASH_PAGE_WRITE_ADDR_START;
//	lAddrEnd = CONFIG_FLASH_PAGE_WRITE_ADDR_END;
//
//	// 开始地址去除后面的那些位
//	//lAddrStart &= 0xFFFFF800;
//	lAddrStart &= ~(FLASH_PAGE_SIZE - 1);
//	// 结束地址要是一个页地址的首地址，如果不是的话，那么就要调整为下一个页的首地址
//	if (lAddrEnd & (FLASH_PAGE_SIZE - 1))
//	{
//		//lAddrEnd &= 0xFFFFF800;
//		lAddrEnd &= ~(FLASH_PAGE_SIZE - 1);
//		//lAddrEnd += 0x0800;
//		lAddrEnd += FLASH_PAGE_SIZE;
//	}
//
//	/* Define the number of page to be erased */
//	lPageNum = (lAddrEnd - lAddrStart) / FLASH_PAGE_SIZE;
//
//	rt_kprintf("start = %x\t end = %x\t num = %x\t %x \n",
//				lAddrStart, lAddrEnd, lPageNum,
//				CONFIG_FLASH_PAGE_WRITE_ADDR_START);
//
//	/* Porgram FLASH Bank1 ********************************************************/
//	/* Unlock the Flash Bank1 Program Erase controller */
//	FLASH_UnlockBank1();
//
//	/* Clear All pending flags */
//	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
//
//	uint32_t lI = 0;
//	volatile FLASH_Status lFlashStatus = FLASH_COMPLETE;
//
//	/* Erase the FLASH pages */
//	for (lI = 0; (lI < lPageNum) && (lFlashStatus == FLASH_COMPLETE); lI++)
//	{
//		rt_kprintf("%x\n", lAddrStart + (FLASH_PAGE_SIZE * lI));
//		lFlashStatus = FLASH_ErasePage(lAddrStart + (FLASH_PAGE_SIZE * lI));
//	}
//
//	uint32_t lPageAddr = CONFIG_FLASH_PAGE_WRITE_ADDR_START;
//
//	/* Program Flash Bank1 */
//	while ((lPageAddr < CONFIG_FLASH_PAGE_WRITE_ADDR_END) &&
//			(lFlashStatus == FLASH_COMPLETE))
//	{
//		lFlashStatus = FLASH_ProgramWord(lPageAddr, 4321);
//		lPageAddr += 4;
//	}
//
//	FLASH_LockBank1();
//
//	lPageAddr = CONFIG_FLASH_PAGE_WRITE_ADDR_START;
//
//	for (lI = 0; lI < 10; lI++)
//	{
//		rt_kprintf("%d\t", *(volatile uint32_t *)lPageAddr);
//		lPageAddr += 4;
//	}
//	rt_kprintf("\n");
//
//}


/**
 * @brief   FLASH 擦除
 *
 * @param   lpFlash
 */
static void FlashErase(S_Flash_Erase* lpFlash)
{
	/* Porgram FLASH Bank1 ********************************************************/
	/* Unlock the Flash Bank1 Program Erase controller */
	FLASH_UnlockBank1();

	/* Clear All pending flags */
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);

	uint32_t lI = 0;
	volatile FLASH_Status lFlashStatus = FLASH_COMPLETE;

	/* Erase the FLASH pages */
	for (lI = 0; (lI < lpFlash->Page.Num) && (lFlashStatus == FLASH_COMPLETE);
			lI++)
	{
		lFlashStatus = FLASH_ErasePage(lpFlash->Addr.Start +
										(lpFlash->Page.Size * lI));
	}
}


/**
 * @brief   FLASH 编程
 *
 * @param   lpFlash
 */
static void FlashProgram(S_Flash_Write* lpWrite)
{
	volatile FLASH_Status lFlashStatus = FLASH_COMPLETE;
	uint32_t lPageAddr = lpWrite->Addr.Start;
	uint32_t lI = 0;

	/* Program Flash Bank1 */
	while ((lPageAddr < lpWrite->Addr.End) &&
			(lFlashStatus == FLASH_COMPLETE))
	{
		lFlashStatus = FLASH_ProgramHalfWord(lPageAddr, lpWrite->Array[lI]);
		lPageAddr += 2;
		lI++;
	}

	FLASH_LockBank1();
}


/**
 * @brief   FLASH 写入
 *
 * @param   lpWrite
 */
void FlashWrite(S_Flash_Write* lpWrite)
{
	S_Flash_Erase lErase;

	lErase.Addr.Start = lpWrite->Addr.Start;
	lErase.Addr.End = lpWrite->Addr.End;
	lErase.Page.Size = FLASH_PAGE_SIZE;

	// 开始地址去除后面的那些位
	//lAddrStart &= 0xFFFFF800;
	lErase.Addr.Start &= ~(FLASH_PAGE_SIZE - 1);
	// 结束地址要是一个页地址的首地址，如果不是的话，那么就要调整为下一个页的首地址
	if (lErase.Addr.End & (FLASH_PAGE_SIZE - 1))
	{
		//lAddrEnd &= 0xFFFFF800;
		lErase.Addr.End &= ~(FLASH_PAGE_SIZE - 1);
		//lAddrEnd += 0x0800;
		lErase.Addr.End += FLASH_PAGE_SIZE;
	}

	/* Define the number of page to be erased */
	lErase.Page.Num = (lErase.Addr.End - lErase.Addr.Start) /
							FLASH_PAGE_SIZE;

	FlashErase(&lErase);

	FlashProgram(lpWrite);
}


/**
 * @brief   FLASH 读取
 *
 * @param   lpFlash
 */
void FlashRead(S_Flash_Read* lpFlash)
{
	uint32_t lAddr, lI;

	lI = 0;

	lAddr = lpFlash->Addr.Start;

	while (lAddr < lpFlash->Addr.End)
	{
		*(lpFlash->Array + lI) = *(volatile uint8_t *)lAddr;
		lI++;
		lAddr++;
	}
}
