/**
 * @file Flight_Control.h
 * @author Leo Liu
 * @brief flight control for the quadcopter
 * @version 1.0
 * @date 2023-09-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __FLIGHT_CONTROL_H
#define __FLIGHT_CONTROL_H

#include "stdio.h"
#include "stdint.h"
#include "A2212_Motor.h"
#include "DR16_Remote.h"
#include "User_Defined_Math.h"
#include "Board_A_IMU.h"
#include "PID.h"
#include "Kalman_Filter.h"
#include "Ramp_Calc.h"

#define Flight_Control_Func_GroundInit    \
    {                                 		\
			&Flight_Control_Get_Data,						\
				&Flight_Control_Processing,				\
    }

typedef struct
{
	enum
	{
		Init,
		In_Control,
	}Mode;
	
	struct
	{
		float Pitch;
		float Yaw;
		float Roll;
		float Altitude;
		float Gyro_Pitch;
		float Gyro_Yaw;
		float Gyro_Roll;
	}Current;
	
	struct
	{
		float Pitch;
		float Yaw;
		float Roll;
		float Altitude;
	}Target;
	
	struct
	{
		float Throttle;
		float Pitch;
		float Yaw;
		float Roll;
		float Pitch_KF;
		float Yaw_KF;
		float Roll_KF;
		float Pitch_Smooth;
		float Yaw_Smooth;
		float Roll_Smooth;
		float Altitude;
	}Output;
	
	uint8_t Init_Flag;
}Flight_Control_t;

typedef struct
{
	void (*Flight_Control_Get_Data)(void);
	void (*Flight_Control_Processing)(void);
}Flight_Control_Func_t;

extern Flight_Control_t Flight_Control;
extern Flight_Control_Func_t Flight_Control_Func;

#endif
