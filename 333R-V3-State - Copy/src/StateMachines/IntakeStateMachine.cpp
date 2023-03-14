#include "main.h"

INTAKE_STATES IntakeStateMachine::getState() { return mstate; }
void IntakeStateMachine::setState(const INTAKE_STATES istate)
{
    mstate = istate;
}

void IntakeStateMachine::enableControl()
{
    mcontrolEnabled = true;
}

void IntakeStateMachine::disableControl()
{
    mcontrolEnabled = false;
}

void IntakeStateMachine::controlState() // update the state based on controller input
{

    if (mbtnToggle.changedToPressed()) // if the toggle button is pressed
    {
        if (getState() == INTAKE_STATES::in) // if it's already going in,
            setState(INTAKE_STATES::off);    // make it go out.
        else                                 // otherwise,
            setState(INTAKE_STATES::in);     // make in go in.
        mtoggling = true;                    // note that the system should remain the way it was toggled
    }
    if (mbtnToggleout.changedToPressed()) // if the toggle button is pressed
    {
        if (getState() == INTAKE_STATES::out) // if it's already going in,
            setState(INTAKE_STATES::off);    // make it go out.
        else                                 // otherwise,
            setState(INTAKE_STATES::out);     // make in go in.
        mtoggling = true;                    // note that the system should remain the way it was toggled
    }
    if (mbtnIn.isPressed())
    {
        setState(INTAKE_STATES::in);
        mtoggling = false; // ignore the toggled state in future loops
    }
    else if (mbtnOut.isPressed())
    {
        setState(INTAKE_STATES::out);
        mtoggling = false; // ignore the toggled state in future loops
    }
    else if (mtoggling == false && mstate != INTAKE_STATES::override) // if it's supposed to ignore toggling...
    {
        setState(INTAKE_STATES::off); // just turn off
    }
}


void IntakeStateMachine::update() // moves the intake based on the state
{
    switch (mstate)
    {
    case INTAKE_STATES::off: //Turns off the intake
        mmtr.moveVoltage(0);
        break;
    case INTAKE_STATES::in: // Spins the intake forward
        mmtr.moveVoltage(12000);
        pros::delay(50);
        while (mmtr.getActualVelocity() < 2)
        {
            mmtr.moveVoltage(-12000);
            pros::delay(100);
            mmtr.moveVoltage(12000);
            pros::delay(100);
        }
        break;
    case INTAKE_STATES::out: //Spins the intake in reverse
        mmtr.moveVoltage(-12000);
        pros::delay(50);
        while (mmtr.getActualVelocity() > -2)
        {
            mmtr.moveVoltage(12000);
            pros::delay(100);
            mmtr.moveVoltage(-12000);
            pros::delay(100);
        }
        break;
    case INTAKE_STATES::override: //When we need to override a current state
        mmtr.moveVoltage(-12000);
        break;
    }
}

void IntakeStateMachine::run()
{
    while (true)
    {   
        def::display.setChartData(7, def::mtr_it.getActualVelocity() - 150);
        //def::display.setMiscData(3, "IN Actual: " + std::to_string(def::mtr_it_m.getActualVelocity()));
        //def::display.setMiscData(4, "IN Target: " + std::to_string(def::mtr_it_m.getTargetVelocity()));
        def::display.setMiscData(3, "IN Error: " + std::to_string(def::mtr_it.getVelocityError()));
        def::display.setMiscData(4, "IN Temp: " + std::to_string(def::mtr_it.getTemperature()));
        //def::display.setMiscData(3, "3 HUE: " + std::to_string(def::o_rollerR.get_hue()));
        //def::display.setMiscData(4, "4 HUE " + std::to_string(def::o_rollerL.get_hue()));

        if (mcontrolEnabled)
            controlState();
        update();
        pros::delay(20);
    }
}

/* ----------------------------------------------------------- */
/*                     Private Information                     */
/* ----------------------------------------------------------- */
/* ------------------------- Devices ------------------------- */
Motor &IntakeStateMachine::mmtr = def::mtr_it;

/* -------------------------- State -------------------------- */
INTAKE_STATES IntakeStateMachine::mstate = INTAKE_STATES::off;
bool IntakeStateMachine::mtoggling = false;
bool IntakeStateMachine::mcontrolEnabled = false;
INTAKE_STATES IntakeStateMachine::moverrideState = INTAKE_STATES::off;

/* ------------------------- Controls ------------------------ */
ControllerButton &IntakeStateMachine::mbtnToggle = def::btn_intake_toggle;
ControllerButton &IntakeStateMachine::mbtnToggleout = def::btn_intake_toggleout;
ControllerButton &IntakeStateMachine::mbtnIn = def::btn_intake_in;
ControllerButton &IntakeStateMachine::mbtnOut = def::btn_intake_out;