/*
 * Stm32_F103C6_GPIO_Drivers.h
 *
 *  Created on: Feb 22, 2022
 *      Author: fawzy
 */

#ifndef INC_STM32_F103C6_GPIO_DRIVERS_H_
#define INC_STM32_F103C6_GPIO_DRIVERS_H_

//-----------------------------
//Includes
//-----------------------------
#include "Stm32_F103_x6.h"

//-----------------------------
//User type definitions (structures)
//-----------------------------
//config structure
typedef struct
{
	uint16_t GPIO_PinNumber;       //Specifies the gpio pins to be configured
	//this parameter must be set based on @ref GPIO_PINS_Define

	uint8_t GPIO_MODE;            //Specifies the operating mode for the selected pins
	//the parameter must be set based on @ref GPIO_MODE_Define


	uint8_t GPIO_OUTPUT_SPEED ;   //Specifies the speed for the selected pins
	//the parameter must be set baeed on @ref GPIO_SPEED_Define

}GPIO_Pinconfig_t;


//================================================================
//-----------------------------
//Macros Configuration References
//-----------------------------
//@ref GPIO_PINS_Define
#define GPIO_PINS_0                                         (uint16_t)0x0001  // pin0 selected  01
#define GPIO_PINS_1                                         (uint16_t)0x0002  // pin1 selected  10
#define GPIO_PINS_2                                         (uint16_t)0x0004  // pin2 selected  100
#define GPIO_PINS_3                                         (uint16_t)0x0008  // pin3 selected  1000
#define GPIO_PINS_4                                         (uint16_t)0x0010  // pin4 selected  1 0000
#define GPIO_PINS_5                                         (uint16_t)0x0020  // pin5 selected  10 0000
#define GPIO_PINS_6                                         (uint16_t)0x0040  // pin6 selected  100 0000
#define GPIO_PINS_7                                         (uint16_t)0x0080  // pin7 selected  1000 0000
#define GPIO_PINS_8                                         (uint16_t)0x0100  // pin8 selected  1 0000 0000
#define GPIO_PINS_9                                         (uint16_t)0x0200  // pin9 selected  10 0000 0000
#define GPIO_PINS_10                                        (uint16_t)0x0400  // pin10 selected  100 0000 0000
#define GPIO_PINS_11                                        (uint16_t)0x0800  // pin11 selected  1000 0000 0000
#define GPIO_PINS_12                                        (uint16_t)0x1000  // pin12 selected  1 0000 0000 0000
#define GPIO_PINS_13                                        (uint16_t)0x2000  // pin13 selected  10 0000 0000 0000
#define GPIO_PINS_14                                        (uint16_t)0x4000  // pin14 selected  100 0000 0000 0000
#define GPIO_PINS_15                                        (uint16_t)0x8000  // pin15 selected  1000 0000 0000 0000
#define GPIO_PINS_All                                       (uint16_t)0xFFFF  // ALL PINS  selected  1111 1111 1111 1111
#define GPIO_PINS_MASK                                      0x0000FFFF  // pin mask for assert test

//@ref GPIO_MODE_Define
/*00: Analog mode
01: Floating input (reset state)
10 : Input with pull-up /
11:  Input with pull-down

00: General purpose output push-pull
01: General purpose output Open-drain
10: Alternate function output Push-pull
11: Alternate function output Open-drain*/
#define GPIO_MODE_Analog                           0x00000000u          //analog mode
#define GPIO_MODE_INPUT_FLO                        0x00000001u          //Floating input (reset state)
#define GPIO_MODE_INPUT_PU                         0x00000002u          //Input with pull-up
#define GPIO_MODE_INPUT_PD                         0x00000003u          //input  with pull down
#define GPIO_MODE_OUTPUT_PP                        0x00000004u          //General purpose output push-pull
#define GPIO_MODE_OUTPUT_OD                        0x00000005u          //General purpose output Open-drain
#define GPIO_MODE_OUTPUT_AF_PP                     0x00000006u          //Alternate function output Push-pull
#define GPIO_MODE_OUTPUT_AF_OD                     0x00000007u          //Alternate function output Open-drain
#define GPIO_MODE_AF_INPUT                         0x00000008u          //alternative function input



//@ref GPIO_SPEED_Define
/*
 * 1: Output mode, max speed 10 MHz.
2: Output mode, max speed 2 MHz.
3: Output mode, max speed 50 MHz.
 *
 */

#define GPIO_SPEED_10M                             0x00000001u          //Output mode, max speed 10 MHz.
#define GPIO_SPEED_2M                              0x00000002u          //Output mode, max speed 2 MHz.
#define GPIO_SPEED_50M                             0x00000003u          // Output mode, max speed 50 MHz.

//@ref GPIO_PIN_state
#define GPIO_PIN_set                     1
#define GPIO_PIN_reset                   0

// @ref GPIO_RETURN_LOCK
#define GPIO_RETURN_LOCK_Enabled         1
#define GPIO_RETURN_LOCK_ERROR           0

//==================================================
/*
* ===============================================
* APIs Supported by "MCAL GPIO DRIVER"
* ===============================================
*/





void MCAL_GPIO_Init(GPIO_TypeDef *GPIOX ,GPIO_Pinconfig_t *pinconfig);
void MCAL_GPIO_DeInit(GPIO_TypeDef *GPIOX );

uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef *GPIOX ,uint16_t pinNumber);
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef *GPIOX );

void MCAL_GPIO_WritePin(GPIO_TypeDef *GPIOX ,uint16_t pinNumber ,uint8_t value);
void MCAL_GPIO_WritePort(GPIO_TypeDef *GPIOX ,uint16_t value);

void MCAL_GPIO_togglePin(GPIO_TypeDef *GPIOX ,uint16_t pinNumber );
uint8_t MCAL_GPIO_lockPin(GPIO_TypeDef *GPIOX ,uint16_t pinNumber );










#endif /* INC_STM32_F103C6_GPIO_DRIVERS_H_ */
