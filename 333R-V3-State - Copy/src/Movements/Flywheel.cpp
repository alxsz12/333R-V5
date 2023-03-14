#include "main.h"

sylib::SpeedControllerInfo motor_speed_controller (
        [](double rpm){return 5;}, // kV function
        1, // kP
        1, // kI
        1, // kD
        1, // kH
        false, // anti-windup enabled
        0, // anti-windup range
        false, // p controller bounds threshold enabled
        0, // p controller bounds cutoff enabled
        1, // kP2 for when over threshold
        0 // range to target to apply max voltage
    );
    
auto fw = sylib::Motor(9,3600, false, motor_speed_controller);

void Flywheel::flyTest()
{
    fw.set_velocity_custom_controller(3600); 
    printf("%d,%f,%f,%f,%d\n", sylib::millis(), fw.get_velocity(), fw.get_velocity_error(), fw.get_acceleration(), fw.get_efficiency());
}

void Flywheel::AShoot(int s, bool wait)
{
    if(s == 12)
    {
        FlywheelStateMachine::setState(FW_STATES::Twelve);
    }
    if(s == 115)
    {
        FlywheelStateMachine::setState(FW_STATES::ElevenH);
    }
    if(s == 11)
    {
        FlywheelStateMachine::setState(FW_STATES::Eleven);
    }
    if(s == 10)
    {
        FlywheelStateMachine::setState(FW_STATES::Ten);
    }

    if(wait){
        pros::delay(3000); //waits for it to spin up if its told to wait
    }
    IntakeStateMachine::setState(INTAKE_STATES::in); //shoots first disc
    pros::delay(125); //Waits for the shot
    IntakeStateMachine::setState(INTAKE_STATES::off);//turns off the intake
    pros::delay(1000); // waits for the fly to spin back up
    IntakeStateMachine::setState(INTAKE_STATES::in); //shoots again
    pros::delay(500); //waits to turn the intake off
    IntakeStateMachine::setState(INTAKE_STATES::off);
    def::controller.rumble("-");
}