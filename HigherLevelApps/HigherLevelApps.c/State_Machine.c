/**
 * @file State_Machine.c
 * @author Leo Liu
 * @brief control the state of the robot
 * @version 1.0
 * @date 2022-07-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "State_Machine.h"

void Remote_Control_Update(void);

State_Machine_Func_t State_Machine_Func = State_Machine_Func_GroundInit;
#undef State_Machine_Func_GroundInit

void Remote_Control_Update(void)
{
	if((DR16_Export_Data.Remote_Control.Left_Switch == SWITCH_DOWN && DR16_Export_Data.Remote_Control.Right_Switch == SWITCH_DOWN) 
		|| (DR16_Export_Data.Info_Update_Frame < 1))
	{
		Robot.Is_Disabled = 1;
	}
	
	else if(DR16_Export_Data.Remote_Control.Right_Switch == SWITCH_MID)
	{
		switch(DR16_Export_Data.Remote_Control.Left_Switch)
		{
			case(SWITCH_DOWN):
			{
				Robot.Is_Disabled = 0;
				Flight_Control.Mode = Init;
				break;
			}
			case(SWITCH_MID):
			{
				Robot.Is_Disabled = 0;
				Flight_Control.Mode = In_Control;
				break;
			}
			case(SWITCH_UP):
			{
				Robot.Is_Disabled = 1;
				break;
			}
		}
	}

	else if(DR16_Export_Data.Remote_Control.Right_Switch == SWITCH_UP)
	{
		switch(DR16_Export_Data.Remote_Control.Left_Switch)
		{
			case(SWITCH_DOWN):
			{

				break;
			}	
			case(SWITCH_MID):
			{

				break;
			}
			case(SWITCH_UP):
			{

				break;
			}
		}
	}
}
