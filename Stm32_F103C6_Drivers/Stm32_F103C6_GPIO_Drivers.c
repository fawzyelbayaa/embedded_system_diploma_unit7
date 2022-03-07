/*
 * Stm32_F103C6_GPIO_Drivers.c
 *
 *  Created on: Feb 22, 2022
 *      Author: fawzy elbayaa
 */
#include "Stm32_F103C6_GPIO_Drivers.h"


/**================================================================
 * @Fn          -GET_CRLH_Position
 * @brief       -get specific pin and shift from mode[:]
 * @param [in]  -PinNumber:set pin number according to @ref GPIO_PINS_Define
 * @retval      -return the value to shifted from mode[]
 * Note         -
 */

uint8_t GET_CRLH_Position(uint16_t PinNumber)
{
	switch (PinNumber)
	{
	case GPIO_PINS_0 :
		return 0;
		break;
	case GPIO_PINS_1 :
		return 4;
		break;
	case GPIO_PINS_2 :
		return 8;
		break;
	case GPIO_PINS_3 :
		return 12;
		break;
	case GPIO_PINS_4 :
		return 16;
		break;
	case GPIO_PINS_5 :
		return 20;
		break;
	case GPIO_PINS_6 :
		return 24;
		break;
	case GPIO_PINS_7 :
		return 28;
		break;
	case GPIO_PINS_8 :
		return 0;
		break;

	case GPIO_PINS_9 :
		return 4;
		break;
	case GPIO_PINS_10 :
		return 8;
		break;
	case GPIO_PINS_11 :
		return 12;
		break;
	case GPIO_PINS_12 :
		return 16;
		break;
	case GPIO_PINS_13 :
		return 20;
		break;
	case GPIO_PINS_14 :
		return 24;
		break;
	case GPIO_PINS_15 :
		return 28;
		break;

	}
	return 0;

}


/**================================================================
 * @Fn          -MCAL_GPIO_Init
 * @brief       -Initializes the GPIOX PINy according to the specific parameter in pinconfig
 * @param [in]  -GPIOX :where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param [in]  -pinconfig :pointer to the GPIO_pinconfig_t structure that contain
 *                           the configuration information for specified GPIO pins
 * @retval      -none
 * Note         -Stm32F103C6 MCU has GPIO A, B, C, D, E Modules
				But LQFP48 Package has only GPIO A, B, PART of C/D exported as external PINs from the Module
 */


void MCAL_GPIO_Init(GPIO_TypeDef *GPIOX ,GPIO_Pinconfig_t *pinconfig)
{
	volatile uint32_t * Configregister =NULL;
	uint8_t PIN_Config=0;
	Configregister =(pinconfig->GPIO_PinNumber <GPIO_PINS_8)? &GPIOX->CRL : &GPIOX->CRH;
	//Clear CNF[:]  MODE[:]
	*Configregister &=~(0xf<<GET_CRLH_Position(pinconfig->GPIO_PinNumber));

	//IF PIN IS OUTPUT
	if((pinconfig->GPIO_MODE ==GPIO_MODE_OUTPUT_PP)||(pinconfig->GPIO_MODE ==GPIO_MODE_OUTPUT_OD)||(pinconfig->GPIO_MODE ==GPIO_MODE_OUTPUT_AF_PP)||(pinconfig->GPIO_MODE ==GPIO_MODE_OUTPUT_AF_OD))
	{
		PIN_Config =((((pinconfig->GPIO_MODE -4 ) <<2) | (pinconfig->GPIO_OUTPUT_SPEED)) &0x0f);


	}
	else //if pin is input
	{
		if ((pinconfig->GPIO_MODE ==GPIO_MODE_Analog) ||(pinconfig->GPIO_MODE ==GPIO_MODE_INPUT_FLO))
		{
			//set CNF[:]  MODE[:]
			PIN_Config =((((pinconfig->GPIO_MODE  ) <<2) | 0X0) &0x0f);

		}
		else if((pinconfig->GPIO_MODE ==GPIO_MODE_AF_INPUT)) //consider it as input floating
		{
			//set CNF[:]  MODE[:]
			PIN_Config =((((GPIO_MODE_INPUT_FLO ) <<2) | 0X0) &0x0f);

		}
		else //input PU or PD
		{
			PIN_Config =((((GPIO_MODE_INPUT_PU)>>2) |0x0)&0x0f);
			if(pinconfig->GPIO_MODE ==GPIO_MODE_INPUT_PU)
			{
				//Table 20. Port bit configuration table PXODR=1
				GPIOX->ODR |=pinconfig->GPIO_PinNumber;

			}
			else
			{
				//Table 20. Port bit configuration table PXODR=0
				GPIOX->ODR &=~pinconfig->GPIO_PinNumber;


			}


		}

	}

	//write on CRL or CRH
	(*Configregister) |= (PIN_Config <<GET_CRLH_Position(pinconfig->GPIO_PinNumber));




}

/**================================================================
 * @Fn          -MCAL_GPIO_DeInit
 * @brief       -reset all GPIO register
 * @param [in]  -GPIOX :where x can be (A..E depending on device used) to select the GPIO peripheral
 * @retval      -none
 * Note         -none
 */

void MCAL_GPIO_DeInit(GPIO_TypeDef *GPIOX )
{
	/*GPIOX->BRR=0X00000000;
	GPIOX->BSRR =0X00000000;
	GPIOX->CRH=0X44444444;
	GPIOX->CRL=0X44444444;
	//GPIOX->IDR=0X00000000;           // READ ONLY
	GPIOX->LCKR=0X00000000;
	GPIOX->ODR=0X00000000;*/

	if(GPIOX==GPIOA)
	{
		RCC->APB2RSTR |=(1<<2);      // bit 2 IOPARST: IO port A reset
		RCC->APB2RSTR &=~(1<<2);
	}
	if(GPIOX==GPIOB)
	{
		RCC->APB2RSTR |=(1<<3);      // bit 3 IOPARST: IO port A reset
		RCC->APB2RSTR &=~(1<<3);
	}
	if(GPIOX==GPIOC)
	{
		RCC->APB2RSTR |=(1<<4);      // bit 4 IOPARST: IO port A reset
		RCC->APB2RSTR &=~(1<<4);
	}
	if(GPIOX==GPIOD)
	{
		RCC->APB2RSTR |=(1<<5);      // bit 5 IOPARST: IO port A reset
		RCC->APB2RSTR &=~(1<<5);
	}
	/*if(GPIOX==GPIOE)
	{
		RCC->APB2RSTR |=(1<<6);      // bit 6 IOPARST: IO port A reset
		RCC->APB2RSTR &=~(1<<6);
	}*/


}

/**================================================================
 * @Fn          -MCAL_GPIO_ReadPin
 * @brief       -read specific pin
 * @param [in]  -GPIOX :where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param [in]  -pinNumber :set pin number according to @ref GPIO_PINS_Define
 *
 * @retval      -the input pin value (two values based in @ref GPIO_PIN_state)
 * Note         -none
 */

uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef *GPIOX ,uint16_t pinNumber)
{
	uint8_t bit_status=0;
	if(((GPIOX->IDR) & pinNumber) !=(uint32_t)GPIO_PIN_reset)
	{
		bit_status =GPIO_PIN_set;
	}
	else
	{
		bit_status =GPIO_PIN_reset;
	}
	return bit_status;

}

/**================================================================
 * @Fn          -MCAL_GPIO_ReadPort
 * @brief       -read specific port
 * @param [in]  -GPIOX :where x can be (A..E depending on device used) to select the GPIO peripheral

 * @retval      -the input port value
 * Note         -none
 */

uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef *GPIOX )
{
	uint16_t port_value;
	port_value =(uint16_t)(GPIOX->IDR);
	return port_value;

}
/**================================================================
 * @Fn          -MCAL_GPIO_WritePin
 * @brief       -write on specific pin
 * @param [in]  -GPIOX :where x can be (A..E depending on device used) to select the GPIO peripheral
  @param [in]  -pinNumber :set pin number according to @@ref GPIO_PINS_Define
  @param [in]  -value : pin value
 * @retval      -none
 * Note         -none
 */


void MCAL_GPIO_WritePin(GPIO_TypeDef *GPIOX ,uint16_t pinNumber ,uint8_t value)
{
	if(value !=GPIO_PIN_reset)
	{
		//GPIOX->ODR |=pinNumber;
		//or
		/*Bits 15:0 BSy: Port x Set bit y (y= 0 .. 15)
        These bits are write-only and can be accessed in Word mode only.
         0: No action on the corresponding ODRx bit
         1: Set the corresponding ODRx bit
		 *
		 */
		GPIOX->BSRR =(uint32_t)pinNumber;
	}
	else
	{
		/*
		 * Bits 15:0 BRy: Port x Reset bit y (y= 0 .. 15)
         These bits are write-only and can be accessed in Word mode only.
         0: No action on the corresponding ODRx bit
         1: Reset the corresponding ODRx bit
		 */
		GPIOX->BRR=(uint32_t)pinNumber;

	}


}
/**================================================================
 * @Fn          -MCAL_GPIO_WritePort
 * @brief       -write on specific port
 * @param [in]  -GPIOX :where x can be (A..E depending on device used) to select the GPIO peripheral

  @param [in]  -value : port value
 * @retval      -none
 * Note         -none
 */


void MCAL_GPIO_WritePort(GPIO_TypeDef *GPIOX ,uint16_t value)
{
	GPIOX->ODR =value;

}
/**================================================================
 * @Fn          -MCAL_GPIO_togglePin
 * @brief       -toggle specific Pin
 * @param [in]  -GPIOX :where x can be (A..E depending on device used) to select the GPIO peripheral

  @param [in]  -pinNumber :set pin number according to @@ref GPIO_PINS_Define
 * @retval      -none
 * Note         -none
 */

void MCAL_GPIO_togglePin(GPIO_TypeDef *GPIOX ,uint16_t pinNumber )
{
	GPIOX->ODR ^=(uint32_t)pinNumber;

}
/**================================================================
 * @Fn          -MCAL_GPIO_lockPin
 * @brief       -lock specific Pin
 * @param [in]  -GPIOX :where x can be (A..E depending on device used) to select the GPIO peripheral

  @param [in]  -pinNumber :set pin number according to @@ref GPIO_PINS_Define
 * @retval      -OK if pin configure is locked Or ERROR if pin is not locked (OK & ERROR are defined @ref GPIO_RETURN_LOCK)
 * Note         -none
 */
uint8_t MCAL_GPIO_lockPin(GPIO_TypeDef *GPIOX ,uint16_t pinNumber )
{
	/*Bit 16 LCKK[16]: Lock key
	This bit can be read anytime. It can only be modified using the Lock Key Writing Sequence.
	0: Port configuration lock key not active
	1: Port configuration lock key active. GPIOx_LCKR register is locked until the next reset.
	LOCK key writing sequence:
	Write 1
	Write 0
	Write 1
	Read 0
	Read 1 (this read is optional but confirms that the lock is active)
	Note: During the LOCK Key Writing sequence, the value of LCK[15:0] must not change.
	Any error in the lock sequence will abort the lock.
	Bits 15:0 LCKy: Port x Lock bit y (y= 0 .. 15)
	These bits are read write but can only be written when the LCKK bit is 0.
	0: Port configuration not locked
	1: Port configuration locked.*/
	volatile uint32_t tmp=1<<16;
	//set the LCKy
	tmp |=pinNumber;

	//Write 1
	GPIOX->LCKR =tmp;

	//Write 0
	GPIOX->LCKR =pinNumber;

	//Write 1
	GPIOX->LCKR =tmp;

	//Read 0
	tmp =GPIOX->LCKR;
	//Read 1 (this read is optional but confirms that the lock is active)
	if((uint32_t)(GPIOX->LCKR & 1<<16))
	{
		return GPIO_RETURN_LOCK_Enabled;

	}
	else
	{
		return GPIO_RETURN_LOCK_ERROR;
	}


}



