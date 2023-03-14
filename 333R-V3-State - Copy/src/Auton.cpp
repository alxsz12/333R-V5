#include "main.h"


// ------------------------Auton.cpp-----------------------------------------//
// This file is being used to control the different robot movements during   //
// the autonomous period. We have different enumerations depending on which  //
// color side and auton is selected. This allows us to be able to use our    //
// autons more effciently so we don't have to make a bunch of different      //
// autonomous programs depending on for example the color that we were given //
// We also use this file where we upload the current selected auton from the //
// brain to be able to always have it available. Then we have the different  //
// movements that we have written down below.                                //
/*---------------------------------------------------------------------------*/

Auton::Autons Auton::auton;    // default auton is deploy, if the sd card is not installed
Auton::Sides Auton::side;      // default side is Right if the sd card is not installed
Auton::Colors Auton::color;    // default color is Red if the sd card is not installed
Auton::Colors Auton::opponent; // default color is Red if the sd card is not installed

void Auton::readSettings() // read the sd card to set the settings
{
    FILE *file;                    // cpp a file object to be used later
    if (pros::usd::is_installed()) // checks if the sd card is installed before trying to read it
    {
        file = fopen("/usd/auton_settings.txt", "r"); // open the auton settings
        if (file)                                     // check to see if the file opened correctly
        {
            int autonSideAndColor; 
            fscanf(file, "%i", &autonSideAndColor);

            auton = (Auton::Autons)(autonSideAndColor / 100);
            side = (Auton::Sides)((autonSideAndColor / 10) % 10);
            color = (Auton::Colors)(autonSideAndColor % 10);
            opponent = color == Auton::Colors::Red ? Auton::Colors::Blue : Auton::Colors::Red;

            std::cout << "autonSideAndColor in sd card is " //prints to the terminal
            << std::to_string(autonSideAndColor) << ". Auton is " // the side
            << (int)auton << ", side is " << (int)side << ", and color is " << (int)color << "." << std::endl; // color
            // and the auton selected
        }
        else
        {
            std::cout << "/usd/auton_settings.txt is null."
                      << std::endl; // if the file didn't open right, tell the terminal
        }
        fclose(file); // close the file
    }
}
void Auton::suspendAsyncTask()
{
    masync_task.suspend();
}


void Auton::cEnable()
{
    switch(color)//sequence loop to run the selected color
    {
        case Colors::Red:
            Intake::Red();
        break; 
        case Colors::Blue:
            Intake::Blue();
        break;
    }
}

void Auton::runAuton(){ // Function that controls all of the autonomous movements
    Auton::readSettings(); //Loads the autons from the SD card
    Auton::suspendAsyncTask(); //Stops the async tasks

    mstartTime = mtimer.millis(); // Timer for the auton
    waitForImu(); // Wait for calibration
    //Setting the initial state and then disabiling the controls
    DrivetrainStateMachine::disableControl();
    FlywheelStateMachine::disableControl();
    IntakeStateMachine::disableControl();
    EndGameStateMachine::disableControl();
    //Sets the states to disable controller inputs
    DrivetrainStateMachine::setState(DT_STATES::busy);
    def::r_rot.reset_position();
    def::r_rot.reset();
    
    switch (auton){ //Sequence loop to contain the different autons

        case Autons::none:
            //Doing Nothing
        break;
        
        case Autons::Test:
        //Used to test auton movements
        break;

        case Autons::SAWP:
        switch(side)
            {
                case Sides::Left:
                    FlywheelStateMachine::setState(FW_STATES::ElevenH); // Starts the fly
                    Drivetrain::bDist(95);//driving back to the roller
                    Intake::RollerColor();//Roller
                    Drivetrain::straightForDistance(2.5_in);//drives forward
                    Drivetrain::turnToAngle(49_deg); //turns to face the center of the field
                    IntakeStateMachine::setState(INTAKE_STATES::out);//allows to intake discs
                    Drivetrain::setMaxSpeed(0.25); // slows the drivetrain down
                    Drivetrain::straightForDistance(26_in); //drives to intake the dics
                    pros::delay(1000); //lets the intake finish loading
                    IntakeStateMachine::setState(INTAKE_STATES::off); //turns the intake off
                    Drivetrain::turnToAngle(-25_deg); //turns to face the high goal
                    Flywheel::AShoot(12, false); //shoots at full
                    Drivetrain::turnToAngle(49_deg); //turns to face the center of the field
                    IntakeStateMachine::setState(INTAKE_STATES::out); // allows to intake discs
                    Drivetrain::straightForDistance(24_in); //drives to the other end of the field
                    Drivetrain::turnToAngle(-50_deg); // turns back to face the high goal 
                    Drivetrain::straightForDistance(2_in); // drives forward
                    //Flywheel::AShoot115(false);
                break;

                case Sides::Right:
                    IntakeStateMachine::setState(INTAKE_STATES::out); // Starts the intake 
                    FlywheelStateMachine::setState(FW_STATES::ElevenH); //Starts the flywheel
                    pros::delay(250); // waits for the intake to start
                    Drivetrain::straightForDistance(16_in); //drives forward to the first disc
                    pros::delay(900); // waits for the disc to intake
                    IntakeStateMachine::setState(INTAKE_STATES::off);//turns the intake off
                    Drivetrain::turnToAngle(30.5_deg); //turns to the high goal
                    //Flywheel::AShoot115(false); //shoots the discs
                    pros::delay(900); // waits for the fly to stop shooting 
                    Drivetrain::turnToAngle(-40_deg); //turns to the roller
                    Drivetrain::straightForDistance(-24_in); //drives to the roller
                    Drivetrain::turnToAngle(2.5_deg);//Turns into the roller
                    Drivetrain::bDist(95);//driving back to the roller
                    Intake::RollerColor();//Rols to the right color
                    Drivetrain::straightForDistance(2.5_in);//drives forward
                break;
            }

        break;

        case Autons::HSWP:
            
            Drivetrain::bDist(95);//driving back to the roller
            Intake::RollerColor();//Roller
            Drivetrain::straightForDistance(2.5_in);//drives forward
            Drivetrain::turnToAngle(49_deg); //turns to face the center of the field
            IntakeStateMachine::setState(INTAKE_STATES::out);//allows to intake discs
            Drivetrain::setMaxSpeed(0.25); //slows down the drivetrain to intake discs
            Drivetrain::straightForDistance(26_in); //drives to intake the dics
            pros::delay(1000); // delays to allow the intake to finish loading
            IntakeStateMachine::setState(INTAKE_STATES::off); //turns the intake off
            Drivetrain::turnToAngle(-25_deg); //turns to face the high goal
            //Flywheel::AShoot115(true);
            
        break;

        case Autons::PROG:
            FlywheelStateMachine::setState(FW_STATES::Twelve); //Starts the flywheel
            Drivetrain::straightForDistance(2_in); // drives away from the wall
            Drivetrain::turnToAngle(90_deg); // turns to face the blue goal
            //Flywheel::AShoot12(false); //fires the discs
            Drivetrain::turnToAngle(4_deg); //turns back to the roller
            Drivetrain::bDist(95);//runs back to the roller
            Intake::SkillsColor(); //rolls the roller
            Drivetrain::straightForDistance(2.5_in); // drives away
            Drivetrain::turnToAngle(-45_deg); //faces the other roller
            Drivetrain::straightForDistance(15_in); //drives to the roler
            Drivetrain::turnToAngle(90_deg); // turns to face away from the roller
            Drivetrain::bDist(95); //drives back into the roller
            Intake::SkillsColor(); //rolls the roller
            Drivetrain::straightForDistance(2.5_in); //drives away from the roller
            Drivetrain::turnToAngle(4_deg); // turns away from the roller
            Drivetrain::straightForDistance(7_in); //drives forward
            Drivetrain::turnToAngle(45_deg); //turns to face the discs
            IntakeStateMachine::setState(INTAKE_STATES::out); // starts the intake
            Drivetrain::straightForDistance(36_in); //drives forward
            Drivetrain::turnToAngle(-37.5_deg); //turns to face the goal
            IntakeStateMachine::setState(INTAKE_STATES::off); // turns off the intake
            //Flywheel::AShoot10(false); // shoots at the high goal
            Drivetrain::turnToAngle(45_deg); // turns to face the other end of the field
            Drivetrain::straightForDistance(24_in); // drives forward
            Drivetrain::turnToAngle(-90_deg); //turns to face the high goal
            //Flywheel::AShoot10(false); // shoots at the high goal
            Drivetrain::turnToAngle(45_deg); // turns to face the other end of rhe field
            Drivetrain::straightForDistance(12_in); // drives to the end of the field
            Drivetrain::turnToAngle(180_deg); // turns to face the back of the roler
            Drivetrain::bDist(95); // drives to the roller
            Intake::SkillsColor(); // rolls the roller
            Drivetrain::turnToAngle(-135_deg); // turns to face the other end of the field
            EndGameStateMachine::setState(END_STATES::on);
        break;

        case Autons::PROGS:
            FlywheelStateMachine::setState(FW_STATES::Twelve); //Starts the flywheel
            Drivetrain::straightForDistance(2_in);
            Drivetrain::turnToAngle(90_deg); // turns to face the blue goal
            //Flywheel::AShoot12(false); //fires the discs
            Drivetrain::turnToAngle(4_deg); //turns back to the roller
            Drivetrain::bDist(95);//runs back to the roller
            Intake::SkillsColor();
            Drivetrain::straightForDistance(2.5_in);
            Drivetrain::turnToAngle(-45_deg);
            Drivetrain::straightForDistance(15_in);
            Drivetrain::turnToAngle(90_deg);
            Drivetrain::bDist(95);
            Intake::SkillsColor();
            Drivetrain::turnToAngle(135_deg);
            Drivetrain::straightForDistance(5_in);
            Drivetrain::turnToAngle(45_deg);
            EndGameStateMachine::setState(END_STATES::on);
        break;
        }
}

void Auton::startAsyncTaskWithSettings(std::function<bool()> iasyncCondition, std::function<void()> iasyncAction)
{
    masyncCondition = iasyncCondition;
    masyncAction = iasyncAction;
    masync_task.resume();
}
void Auton::async_task_func(void *)
{
    while (true)
    {
        if (masyncCondition())
        {
            masyncAction();
            masync_task.suspend();
        }
        pros::delay(20);
    }
}
std::function<bool()> Auton::masyncCondition = []()
{ return false; };
std::function<void()> Auton::masyncAction;
pros::Task Auton::masync_task(Auton::async_task_func);

void Auton::startTaskAfterDelay(QTime idelay, std::function<void()> iaction)
{
    mdelayAction = iaction;
    mdelayTime = idelay;
    mdelay_task.resume();
}
void Auton::delay_task_func(void *)
{
    while (true)
    {
        if (mtimer.millis() - mstartTime > mdelayTime)
        {
            mdelayAction();
            mdelay_task.suspend();
        }
        pros::delay(20);
    }
}
std::function<void()> Auton::mdelayAction;
Timer Auton::mtimer = Timer();
QTime Auton::mstartTime = 0_ms;
QTime Auton::mdelayTime = 2_min;
pros::Task Auton::mdelay_task(Auton::delay_task_func);