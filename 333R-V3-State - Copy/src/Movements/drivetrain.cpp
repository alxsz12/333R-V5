#include "main.h"

//------------------------Motor References-----------------//

//Front Motors
Motor & Drivetrain::mmtrLeftFront = def::mtr_dt_left_front;
Motor & Drivetrain::mmtrRightFront = def::mtr_dt_right_front;

//Back Motors
Motor & Drivetrain::mmtrRightBack = def::mtr_dt_right_back;
Motor & Drivetrain::mmtrLeftBack = def::mtr_dt_left_back;

//Middle Motors
Motor & Drivetrain::mmtrRightMid = def::mtr_dt_right_mid;
Motor & Drivetrain::mmtrLeftMid = def::mtr_dt_left_mid;

// ----------------------Okapi Chassis---------------------//
/* We are using the Okapilib library to make the chassis   */
std::shared_ptr<ChassisController> Drivetrain::mchassis =
    ChassisControllerBuilder()
        .withMotors({Drivetrain::mmtrLeftFront, Drivetrain::mmtrLeftBack},
                    {Drivetrain::mmtrRightFront, Drivetrain::mmtrRightBack})
        .withDimensions(AbstractMotor::gearset::blue,
                        {{def::DRIVE_WHEEL_DIAMETER, def::DRIVE_OFFSET}, imev5BlueTPR})
        .build(); // chassis object for using Pathfilder through okapi
// Variables
double Drivetrain::mmaxSpeed = def::SET_DT_MAX; // Setting the max speed
bool Drivetrain::menabled = true; //Enabler/Disabler boolean

// Making the Async profile to use Async actions in the future

double Drivetrain::getMaxSpeed() { return mmaxSpeed; } // Getter method to get the max value of the drivetrain
void Drivetrain::setMaxSpeed(double imaxSpeed) { mmaxSpeed = imaxSpeed; } //Setter method to set the max value of the drivetrain

bool Drivetrain::isEnabled() { return menabled; }
/* -------------------- Odometry Accessors ------------------- */
OdomState Drivetrain::getState() // get position as OdomState
{
    return CustomOdometry::getState();
}
QLength Drivetrain::getXPos() { return CustomOdometry::getX(); }
QLength Drivetrain::getYPos() { return CustomOdometry::getY(); }
QAngle Drivetrain::getTheta() { return CustomOdometry::getTheta(); }


// ---------------------Enabler Functions-------------------------//
void Drivetrain::enable() // allows movements to be startable
{
    menabled = true;
}

void Drivetrain::disable() // stops active movemnts
{
    menabled = false;
    moveTank(0, 0, false);
}

//--------------------Lock & Unlocking Functions -------------------//

void Drivetrain::lock()
{
    mmtrLeftFront.setBrakeMode(AbstractMotor::brakeMode::hold);
    mmtrRightFront.setBrakeMode(AbstractMotor::brakeMode::hold);
    mmtrRightBack.setBrakeMode(AbstractMotor::brakeMode::hold);
    mmtrLeftBack.setBrakeMode(AbstractMotor::brakeMode::hold);
    mmtrRightMid.setBrakeMode(AbstractMotor::brakeMode::hold);
    mmtrLeftMid.setBrakeMode(AbstractMotor::brakeMode::hold);
}
void Drivetrain::unlock()
{
    mmtrLeftFront.setBrakeMode(AbstractMotor::brakeMode::coast);
    mmtrRightFront.setBrakeMode(AbstractMotor::brakeMode::coast);
    mmtrRightBack.setBrakeMode(AbstractMotor::brakeMode::coast);
    mmtrLeftBack.setBrakeMode(AbstractMotor::brakeMode::coast);
    mmtrRightMid.setBrakeMode(AbstractMotor::brakeMode::coast);
    mmtrLeftMid.setBrakeMode(AbstractMotor::brakeMode::coast);
}

void Drivetrain::moveIndependent(
    double ileft, double iright, const bool idesaturate) // moves each motor {lf, rf, rb, lb} in range [-1,1]
{
    if (idesaturate) // desaturates values
    {
        std::array<double, 2> motor_values =
            util::scaleToFit<2>(mmaxSpeed, {ileft, iright});
        ileft = motor_values[0];
        iright = motor_values[1];
    }
    else
    {
        util::chop<double>(-1, 1, ileft);
        util::chop<double>(-1, 1, iright);
    }
    // moves all of the motors by voltage
    
    mmtrLeftFront.moveVoltage(12000 * ileft); 
    mmtrRightFront.moveVoltage(12000 * iright);
    mmtrRightBack.moveVoltage(12000 * iright);
    mmtrLeftBack.moveVoltage(12000 * ileft);
    mmtrRightMid.moveVoltage(12000 * iright);
    mmtrLeftMid.moveVoltage(12000 * ileft);
    //All of the motors are set to max voltage, 
    //then we have the double values to be a number 
    //less than zero, so then we can lower the output
    //of the voltage to the motors
}
void Drivetrain::moveTank(double ileft, double iright,
                          const bool idesaturate) // spins the left side and right side motors at
                                                  // certian speeds in range [-1,1]
{
    if (idesaturate) // desaturates values
    {
        std::array<double, 2> motor_values = util::scaleToFit<2>(mmaxSpeed, {ileft, iright});
        ileft = motor_values[0];
        iright = motor_values[1];
    }
    Drivetrain::moveIndependent(
        ileft, iright,
        false); // don't try to desaturate, because the values have already been desaturated
}
void Drivetrain::moveArcade(
    double iforward, double iturn,
    const bool idesaturate) // moves the robot with arcade-style inputs in range [-1,1]
{
    if (idesaturate) // desaturates values
    {
        std::array<double, 2> motor_values = {iforward + iturn, iforward - iturn};
        util::scaleToFit<2>(mmaxSpeed, motor_values);                  // modifies reference to motor_values
        Drivetrain::moveIndependent(motor_values[0], motor_values[1]); // moves the motors from within the if to
                                                                       // prevent the need to copy values
    }
    else
    {
        Drivetrain::moveIndependent(iforward + iturn, iforward - iturn, false); // don't desaturate
    }
}

void Drivetrain::arcadeFor(const double iforward, const double iturn, const int ims)
{ // Moves the robot with aracade style inputs for a certain amount of time
    Drivetrain::moveArcade(iforward, iturn);
    pros::delay(ims);
    Drivetrain::moveArcade(0, 0, false);
}

//-----------------------------------------------------------------------//

void Drivetrain::straightForDistance(QLength idistance, PID imagnitudePID, Slew imagnitudeSlew, PID iturnPID)
{
    double inStart = mmtrLeftFront.getPosition() * def::DRIVE_DEG_TO_IN; // starting distance of the motors
    QAngle startAngle = Drivetrain::getTheta();                          // starting angle of the robot

    enable();
    while (menabled && !imagnitudePID.isSettled())
    {
        double angleError = util::wrapDeg180((startAngle - Drivetrain::getTheta()).convert(degree)); // calculates the angle the robot needs to turn
        double inError = idistance.convert(inch) -
                         mmtrLeftFront.getPosition() * def::DRIVE_DEG_TO_IN +
                         inStart; // calculates how far the robot needs to drive

        Drivetrain::moveArcade(imagnitudeSlew.iterate(imagnitudePID.iterate(inError)), -iturnPID.iterate(angleError), false);

        pros::delay(20);
    }
    Drivetrain::moveArcade(0, 0, false); // After the loop ends, we stop the movement of the robot
    def::controller.rumble("-"); // Rumble the controller as an indicater that the robot reached the target
}

void Drivetrain::fDist(int dist) // Moves thr robot forward until the distance sensors reach the target
    {
        enable(); 
        while(menabled && ((def::d_frontL.get() + def::d_frontR.get())/2) > dist ){
            Drivetrain::moveArcade(0.45, 0, false);
            pros::delay(20);
        }
            def::controller.rumble("-");

        Drivetrain::moveArcade(0,0, false);
    }

void Drivetrain::bDist(int dist) // Moves the robot backward until the distance sensors reach the target
    {
        enable(); 
        while(menabled && ((def::d_backL.get() + def::d_backR.get())/2) > dist ){
            Drivetrain::moveArcade(-0.3, 0, false);
            pros::delay(20);
        }
            def::controller.rumble("-");
        Drivetrain::moveArcade(0,0, false);
    }

/*---------------------------------------------------------------------*/
/*-----------------------!!THIS-ONE-WORKS!!----------------------------*/
/*---------------------------------------------------------------------*/
void Drivetrain::turnToAngle(QAngle iangle, PID ipid)
{

    //QAngle startAngle = Drivetrain::getTheta(); // Getting the starting pos. of the robot
    QAngle targetAngle = iangle;
  // Enable the drivetrain and enter a loop that runs until the PID object is settled or the drivetrain is disabled
    enable();
    while (menabled && !ipid.isSettled())
    {
        // Use the inertial sensor to read the current angle of the robot
        //double currentAngle = ((def::imu_side.get_heading()+def::imu_top.get_heading())/2);

        // Calculate the angle error between the current angle and the target angle
        double angleError = util::wrapDeg180((targetAngle.convert(degree) 
        - ((def::imu_side.get_heading()+def::imu_top.get_heading()+def::imu_back.get_heading()+ def::imu_fl.get_heading() + def::imu_fr.get_heading())/5))); // Gets the values directly in the loop, preventing infinite loops

        //double anglError = util::wrapDeg180(targetAngle.convert(degree) - (def::mtr_dt_left_front.getPosition() - def::mtr_dt_right_front.getPosition()*def::DRIVE_DEG_TO_IN));
        // Set the arcade drive values to rotate the robot in place
        Drivetrain::moveArcade(0, ipid.iterate(angleError), false); //Turns the robot based on the iteration of the PID

        pros::delay(20);
    }

    // Stop the drivetrain after the loop is finished
    Drivetrain::moveArcade(0, 0, false);
    def::controller.rumble("-");//Rumble the controller as an indicater that the robot reached the target
}
/*-------------------------------------------TO-DO------------------------------------------*/

/* Buy Andrew RTX 4090*/


