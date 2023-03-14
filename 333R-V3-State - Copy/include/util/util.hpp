#pragma once
#include "main.h"

void waitForImu();//Blocks execution of code until imu is done calibrating

void resetImu();

bool waitUntil(
    std::function<bool()> icondition, okapi::QTime itimout = 0_ms,
    std::function<void()> iaction = []() {});             // runs code until the condition is true
double controlAdjust(double iinput, double ipower = 1);   // adjusts the curve of the input from the joysticks

void display_task_func(void *); // display task to be run independently

void display_task_func(); // display task to be run independently

void deploy(); // deploys the robot

//----------------------------------------------PID---------------------------------//
class PID
{
    double msettlerError, msettlerDerivative; // target error and derivative for the settler
    QTime msettlerTime;                       // target time for the settler
    std::unique_ptr<SettledUtil> msettler;    // okapi settler that is used to determine if the PID
                                              // should stop, based on error, derivative, and time

    double mkP, mkI, mkD, mkIRange; // constants

    double merror, mlastError, mtotalError;
    double mderivative; // used for storing derivative before lastError is overwritten

public:
    PID(double ikP, double ikI, double ikD, double ikIRange, double isettlerError,
        double isettlerDerivative, QTime isettlerTime); // constructor

    PID(const PID &iother); // copy constructor

    double getLastError();
    double getTotalError();

    void setGains(double ikP, double ikI, double ikD);

    double getP();
    double getI();
    double getD();

    double iterate(double ierror); // goes through one iteration of the PID loop

    bool isSettled(); // returns whether or not the controller is settled at the target
};

class Slew
{
    double mincrement;        // amount to change between each iteration
    double mactiveDifference; // threshold to activate slew
    double mlastValue;        // previous value

  public:
    Slew(double iincrement, double iactiveDifference); // constructor

    double getIncrement();
    double getActiveDifference();
    double getLastValue();

    double iterate(double ivalue); // limits the input value to maximum changes described by constants when run in a loop
};

namespace util
{
    /* ----------------------- DEMA Filter -----------------------  /
     * DEMA is short for Double Exponential Moving Average. It is a method
     * is a type of filter that smooths data and gives more weight to
     * more recent values.
     *
     * A Simple Moving Average (SMA) takes the mean of a certain number
     * of values over a specified period of time. An Exponential Moving
     * Average (EMA) is similar, but it gives more weight to newer values,
     * so it more closly tracks the actual value. A DEMA is the EMA of
     * an EMA. More specifically, it is calculated by 2EMA - EMA(EMA),
     * and it gives even more weight to newer values.
     *
     * The DEMAFilter class was originally added as an easy way to improve
     * the quality of angle measurements from the inertial sensor. It was
     * needed because the odometry loop updates at 100hz, and the inertial
     * sensors used to only update at 50hz. The DEMA filter did improve
     * the position calculation a small amount, but now the inertial
     * sensor can update at 100hz (maybe more; it's unclear), and the
     * filter is no longer useful.
     */
    template <int N> // the DEMA filter can be set to use the previous N values, changing how
                     // significant newer values are
    class DEMAFilter
    {
        const double mk;              // weighting constant
        double mlastEMA, mlastEMAEMA; // previous EMA values

        double EMACalc(double &inext, double &iold)
        {
            return (inext - iold) * mk + iold;
        } // EMA calculation

    public:
        DEMAFilter(std::array<double, 2 * N - 1> ifirstVals)
            : mk(2.0 /
                 (N +
                  1)) // to start filtering values, the DEMA filter needs to have pre-filtered values.
                      // The constructor calculates the "last" values of the EMA and EMA(EMA)
        {
            for (int i = 0; i < N; i++) // calc sum of the first N numbers
            {
                mlastEMA += ifirstVals[i];
            }
            mlastEMA /= N; // store the SMA (mean) of the first N numbers

            mlastEMAEMA = mlastEMA;
            for (int i = 0; i < N - 1; i++)
            {
                mlastEMA = EMACalc(ifirstVals[i + N],
                                   mlastEMA); // put the next values from the input through EMA filter
                mlastEMAEMA += mlastEMA;      // store sum of these values
            }
            mlastEMAEMA /= N; // store the SMA (mean) of the first N values from the EMA
        }

        double filter(double iinput) // filters the input value by doing DEMA calculation
        {
            double EMA = EMACalc(iinput, mlastEMA);    // first EMA
            double EMAEMA = EMACalc(EMA, mlastEMAEMA); // EMA of first EMA (EMA(EMA))
            mlastEMA = EMA;                            // store previous EMA
            mlastEMAEMA = EMAEMA;                      // store previous EMA(EMA)

            return 2 * EMA - EMAEMA; // 2EMA - EMA(EMA)
        }
    };
    /* ---------------------- Angle Wrappers ---------------------  /
     * All of these functions take an angle as an input, and return an
     * angle fitting into a certain range. For example, wrapDeg(370) would
     * return 10, and wrapDeg180(200) would return -160
     */
    double wrapDeg(double iangle);       // [0, 360)
    double wrapDeg180(double iangle);    // [-180, 180)
    double wrapRad(double iangle);       // [0, 2pi)
    double wrapRadPI(double iangle);     // [-pi, pi)
    QAngle wrapQAngle(QAngle iangle);    // [0_deg, 360_deg)
    QAngle wrapQAngle180(QAngle iangle); // [-180_deg, 180_deg)
    /* ------------------- Other Angle Methods ------------------- */
    bool degIsBetween(double istart, double iend,
                      double icheck); // checks if an angle is between 2 others
    /* ------------------------- Find Max ------------------------  /
 * these functions all find the maximum value of a few different types
 * of inputs. They use templates so they can be used on different types,
 * and on arrays of different lengths.
 */
template <class T, std::size_t N>
T findMax(const std::array<T, N> && iarray) // returns the max value in iarray
{
    T largest = iarray.at(0);    // gives largest a value to compare with
    for (const T & val : iarray) // loops through all values
        if (val > largest)
            largest = val; // stores the largest value
    return largest;
}
template <class T, std::size_t N>
T findMax(const std::array<T, N> & iarray) // returns the max value in iarray
{
    T largest = iarray.at(0);    // gives largest a value to compare with
    for (const T & val : iarray) // loops through all values
        if (val > largest)
            largest = val; // stores the largest value
    return largest;
}
template <class T, std::size_t N>
T findAbsMax(const std::array<T, N> && iarray) // returns the max absolute value in iarray
{
    T largest = iarray.at(0);    // gives largest a value to compare with
    for (const T & val : iarray) // loops through all values
        if (abs(val) > largest)
            largest = abs(val); // stores the largest value
    return largest;
}
template <class T, std::size_t N>
T findAbsMax(const std::array<T, N> & iarray) // returns the max absolute value in iarray
{
    T largest = iarray.at(0);    // gives largest a value to compare with
    for (const T & val : iarray) // loops through all values
        if (abs(val) > largest)
            largest = abs(val); // stores the largest value
    return largest;
}

/* ------------------------- Fitters -------------------------  /
 * These functions modfify the input to fit in a specified range
 */
template <std::size_t N>
std::array<double, N> scaleToFit(double imagnitude, std::array<double, N> && iarray) // scales all elements in iarray to fit within [-imagnitude, imagnitude]
{
    double largest = findAbsMax<double, N>(iarray);
    if (largest > imagnitude) // if anything is out of range
    {
        largest = std::abs(largest);
        for (double & val : iarray) // scales everything down to fit in the range
            val = val / largest * imagnitude;
    }
    return iarray;
}
template <std::size_t N>
void scaleToFit(double imagnitude, std::array<double, N> & iarray) // scales all elements in iarray to fit within [-imagnitude, imagnitude]
{
    double largest = findAbsMax<double, N>(iarray);
    if (largest > imagnitude) // if anything is out of range
    {
        largest = std::abs(largest);
        for (double & val : iarray) // scales everything down to fit in the range
            val = val / largest * imagnitude;
    }
}

template <class T, std::size_t N>
void chop(T imin, T imax, std::array<T, N> & iarray) // if any values in iarray are out of range, they are set to the limit
{
    for (double & val : iarray)
    {
        if (val > imax)
            val = imax;
        else if (val < imin)
            val = imin;
    }
}
template <class T>
void chop(T imin, T imax, T & inum) // if the value is out of range, it is set to the limit
{
    if (inum > imax)
        inum = imax;
    else if (inum < imin)
        inum = imin;
}
} // namespace util