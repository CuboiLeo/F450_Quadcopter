/**
 * @file A2212_Motor.h
 * @author Leo Liu
 * @brief A2212 Brushless Motor
 * @version 1.0
 * @date 2023-09-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __A2212_MOTOR_H
#define __A2212_MOTOR_H

#include <stdio.h>
#include <stdint.h>
#include "tim.h"

#define A2212_OUTPUT_LIMIT 5000

#define A2212_Motor_Func_GroundInit       \
    {                                 		\
				&A2212_Motor_Init,								\
						&A2212_Motor_Send_PWM,				\
    }

typedef struct
{
	float FL_Output;
	float FR_Output;
	float RL_Output;
	float RR_Output;
}A2212_Motor_t;

typedef struct
{
	void (*A2212_Motor_Init)(TIM_HandleTypeDef *htim);
	void (*A2212_Motor_Send_PWM)(TIM_HandleTypeDef *htim, float FL, float FR, float RL, float RR);
}A2212_Motor_Func_t;

extern A2212_Motor_t A2212_Motor;
extern A2212_Motor_Func_t A2212_Motor_Func;


#endif
