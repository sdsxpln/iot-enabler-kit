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
* Filename:	CG_ad.c
* Abstract:	This file implements device driver for AD module.
* APIlib:	Applilet3 for RL78/G13 E1.00b [14 Jan 2011]
* Device:	R5F100LE
* Compiler:	IAR Systems iccrl78
* Creation date:	8/26/2011
*******************************************************************************
*/

/*
*******************************************************************************
** Include files
*******************************************************************************
*/
#include "CG_macrodriver.h"
#include "CG_ad.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "CG_userdefine.h"

/*
*******************************************************************************
**  Global define
*******************************************************************************
*/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function initializes the AD converter.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void AD_Init(void)
{
	ADCEN = 1U;	/* supply AD clock */
	ADM0 = _00_AD_ADM0_INITIALVALUE;	/* disable AD conversion and clear ADM0 register */
	ADMK = 1U;	/* disable INTAD interrupt */
	ADIF = 0U;	/* clear INTAD interrupt flag */
	/* Set INTAD level2 priority */
	ADPR1 = 1U;
	ADPR0 = 0U;
	ADPC = _08_AD_ADPC_7ANALOG;
	/* Set ANI0 - ANI6 pin as analog input */
	PM2 |= 0x7FU;
	/* Set ANI18 pin */
	PMC14 |= 0x80U;
	PM14 |= 0x80U;
	/* Set ANI19 pin */
	PMC12 |= 0x01U;
	PM12 |= 0x01U;
	ADM0 = _00_AD_CONVERSION_CLOCK_64 | _00_AD_TIME_MODE_STANDARD_1 | _00_AD_OPERMODE_SELECT;
	ADM1 = _00_AD_TRIGGER_SOFTWARE | _00_AD_CONVMODE_CONSELECT;
	ADM2 = _00_AD_POSITIVE_VDD | _00_AD_NEGATIVE_VSS | _00_AD_AREA_MODE_1 | _00_AD_RESOLUTION_10BIT;
	ADUL = _FF_AD_ADUL_VALUE;
	ADLL = _00_AD_ADLL_VALUE;
	ADS = _04_AD_INPUT_CHANNEL_4;
	ADCE = 1U;	/* enable AD comparator */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function starts the AD converter.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void AD_Start(void)
{
	ADIF = 0U;	/* clear INTAD interrupt flag */
	ADMK = 0U;	/* enable INTAD interrupt */
	ADCS = 1U;	/* enable AD conversion */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function stops the AD converter.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void AD_Stop(void)
{
	ADCS = 0U;	/* disable AD conversion */
	ADMK = 1U;	/* disable INTAD interrupt */
	ADIF = 0U;	/* clear INTAD interrupt flag */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function enables comparator operation.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void AD_ComparatorOn(void)
{
	ADCE = 1U;	/* enable AD comparator */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function stops comparator operation.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void AD_ComparatorOff(void)
{
	ADCE = 0U;	/* disable AD comparator */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function returns the conversion result in the buffer.
**
**  Parameters:
**	buffer: the address where to write the conversion result
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void AD_Read(USHORT *buffer)
{
	*buffer = (USHORT)(ADCR >> 6U);
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function selects analog input channel.
**
**  Parameters:
**	channel: analog input channel
**
**  Returns:
**	MD_OK
**	MD_ARGERROR
**
**-----------------------------------------------------------------------------
*/
MD_STATUS AD_SelectADChannel(enum ADChannel channel)
{
	MD_STATUS status = MD_OK;

	if (((channel > ADCHANNEL7) && (channel < ADCHANNEL16)) || ((channel > ADCHANNEL19) && (channel < ADTEMPERSENSOR0)) || (channel > ADTEMPERSENSOR1))
	{
		status = MD_ARGERROR;
	}
	else
	{
		ADS = (UCHAR)channel;
	}

	return (status);
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
