/**
 * @file Robot_Control.h
 * @author Leo Liu
 * @brief header file for robot control
 * @version 1.0
 * @date 2022-07-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __ROBOT_CONTROL_H
#define __ROBOT_CONTROL_H

#include "PID.h"
#include "DR16_Remote.h"
#include "Board_A_IMU.h"
#include "A2212_Motor.h"
#include "User_Defined_Math.h"
#include "State_Machine.h"
#include "Flight_Control.h"
#include "freertos.h"
#include "cmsis_os.h"
#include <stdint.h>

#define Robot_Func_GroundInit	\
{															\
		&Robot_Get_Data,					\
				&Robot_In_Control,		\
}

typedef struct
{
	uint8_t Is_Disabled;
}Robot_t;

typedef struct
{
	void (*Robot_Get_Data)(void);
	void (*Robot_In_Control)(void);
}Robot_Func_t;

extern Robot_t Robot;
extern Robot_Func_t Robot_Func;

#endif
