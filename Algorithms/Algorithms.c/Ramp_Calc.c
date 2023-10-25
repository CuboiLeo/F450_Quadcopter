/**
 * @file Ramp_Calc.c
 * @author Leo Liu
 * @brief ramp up or down calculation
 * @version 1.0
 * @date 2022-07-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Ramp_Calc.h"

Ramp_Calc_t Ramp_Calc;

float Ramp(float Current_Value, float Target_Value, float Ramp_Rate);

Ramp_Calc_Func_t Ramp_Calc_Func = Ramp_Calc_Func_GroundInit;
#undef Ramp_Calc_Func_GroundInit

//Slowly ramp the given value to the target value
float Ramp(float Current_Value, float Target_Value, float Ramp_Rate)
{
	float Error = Target_Value - Current_Value;
	if(Error > 0)
		Current_Value += Ramp_Rate;
	else if(Error < 0)
		Current_Value -= Ramp_Rate;
	
	return Current_Value;
}

