/**
 * @file State_Machine.h
 * @author Leo Liu
 * @brief header file for state machine
 * @version 1.0
 * @date 2022-07-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __STATE_MACHINE_H
#define __STATE_MACHINE_H

#include "DR16_Remote.h"
#include "Robot_Control.h"
#include "Flight_Control.h"

#define State_Machine_Func_GroundInit \
{																			\
		&Remote_Control_Update,						\
}

typedef struct
{
	void (*Remote_Control_Update)(void);
}State_Machine_Func_t;

extern State_Machine_Func_t State_Machine_Func;

#endif
