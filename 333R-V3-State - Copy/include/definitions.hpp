#pragma once
#include "main.h"
#include "pros/adi.h"

#define DT_STATES DrivetrainStateMachine::MStates
#define FW_STATES FlywheelStateMachine::MStates
#define INTAKE_STATES IntakeStateMachine::MStates
#define END_STATES EndGameStateMachine::MStates

/*----------------------------------------------------------*/
/* Definitions.hpp is used to declare the defintions of all */
/* the motors, sensors, controller buttons, and constants   */
/* used for things like the drivetrain or odom etc.         */
/*----------------------------------------------------------*/

// Name used to access the defined devices
namespace def 
{
/*----------------------------------------------------------*/
/*------------------------- MOTORS -------------------------*/
/*----------------------------------------------------------*/

/*---------------------DrivetrainMotors---------------------*/
//-----Left------//
extern Motor mtr_dt_left_front;
extern Motor mtr_dt_left_mid;
extern Motor mtr_dt_left_back;
//-----Right------//
extern Motor mtr_dt_right_front;
extern Motor mtr_dt_right_mid;
extern Motor mtr_dt_right_back;
/*--------------------IntakeMotors--------------------------*/
extern Motor mtr_it;
/*-------------------FlywheelMotors-------------------------*/
extern Motor mtr_fw;

/*----------------------------------------------------------*/
/*----------------------- Pnumatics ------------------------*/
/*----------------------------------------------------------*/
//--Endgame--//
extern pros::ADIDigitalOut sol_endg;

/*----------------------------------------------------------*/
/*------------------------ Sensors -------------------------*/
/*----------------------------------------------------------*/

/*-------------------InterialSensors------------------------*/
extern pros::Imu imu_top;
extern pros::Imu imu_side;
extern pros::Imu imu_back;
extern pros::Imu imu_fl;
extern pros::Imu imu_fr;
/*------------------DistanceSensors------------------------*/
//--Back roller--//
extern pros::Distance d_backL;
extern pros::Distance d_backR;
//--Front intake--//
extern pros::Distance d_frontL;
extern pros::Distance d_frontR;
//--Disc sensors--//
extern pros::Distance d_discs;
/*-------------------ColorSensors--------------------------*/
//extern pros::Optical o_rollerR;
extern pros::Optical o_rollerL;
extern pros::Rotation r_rot;

/*----------------------------------------------------------*/
/*---------------------- Controller ------------------------*/
/*----------------------------------------------------------*/
extern Controller controller;

/*------------------------ Buttons -------------------------*/
//--Flywheel--//
extern ControllerButton btn_fw_shoot;
extern ControllerButton btn_fw_up;
extern ControllerButton btn_fw_down;
//--Intake/Roller/Indexer--//
extern ControllerButton btn_intake_toggle;
extern ControllerButton btn_intake_toggleout;
extern ControllerButton btn_intake_in;
extern ControllerButton btn_intake_out;
//--Endgame--//
extern ControllerButton btn_end_on;
extern ControllerButton btn_end_on2;

/*----------------------------------------------------------*/
/*---------------------- Constants -------------------------*/
/*----------------------------------------------------------*/

/*---------------------- Drivetrain ------------------------*/
const QLength DRIVE_WHEEL_DIAMETER = 2.75_in;//Wheel diamater
const extern double DRIVE_STRAIGHT_SCALE; // converts motor degrees to meters
const extern double DRIVE_TURN_SCALE;     // converts motor degrees to robot degrees
const double DRIVE_WHEEL_DIAMETER_IN = DRIVE_WHEEL_DIAMETER.convert(inch); 
const QLength DRIVE_WHEEL_CIRCUMFERENCE = DRIVE_WHEEL_DIAMETER * M_PI; 
const double DRIVE_WHEEL_CIRCUMFERENCE_IN = DRIVE_WHEEL_CIRCUMFERENCE.convert(inch); 
const QLength DRIVE_OFFSET = 13_in; //How far apart the sets are from each other
const double DRIVE_RATIO = 48.0 / 36.0; //The gears from the motors to the wheels
const double DRIVE_DEG_TO_IN = DRIVE_RATIO * DRIVE_WHEEL_CIRCUMFERENCE_IN / 360; // * 3 for 600rpm motors

const extern QSpeed DRIVE_MAX_SPEED;        // a measured linear velocity
const extern QAcceleration DRIVE_MAX_ACCEL; // approxamate measured linear acceleration
const double SET_DT_MAX = 1;//Maximum amount of power alloted to the drivetrain

const OdomState SET_ODOM_START = {0_in, 0_in, 0_deg}; // starting position of the robot on the field
//--Power curves--//
const double SET_DT_POW_STRAIGHT = 2; //Curves the straight accelerati0n 
const double SET_DT_POW_TURN = 3; // curves the turning acceleration

}