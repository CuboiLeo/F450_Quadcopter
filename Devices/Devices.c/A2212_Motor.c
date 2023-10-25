/**
 * @file A2212_Motor.c
 * @author Leo Liu
 * @brief A2212 Brushless Motor
 * @version 1.0
 * @date 2023-09-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "A2212_Motor.h"

void A2212_Motor_Init(TIM_HandleTypeDef *htim);
void A2212_Motor_Send_PWM(TIM_HandleTypeDef *htim, float FL, float FR, float RL, float RR);

A2212_Motor_t A2212_Motor;
A2212_Motor_Func_t A2212_Motor_Func = A2212_Motor_Func_GroundInit;
#undef A2212_Motor_Func_GroundInit

void A2212_Motor_Init(TIM_HandleTypeDef *htim)
{
	HAL_TIM_PWM_Start(htim,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(htim,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(htim,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(htim,TIM_CHANNEL_4);
}

void A2212_Motor_Send_PWM(TIM_HandleTypeDef *htim, float FL, float FR, float RL, float RR)
{
	__HAL_TIM_SetCompare(htim,TIM_CHANNEL_1,RR);
	__HAL_TIM_SetCompare(htim,TIM_CHANNEL_2,RL);
	__HAL_TIM_SetCompare(htim,TIM_CHANNEL_3,FL);
	__HAL_TIM_SetCompare(htim,TIM_CHANNEL_4,FR);
}
