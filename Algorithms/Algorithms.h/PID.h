/**
 * @file PID.h
 * @author Leo Liu
 * @brief header file for PID
 * @version 1.0
 * @date 2022-07-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */
 
#ifndef __PID_H
#define	__PID_H

#include "User_Defined_Math.h" 
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define PID_Func_GroundInit		\
		{													\
			&Positional_PID,				\
					&Clear_PID_Data,		\
		}

typedef struct
{
	float Target_Value;
	float Measured_Value;
	
	float Error;
	float Prev_Error;
	float Prev_Prev_Error;
	
	float Kp;
	float Ki;
	float Kd;
	
	float P_Out;
	float I_Out;
	float D_Out;
	
	float Output;
	float Output_Max;
	float I_Out_Max;
}PID_t;

typedef struct
{
	float (*Positional_PID)(PID_t *PID, float Target_Value, float Measured_Value);
	void (*Clear_PID_Data)(PID_t *PID);
}PID_Func_t;

#define Yaw_Angle_PIDInit			\
		{													\
				0,										\
					0,									\
					0,									\
					0,									\
					0,									\
					20.0f,							\
					0,									\
					10.0f,							\
					0,									\
					0,									\
					0,									\
					0,									\
					2000.0f,						\
					0,									\
		}
		
#define Pitch_Angle_PIDInit		\
		{													\
				0,										\
					0,									\
					0,									\
					0,									\
					0,									\
					40.0f,							\
					0,									\
					80.0f,							\
					0,									\
					0,									\
					0,									\
					0,									\
					2000.0f,						\
					0,									\
		}

#define Roll_Angle_PIDInit		\
		{													\
				0,										\
					0,									\
					0,									\
					0,									\
					0,									\
					40.0f,							\
					0,									\
					80.0f,							\
					0,									\
					0,									\
					0,									\
					0,									\
					2000.0f,						\
					0,									\
		}

#define Altitude_PIDInit		\
		{													\
				0,										\
					0,									\
					0,									\
					0,									\
					0,									\
					0,									\
					0,									\
					0,									\
					0,									\
					0,									\
					0,									\
					0,									\
					0,									\
					0,									\
		}
extern PID_Func_t PID_Func;
extern PID_t Yaw_Angle_PID;
extern PID_t Pitch_Angle_PID;
extern PID_t Roll_Angle_PID;
extern PID_t Altitude_PID;

#endif
