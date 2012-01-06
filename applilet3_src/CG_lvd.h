/*
*******************************************************************************
* Copyright(C) 2011 Renesas Electronics Corporation
* RENESAS ELECTRONICS CONFIDENTIAL AND PROPRIETARY
* This program must be used solely for the purpose for which
* it was furnished by Renesas Electronics Corporation. No part of this
* program may be reproduced or disclosed to others, in any
* form, without the prior written permission of Renesas Electronics
* Corporation. 
*
* This device driver was created by Applilet3 for RL78/G13
* 16-Bit Single-Chip Microcontrollers
* Filename:	CG_lvd.h
* Abstract:	This file implements device driver for LVD module.
* APIlib:	Applilet3 for RL78/G13 E1.00b [14 Jan 2011]
* Device:	R5F100LE
* Compiler:	IAR Systems iccrl78
* Creation date:	8/12/2011
*******************************************************************************
*/

#ifndef _MDLVD_
#define _MDLVD_
/*
*******************************************************************************
**  Register bit define
*******************************************************************************
*/
/*
	Low-voltage detection status register (LVIM)
*/
/* LVIS register rewrite enable/disable control (LVISEN) */
#define _00_LVD_REWRITE_LVIS_DISABLE	0x00U	/* disable */
#define _80_LVD_REWRITE_LVIS_ENABLE	0x80U	/* enable */
/* LVI output mask status flag (LVIOMSK) */
#define _00_LVD_MASK_INVALIDITY		0x00U	/* mask invalidity */
#define _04_LVD_MASK_VALIDITY		0x02U	/* mask validity */
/* Low-voltage detection flag (LVIF) */
#define _00_LVD_FLAG_OVER		0x00U	/* voltage >= detection voltage */
#define _01_LVD_FLAG_LESS		0x01U	/* voltage < detection voltage */

/*
	Low-voltage detection operation control register (LVIS)
*/
/* Operation mode (LVIMD) */
#define _00_LVD_MODE_INT		0x00U	/* generate interrupt */
#define _00_LVD_MODE_RESET		0x01U	/* generate reset */
/* LVI detection level (LVILV) */
#define _00_LVD_LEVEL_INT		0x00U	/* interrupt generate level */
#define _00_LVD_LEVEL_RESET		0x01U	/* reset generate level */
/*
*******************************************************************************
**  Macro define
*******************************************************************************
*/
/*
*******************************************************************************
**  Function define
*******************************************************************************
*/
void LVD_Init(void);
void LVD_InterruptModeStart(void);
__interrupt void MD_INTLVI(void);

/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
