/**
 * @file Ramp_Calc.h
 * @author Leo Liu
 * @brief header file for ramp calc
 * @version 1.0
 * @date 2022-07-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __RAMP_CALC_H
#define __RAMP_CALC_H

#include "User_Defined_Math.h"
#include "math.h"

#define Ramp_Calc_Func_GroundInit	\
		{															\
				&Ramp,										\
		}

typedef struct
{
	uint8_t Ramp_Finished_Flag;
}Ramp_Calc_t;

typedef struct
{
	float (*Ramp)(float Current_Value,float Target_Value, float Ramp_Rate);
}Ramp_Calc_Func_t;

extern Ramp_Calc_Func_t Ramp_Calc_Func;

#endif
