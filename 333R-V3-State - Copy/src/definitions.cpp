#include "main.h"

namespace def
{
/*----------------------------------------------------------*/
/*------------------------- MOTORS -------------------------*/
/*----------------------------------------------------------*/

/*---------------------DrivetrainMotors---------------------*/
//-----Left------//
Motor mtr_dt_left_front(-15); 
Motor mtr_dt_left_mid(-16);
Motor mtr_dt_left_back(-17); 
//-----Right------//
Motor mtr_dt_right_front(18); 
Motor mtr_dt_right_mid(19);
Motor mtr_dt_right_back(20); 

/*-----------------------IntakeMotor-----------------------*/
Motor mtr_it(10);

/*----------------------FlhywheelMotor---------------------*/
Motor mtr_fw(9);

/*----------------------------------------------------------*/
/*----------------------- Pnumatics ------------------------*/
/*----------------------------------------------------------*/
//--Endgame--//
pros::ADIDigitalOut sol_endg('A');

/*----------------------------------------------------------*/
/*------------------------ Sensors -------------------------*/
/*----------------------------------------------------------*/

/*-------------------InterialSensors------------------------*/
pros::Imu imu_side(13);
pros::Imu imu_top(12);
pros::Imu imu_back(2);
pros::Imu imu_fl(1);
pros::Imu imu_fr(11);
/*------------------DistanceSensors------------------------*/
//--Back roller--//
pros::Distance d_backL(7);
pros::Distance d_backR(8);
//--Front intake--//
pros::Distance d_frontL(14);
pros::Distance d_frontR(5);
//--Disc sensors--//
pros::Distance d_discs(6);
/*------------------ColorSensors---------------------------*/
//pros::Optical o_rollerR(3);
pros::Optical o_rollerL(4);
pros::Rotation r_rot(3);

/*----------------------------------------------------------*/
/*---------------------- Controller ------------------------*/
/*----------------------------------------------------------*/
//-----------Controller
Controller controller = Controller();

//Controller Button Definitions
ControllerButton btn_indexer_spin = ControllerDigital::L2;

ControllerButton btn_fw_shoot = ControllerDigital::L1;

ControllerButton btn_fw_up = ControllerDigital::up;
ControllerButton btn_fw_down = ControllerDigital::down;


ControllerButton btn_intake_toggle = ControllerDigital::X;
ControllerButton btn_intake_toggleout = ControllerDigital::Y;
ControllerButton btn_intake_in = ControllerDigital::R2;
ControllerButton btn_intake_out = ControllerDigital::R1;

ControllerButton btn_end_on = ControllerDigital::left;
ControllerButton btn_end_on2 = ControllerDigital::right;

/*----------------------------------------------------------*/
/*---------------------- Constants -------------------------*/
/*----------------------------------------------------------*/

/*---------------------- Drivetrain ------------------------*/

//Drivetrain drivetrain = Drivetrain(); // used by DrivetrainStateMachine for drivetrain control

//DrivetrainStateMachine sm_dt = DrivetrainStateMachine(); // state machine to control the drivetrain

//const double DRIVE_STRAIGHT_SCALE = 1922;
const double DRIVE_TURN_SCALE = 15;
const QSpeed DRIVE_MAX_SPEED = 1.3_mps;      // a measured linear velocity
const QAcceleration DRIVE_MAX_ACCEL = 1.1_G; // approxamate measured linear acceleration

}