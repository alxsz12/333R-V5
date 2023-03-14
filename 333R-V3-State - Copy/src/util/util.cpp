#include "main.h"

void waitForImu() // blocks the execution of the code until the imu is done calibrating
{
    while (def::imu_top.is_calibrating() || def::imu_side.is_calibrating() || def::imu_back.is_calibrating() || def::imu_fl.is_calibrating() || def::imu_fr.is_calibrating())
        pros::delay(100);
}

void resetImu()
{
    def::imu_back.reset();
    def::imu_top.reset();
    def::imu_side.reset();
    def::imu_fl.reset();
    def::imu_fr.reset();
    waitForImu();
    pros::delay(20);
}

bool waitUntil(std::function<bool()> icondition, QTime itimeout, std::function<void()> iaction)
{
    Timer timer = Timer();
    QTime startTime = timer.millis();

    while (!icondition())
    {
        if (itimeout != 0_ms && timer.millis() - startTime >= itimeout)
        {
            return false;
        }
        iaction();
        pros::delay(10);
    }
    return true;
}

double controlAdjust(double iinput,
                     double ipower) // adjusts the curve of the input from the joysticks
{
    double result = pow(iinput, ipower); // calculate the curve
    if (iinput * result < 0)             // if input is negative and output is positive
    {
        result = -result; // make it negative
    }
    return result;
}

void display_task_func(void *) // display task to be run independently
{
    while (true)
    {

        // room for any other miscellaneous debugging

        pros::delay(20);
    }
}

/* -------------------------- Macros ------------------------- */
void deploy() // deploys the robot
{
    pros::delay(250);
}

void display_task_func() // display task to be run independently
{
    while (true)
    {
        // room for any other miscellaneous debugging
        def::display.setMiscData(1, "FW Actual: " + std::to_string(def::mtr_fw.getActualVelocity()));
        def::display.setMiscData(2, "FW Target: " + std::to_string(def::mtr_fw.getTargetVelocity()));

        //Graph Data
        def::display.setChartData(0, def::mtr_dt_left_front.getActualVelocity() - 150);
        def::display.setChartData(1, def::mtr_dt_left_mid.getActualVelocity() - 150);
        def::display.setChartData(2, def::mtr_dt_left_back.getActualVelocity() - 150);
        def::display.setChartData(3, def::mtr_dt_right_front.getActualVelocity() - 150);
        def::display.setChartData(4, def::mtr_dt_right_mid.getActualVelocity() - 150);
        def::display.setChartData(5, def::mtr_dt_right_back.getActualVelocity() - 150);
        def::display.setChartData(6, def::mtr_fw.getActualVelocity() - 150);
        def::display.setChartData(7, def::mtr_it.getActualVelocity() - 150);

        pros::delay(20);
    }
}

//--------------------------------------------------------------//
//--------------------------------------------------------------//
//--------------------------PID---------------------------------//
//--------------------------------------------------------------//
//--------------------------------------------------------------//
//--------------------------------------------------------------//
//--------------------------------------------------------------//

PID::PID(double ikP, double ikI, double ikD, double ikIRange, double isettlerError,
         double isettlerDerivative,
         QTime isettlerTime) // constructor that sets constants, and initializes variables
    : msettlerError(isettlerError), msettlerDerivative(isettlerDerivative),
      msettlerTime(isettlerTime), msettler(TimeUtilFactory::withSettledUtilParams(
                                               msettlerError, 
                                               msettlerDerivative, 
                                               msettlerTime)
                                               .getSettledUtil()),
      mkP(ikP), mkI(ikI), mkD(ikD), mkIRange(ikIRange), merror(0), mlastError(0), mtotalError(0),
      mderivative(0)
{
}

PID::PID(const PID &iother) // copy constructor for duplicating PID objects behind the scenes
{
    msettlerError = iother.msettlerError;
    msettlerDerivative = iother.msettlerDerivative;
    msettlerTime = iother.msettlerTime;
    msettler =
        TimeUtilFactory::withSettledUtilParams(msettlerError,
                             msettlerDerivative, 
                             msettlerTime)
            .getSettledUtil();
    mkP = iother.mkP;
    mkI = iother.mkI;
    mkD = iother.mkD;
    mkIRange = iother.mkIRange;
    mlastError = iother.mlastError;
    mtotalError = iother.mtotalError;
    mderivative = iother.mderivative;
}

double PID::getLastError() { return mlastError; }
double PID::getTotalError() { return mtotalError; }

void PID::setGains(double ikP, double ikI, double ikD) // used only for changing constants later
{
    mkP = ikP;
    mkI = ikI;
    mkD = ikD;
}

double PID::getP() { return mkP; }
double PID::getI() { return mkI; }
double PID::getD() { return mkD; }

double PID::iterate(double ierror) // goes through one iteration of the PID loop
{
    merror = ierror;
    if (mkI != 0) // regulate integral term
    {
        if (abs(merror) < mkIRange && merror != 0) // if in range, update mtotalError
        {
            mtotalError += merror;
        }
        else
        {
            mtotalError = 0;
        }
        util::chop<double>(-50 / mkI, 50 / mkI,
                           mtotalError); // limit mtotalError to prevent integral windup
    }

    mderivative = merror - mlastError; // calculate the derivative before lastError is overwritten
    mlastError = merror;               // save the current error for the next cycle

    return merror *
               mkP +
           mtotalError * mkI + mderivative * mkD;
}

bool PID::isSettled() // returns whether or not the controller is settled at the target
{
    return msettler->isSettled(merror);
}

//Slew Class 
Slew::Slew(double iincrement, double iactiveDifference)
    : mincrement(iincrement), mactiveDifference(iactiveDifference), mlastValue(0) // constructor
{
}

double Slew::getIncrement() { return mincrement; }
double Slew::getActiveDifference() { return mactiveDifference; }
double Slew::getLastValue() { return mlastValue; }

double Slew::iterate(double ivalue) // limits the input value to maximum changes described by
                                    // constants when run in a loop
{
    if (abs(ivalue - mlastValue) >
        mactiveDifference) // only activate if the value difference is over the threshold
    {
        if (ivalue >
            mlastValue +
                mincrement) // if the input is too big, only let it increase by a maximum amount
        {
            mlastValue = mlastValue + mincrement;
            return mlastValue;
        }
        else if (ivalue < mlastValue - mincrement) // if the input is too small, only let it
                                                   // decrease by a maximum amount
        {
            mlastValue = mlastValue - mincrement;
            return mlastValue;
        }
    }
    mlastValue = ivalue;
    return ivalue; // this only happens if nothing is wrong
}

/* ---------------------- Angle Wrappers ---------------------  /
 * These methods take any angle, and return an angle representing the same position in a specific
 * range. For example, wrapDeg(370) returns 10, because 370 is out of the range [0, 360).
 */
double util::wrapDeg(double iangle) // range [0, 360)
{
    iangle = fmod(iangle, 360);
    if (iangle < 0)
        iangle += 360;
    return iangle;
}
double util::wrapDeg180(double iangle) // range [-180, 180]
{
    iangle = fmod(iangle, 360);
    if (iangle < -180)
        iangle += 360;
    else if (iangle > 180)
        iangle -= 360;
    return iangle;
}
double util::wrapRad(double iangle) // range [0, 2pi)
{
    iangle = fmod(iangle, 2 * 3.14159265358979323846);
    if (iangle < 0)
        iangle += 2 * 3.14159265358979323846;
    return iangle;
}
double util::wrapRadPI(double iangle) // range [-pi, pi]
{
    iangle = fmod(iangle, 2 * 3.14159265358979323846);
    if (iangle < -3.14159265358979323846)
        iangle += 2 * 3.14159265358979323846;
    else if (iangle > 3.14159265358979323846)
        iangle -= 2 * 3.14159265358979323846;
    return iangle;
}
QAngle util::wrapQAngle(QAngle iangle) // range [0, 360) for QAngles
{
    iangle = fmod(iangle.convert(degree), 360) * degree;
    if (iangle < 0_deg)
        iangle += 360_deg;
    return iangle;
}
QAngle util::wrapQAngle180(QAngle iangle) // range [-180, 180] for QAngles
{
    iangle = fmod(iangle.convert(degree), 360) * degree;
    if (iangle < -180_deg)
        iangle += 360_deg;
    else if (iangle > 180_deg)
        iangle -= 360_deg;
    return iangle;
}

/* ------------------- Other Angle Methods ------------------- */
bool util::degIsBetween(double istart, double iend,
                        double icheck) // checks if an angle is between 2 others
{
    iend -= istart;
    if (iend < 0)
    {
        iend += 360;
    }
    icheck -= istart;
    if (icheck < 0)
    {
        icheck += 360;
    }
    return icheck < iend;
}
