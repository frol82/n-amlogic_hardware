/*
 * Copyright (C) 2015 Amlogic, Inc. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
*/


/**************PHY****************/
#define	AML_SLC_NAND_SUPPORT	
#define	AML_MLC_NAND_SUPPORT	
//#define	AML_NAND_DBG
#define 	NEW_NAND_SUPPORT
#define AML_NAND_NEW_OOB

#define NAND_ADJUST_PART_TABLE

#ifdef NAND_ADJUST_PART_TABLE
#define 	ADJUST_BLOCK_NUM	4
#else
#define 	ADJUST_BLOCK_NUM	0
#endif

#define AML_NAND_RB_IRQ
//#define AML_NAND_DMA_POLLING

extern  int is_phydev_off_adjust(void); 
extern  int get_adjust_block_num(void);

