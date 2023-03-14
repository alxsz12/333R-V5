#pragma once
#include "main.h"

class Drivetrain 
{
private:
    //Motor References
    //Left
    static Motor &mmtrLeftFront;
    static Motor &mmtrLeftMid;
    static Motor &mmtrLeftBack;
    //Right
    static Motor &mmtrRightFront;
    static Motor &mmtrRightMid;
    static Motor &mmtrRightBack;
//------------------------- Chassis Builder
    static std::shared_ptr<ChassisController>
        mchassis; // chassis object for using Pathfilder through okapi
protected:
//Settings 
/* -------------------- Odometry Accessors ------------------- */
    static OdomState getState(); // get position as OdomState
    static QLength getXPos();
    static QLength getYPos();
    static QAngle getTheta();

    static double mmaxSpeed;
    static bool menabled;
public:
    //Getter and Setter Methods
    static double getMaxSpeed();
    static void setMaxSpeed(const double imaxSpeed);

    static bool isEnabled();
    static void enable(); // allows movements to be startable
    static void disable(); // stops active movements

    static void lock();
    static void unlock();

    //Movement functions 

    static void moveIndependent(double ileft, double iright, const bool idesaturate = true); // moves each motor {lf, rf, rb, lb} in range [-1,1]
    
    static void moveTank(const double ileft, const double iright, const bool idesaturate = true); // spins the left side and right side motors at certian speeds [-1,1]

    static void moveArcade(const double iforward, const double iturn, const bool idesaturate = true);

    static void arcadeFor(const double iforward, const double iturn, const int ims);

    static void turnToAngle(QAngle iangle, PID ipid = PID(0.09, 0.0, 0.2, 1, 0.5, 0.01, 1_ms));

    static void straightForDistance(QLength idistance,
    PID imagnitudePID = PID(.2, 0.0,0.2, 0, 0.5, 0.001, 1_ms), 
    Slew imagnitudeSlew = Slew(19,20), 
    PID iturnPID = PID(0.2, 0.0, 0.01, 0, 0.5, 0.01, 1_ms));

    static void fDist(int dist);

    static void bDist(int dist);
};

namespace def
{
extern Drivetrain drivetrain; //declares the drivetrain object as external, to only use it once when we use the class
}