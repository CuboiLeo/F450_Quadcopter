/**
 * @file Flight_Control.c
 * @author Leo Liu
 * @brief flight control for the quadcopter
 * @version 1.0
 * @date 2023-09-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "Flight_Control.h"

void Flight_Control_Get_Data(void);
void Flight_Control_Processing(void);

Flight_Control_t Flight_Control;
Flight_Control_Func_t Flight_Control_Func = Flight_Control_Func_GroundInit;
#undef Flight_Control_Func_GroundInit

void Flight_Control_Get_Data(void)
{
	Flight_Control.Current.Pitch = 0.707f*Board_A_IMU.Export_Data.Pitch + 0.707f*Board_A_IMU.Export_Data.Roll;
	Flight_Control.Current.Roll = -(0.707f*Board_A_IMU.Export_Data.Pitch - 0.707f*Board_A_IMU.Export_Data.Roll);
	Flight_Control.Current.Yaw = -Board_A_IMU.Export_Data.Total_Yaw;
	Flight_Control.Current.Gyro_Pitch = 0.707f*Board_A_IMU.Export_Data.Gyro_Pitch + 0.707f*Board_A_IMU.Export_Data.Gyro_Roll;
	Flight_Control.Current.Gyro_Roll = -(0.707f*Board_A_IMU.Export_Data.Gyro_Pitch - 0.707f*Board_A_IMU.Export_Data.Gyro_Roll);
	Flight_Control.Current.Yaw = -Board_A_IMU.Export_Data.Total_Yaw;
	Flight_Control.Current.Gyro_Yaw = -Board_A_IMU.Export_Data.Gyro_Yaw;
	Flight_Control.Current.Altitude = 0;
	
	Flight_Control.Target.Pitch = DR16_Export_Data.Remote_Control.Joystick_Right_Vy/33.0f;
	Flight_Control.Target.Roll = DR16_Export_Data.Remote_Control.Joystick_Right_Vx/33.0f;
	Flight_Control.Target.Yaw += DR16_Export_Data.Remote_Control.Joystick_Left_Vx/8000.0f;
	Flight_Control.Target.Altitude = 0;
}

void Flight_Control_Processing(void)
{
	Flight_Control.Output.Throttle = (DR16_Export_Data.Remote_Control.Joystick_Left_Vy+660.0f)*3.0f;
	Flight_Control.Output.Pitch = Pitch_Angle_PID.Kp*(Flight_Control.Target.Pitch-Flight_Control.Current.Pitch)+Pitch_Angle_PID.Kd*(-Flight_Control.Current.Gyro_Pitch);
	Flight_Control.Output.Roll = Roll_Angle_PID.Kp*(Flight_Control.Target.Roll-Flight_Control.Current.Roll)+Roll_Angle_PID.Kd*(-Flight_Control.Current.Gyro_Roll);
	Flight_Control.Output.Yaw = Yaw_Angle_PID.Kp*(Flight_Control.Target.Yaw-Flight_Control.Current.Yaw)+Yaw_Angle_PID.Kd*(-Flight_Control.Current.Gyro_Yaw);
	Flight_Control.Output.Altitude = 0;
	
	Flight_Control.Output.Pitch_KF = Kalman_Filter_Func.First_Order_Kalman_Filter(&Pitch_KF,Flight_Control.Output.Pitch);
	Flight_Control.Output.Roll_KF = Kalman_Filter_Func.First_Order_Kalman_Filter(&Roll_KF,Flight_Control.Output.Roll);
	Flight_Control.Output.Yaw_KF = Kalman_Filter_Func.First_Order_Kalman_Filter(&Yaw_KF,Flight_Control.Output.Yaw);
//	
//	Flight_Control.Output.Pitch_Smooth = Ramp_Calc_Func.Ramp(Flight_Control.Output.Pitch_Smooth,Flight_Control.Output.Pitch_KF,10.0f);
//	Flight_Control.Output.Roll_Smooth = Ramp_Calc_Func.Ramp(Flight_Control.Output.Roll_Smooth,Flight_Control.Output.Roll_KF,0.1f);
//	Flight_Control.Output.Yaw_Smooth = Ramp_Calc_Func.Ramp(Flight_Control.Output.Yaw_Smooth,Flight_Control.Output.Yaw_KF,0.1f);
	
	A2212_Motor.FL_Output = VAL_LIMIT(Flight_Control.Output.Throttle - Flight_Control.Output.Yaw_KF - Flight_Control.Output.Pitch_KF + Flight_Control.Output.Roll_KF + Flight_Control.Output.Altitude,A2212_OUTPUT_LIMIT,0);
	A2212_Motor.FR_Output = VAL_LIMIT(Flight_Control.Output.Throttle + Flight_Control.Output.Yaw_KF - Flight_Control.Output.Pitch_KF - Flight_Control.Output.Roll_KF + Flight_Control.Output.Altitude,A2212_OUTPUT_LIMIT,0);
	A2212_Motor.RL_Output = VAL_LIMIT(Flight_Control.Output.Throttle + Flight_Control.Output.Yaw_KF + Flight_Control.Output.Pitch_KF + Flight_Control.Output.Roll_KF + Flight_Control.Output.Altitude,A2212_OUTPUT_LIMIT,0);
	A2212_Motor.RR_Output = VAL_LIMIT(Flight_Control.Output.Throttle - Flight_Control.Output.Yaw_KF + Flight_Control.Output.Pitch_KF - Flight_Control.Output.Roll_KF + Flight_Control.Output.Altitude,A2212_OUTPUT_LIMIT,0);
}
