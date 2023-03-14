#include "definitions.hpp"
#include "main.h"
#include "okapi/api/units/QSpeed.hpp"
#include "okapi/api/util/logging.hpp"
#include "okapi/impl/device/motor/motorGroup.hpp"
#include "pros/motors.hpp"
#include "stateMachines/FlywheelStateMachine.hpp"
#include "stateMachines/IntakeStateMachine.hpp"

pros::Controller master (CONTROLLER_MASTER);// Gets the controller reference so that 
                                              // so that we can print to the controller
                                              // the voltage that the flywheel is currently
                                              // spinning at
int fwv = 9750;

FW_STATES FlywheelStateMachine::getState() { return mstate; }
void FlywheelStateMachine::setState(const FW_STATES istate)
{
    mstate = istate;
}

void FlywheelStateMachine::enableControl()
{
    mcontrolEnabled = true;
}

void FlywheelStateMachine::disableControl()
{
    mcontrolEnabled = false;
}

void FlywheelStateMachine::controlState(){
    if(mbtnShoot.changedToPressed()){
        if (getState() == FW_STATES::off) // if it's already shooting
            setState(FW_STATES::shoot);    // make it stop.
        else 
            setState(FW_STATES::off);  //Otherwise the flywheel should be off
    }
}   

void FlywheelStateMachine::speedu(){ // Function to be able to change the flywheel speed //AKA Speed Update 
    if(mbtnUp.changedToPressed()){   // by the voltage, and as you press the buttons  
        fwv+= 500;                   // the flywheel voltage will update by increments of 500
        //fwv = 11000;
        master.print(0, 0, "Flywheel: %d", fwv); // Then we can go and get the controller reference
    }                                // And print the new voltage after the voltage was changed
    if(mbtnDown.changedToPressed()){
         fwv-= 500;
        //fwv = 10000;
        master.print(0, 0, "Flywheel: %d", fwv);
    }
    master.print(0, 0, "Flywheel: %d", fwv); // Prints it at the end of the loop in case there was
    // a button pressed that did not register with printing on the screen
    if(fwv > 12000){
        fwv = 12000;
    }
    if(fwv < 0){
        fwv = 0;
    }
}


/*---------------------Flywheel PID----------------------*/
/*This will be used to try and have the flywheel operate */
/*around a set RPM using the RPM int variable and having */
/*PID iterate around the error that we are calculating   */
/*from the RPM value that we want, and the current       */
/*RPM that the flywheel rpm                              */
/*-------------------------------------------------------*/
//void FlywheelStateMachine::setRPM(const double itarget)
//{
//    enablePID();
//    mpidTarget = itarget;
//}     


/*-------------------------------------------------------*/
/*-------------------------------------------------------*/
/*-------------------------------------------------------*/
 
void FlywheelStateMachine::update() // updates the subsystem based on the state
{
    switch (mstate)
    {
        case FW_STATES::off: // Turns the flywheel Off
            mmtr.moveVoltage(0);
            break;
        case FW_STATES::shoot: // Spins the flywheel 
            mmtr.moveVoltage(fwv); //Moves the flywheel by the changeable variable
            
            break;
        case FW_STATES::Twelve:
            mmtr.moveVoltage(12000);
            break;
        case FW_STATES::ElevenH:
            mmtr.moveVoltage(11500);
            break;
        case FW_STATES::Eleven:
            mmtr.moveVoltage(11000);
            break;
        case FW_STATES::Ten:
            mmtr.moveVoltage(10000);
        break;
    }
}

void FlywheelStateMachine::run()
{
    while (true)
    {
        def::display.setChartData(6, def::mtr_fw.getActualVelocity() - 150);
        def::display.setMiscData(1, "FW Actual: " + std::to_string(def::mtr_fw.getActualVelocity()));
        def::display.setMiscData(2, "FW Target: " + std::to_string(def::mtr_fw.getTargetVelocity()));
        def::display.setMiscData(5, "FW TEMP: " + std::to_string(def::mtr_fw.getTemperature()));
        //def::display.setMiscData(6, "FW Target: " + std::to_string(def::mtr_fw.getTargetVelocity()));
        //Updating the brain here so that we can accurately see where the current velocity is
        //in comparison to the actual target value that the PID has calculated. 
        //This helps with debugging flywheel issues as we think it is issues with the PID, but
        //it helps with figuring that the problem is not the PID, but rather the flywheel
        //needs to he tuned properly with the values printed on the brain here
        if (mcontrolEnabled)
                controlState();
            speedu(); // We can add the speed update function here to run
        update();     // and update the voltage so that it updates as often as possible
        pros::delay(20);
    }
}

/* ------------------------- Devices ------------------------- */
Motor &FlywheelStateMachine::mmtr = def::mtr_fw;
/* -------------------------- State -------------------------- */

//FW_STATES FlywheelStateMachine::moverrideState = FW_STATES::off;
FW_STATES FlywheelStateMachine::mstate = FW_STATES::off;

bool FlywheelStateMachine::mcontrolEnabled = false;

ControllerButton &FlywheelStateMachine::mbtnShoot = def::btn_fw_shoot;

ControllerButton &FlywheelStateMachine::mbtnUp = def::btn_fw_up;
ControllerButton &FlywheelStateMachine::mbtnDown = def::btn_fw_down;