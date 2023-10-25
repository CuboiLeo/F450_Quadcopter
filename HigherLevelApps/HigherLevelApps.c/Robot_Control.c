/**
 * @file Robot_Control.c
 * @author Leo Liu
 * @brief control the robot
 * @version 1.0
 * @date 2022-07-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Robot_Control.h"

Robot_t Robot;

void Robot_Get_Data(void);
void Robot_In_Control(void);

Robot_Func_t Robot_Func = Robot_Func_GroundInit;
#undef Robot_Func_GroundInit

void Robot_Get_Data(void)
{
	State_Machine_Func.Remote_Control_Update();

	Flight_Control_Func.Flight_Control_Get_Data();
	Flight_Control_Func.Flight_Control_Processing();
}

void Robot_In_Control(void)
{
	if(Robot.Is_Disabled == 1)
	{
		A2212_Motor_Func.A2212_Motor_Send_PWM(&htim4,0,0,0,0);
	}
	
	else if(Flight_Control.Mode == Init)
	{
		if(Flight_Control.Init_Flag == 0)
		{
			for(int i = 1000; i > 0; i--)
			{
				A2212_Motor_Func.A2212_Motor_Send_PWM(&htim4,5000,5000,5000,5000);
				osDelay(1);
			}
			for(int i = 1000; i > 0; i--)
			{
				A2212_Motor_Func.A2212_Motor_Send_PWM(&htim4,120,120,120,120);
				osDelay(1);
			}
			Flight_Control.Init_Flag = 1;
		}
		else
		{
			A2212_Motor_Func.A2212_Motor_Send_PWM(&htim4,0,0,0,0);
		}
	}

	else if(Flight_Control.Mode == In_Control)
	{
//		A2212_Motor.RR_Output = VAL_LIMIT((DR16_Export_Data.Remote_Control.Joystick_Left_Vy+660.0f)*2.0f,2400.0f,0.0f);
//		A2212_Motor_Func.A2212_Motor_Send_PWM(&htim4,A2212_Motor.RR_Output,A2212_Motor.RR_Output,A2212_Motor.RR_Output,A2212_Motor.RR_Output);
		A2212_Motor_Func.A2212_Motor_Send_PWM(&htim4,A2212_Motor.FL_Output,A2212_Motor.FR_Output,A2212_Motor.RL_Output,A2212_Motor.RR_Output);
	}
}

