#include "main.h"

void Intake::RollerColor()
{
    def::r_rot.reset_position();
    IntakeStateMachine::setState(INTAKE_STATES::in);
    Drivetrain::moveArcade(-0.3, 0.0, false);
        while (def::r_rot.get_position() < 90) 
        {// while its not in the range of the color
        pros::delay(100);
        }        
        Drivetrain::moveArcade(0.0, 0.0, false);       
        IntakeStateMachine::setState(INTAKE_STATES::off);  //then it stops the motor
        def::controller.rumble("-"); // and rumbles the controller
        pros::delay(20); // to signify that it completed the loop
}

void Intake::SkillsColor()
{
    def::r_rot.reset_position();
    IntakeStateMachine::setState(INTAKE_STATES::in);
    Drivetrain::moveArcade(-0.1, 0.0, false);
        while (def::r_rot.get_position() <= 270) 
        {// while its not in the range of the color
        pros::delay(100);
        }        
        Drivetrain::moveArcade(0.0, 0.0, false);       
        IntakeStateMachine::setState(INTAKE_STATES::off);  //then it stops the motor
        def::controller.rumble("-"); // and rumbles the controller
        pros::delay(20); // to signify that it completed the loop
        def::r_rot.reset_position();
        def::r_rot.set_position(10);
}

void Intake::Red()
{
   
        while (def::r_rot.get_position() < 90) 
        {// while its not in the range of the color
            def::mtr_it.moveVoltage(12000);
            Drivetrain::moveArcade(-0.15, 0.0, false);
        }
            def::mtr_it.moveVoltage(0);
        
        Drivetrain::moveArcade(0.0, 0.0, false);       
        def::mtr_it.moveVoltage(0);  //then it stops the motor
        def::controller.rumble("-"); // and rumbles the controller
        pros::delay(20); // to signify that it completed the loop
}

void Intake::Blue()
{       
        IntakeStateMachine::setState(INTAKE_STATES::in); 
        while (200 <= (def::o_rollerL.get_hue()) <= 250)
        {// while its not in the rang of the color
            pros::delay(100);
        } 
        IntakeStateMachine::setState(INTAKE_STATES::off); 
        //Drivetrain::moveArcade(0.0, 0.0, false);
        //mmtr.moveVoltage(0); //then it stops the motor
        //def::controller.rumble("-");// and rumbles the controller
        //pros::delay(20); //to signify that it completed the loop
}


// void Flywheel::AShoot115(bool wait)
// {
//     FlywheelStateMachine::setState(FW_STATES::ElevenH);//spins to 12000
//     if(wait){
//         pros::delay(1000); //waits for it to spin up if its told to wait
//     }
//     IntakeStateMachine::setState(INTAKE_STATES::in); //shoots first disc
//     pros::delay(125); //Waits for the shot
//     IntakeStateMachine::setState(INTAKE_STATES::off);//turns off the intake
//     pros::delay(1575); // waits for the fly
//     IntakeStateMachine::setState(INTAKE_STATES::in); //shoots again
//     pros::delay(125); //waits tp turn the motors off
//     IntakeStateMachine::setState(INTAKE_STATES::off);
//     pros::delay(1575);
//     IntakeStateMachine::setState(INTAKE_STATES::in); //shoots again
//     pros::delay(125);
//     IntakeStateMachine::setState(INTAKE_STATES::off); //shoots again
//     pros::delay(1575);
//     IntakeStateMachine::setState(INTAKE_STATES::in); //shoots again
//     pros::delay(125);
//     IntakeStateMachine::setState(INTAKE_STATES::off); //shoots again
//     def::controller.rumble("-");
// }
// void Flywheel::AShoot11(bool wait)
// {
//     FlywheelStateMachine::setState(FW_STATES::Eleven);//spins to 12000
//     if(wait){
//         pros::delay(1500); //waits for it to spin up if its told to wait
//     }
//     IntakeStateMachine::setState(INTAKE_STATES::in); //shoots first disc
//     pros::delay(125); //Waits for the shot
//     IntakeStateMachine::setState(INTAKE_STATES::off);//turns off the intake
//     pros::delay(1250); // waits for the fly
//     IntakeStateMachine::setState(INTAKE_STATES::in); //shoots again
//     pros::delay(125); //waits tp turn the motors off
//     IntakeStateMachine::setState(INTAKE_STATES::off);
//     pros::delay(1250);
//     IntakeStateMachine::setState(INTAKE_STATES::in); //shoots again
//     pros::delay(125);
//     IntakeStateMachine::setState(INTAKE_STATES::off); //shoots again
//     pros::delay(1250);
//     IntakeStateMachine::setState(INTAKE_STATES::in); //shoots again
//     pros::delay(125);
//     IntakeStateMachine::setState(INTAKE_STATES::off); //shoots again
//     def::controller.rumble("-");
// }

// void Flywheel::AShoot10(bool wait)
// {
//     FlywheelStateMachine::setState(FW_STATES::Ten);//spins to 12000
//     if(wait){
//         pros::delay(3000); //waits for it to spin up if its told to wait
//     }
//     IntakeStateMachine::setState(INTAKE_STATES::in); //shoots first disc
//     pros::delay(125); //Waits for the shot
//     IntakeStateMachine::setState(INTAKE_STATES::off);//turns off the intake
//     pros::delay(1575); // waits for the fly
//     IntakeStateMachine::setState(INTAKE_STATES::in); //shoots again
//     pros::delay(125); //waits tp turn the motors off
//     IntakeStateMachine::setState(INTAKE_STATES::off);
//     pros::delay(1575);
//     IntakeStateMachine::setState(INTAKE_STATES::in); //shoots again
//     pros::delay(125);
//     IntakeStateMachine::setState(INTAKE_STATES::off); //shoots again
//     pros::delay(1575);
//     IntakeStateMachine::setState(INTAKE_STATES::in); //shoots again
//     pros::delay(125);
//     IntakeStateMachine::setState(INTAKE_STATES::off); //shoots again
//     pros::delay(1575);
//     IntakeStateMachine::setState(INTAKE_STATES::in); //shoots again
//     pros::delay(125);
//     IntakeStateMachine::setState(INTAKE_STATES::off); //shoots again
//     def::controller.rumble("-");
// }
