#ifndef MECANUM_H
#define MECANUM_H

#include "Arduino.h"
#include "Motor.h"

#define FORWARD PI / 2
#define BACKWARD -PI / 2
#define LEFT PI
#define RIGHT 0
#define SQRT2 1.41421

// Movebase
// M1 ----- W ----- M2
// |                |
// |                |
// H                |
// |                |
// |                |
// M3 ------------- M4

class Movebase
{
private:
    //Motor Manager
    Motor *robotMotor1;
    Motor *robotMotor2;
    Motor *robotMotor3;
    Motor *robotMotor4;
    //Movebase Width & Length
    double halfWidthMM;
    double halfLengthMM;
    //Mecanum Wheel Parameters
    double wheelRadis;
    double wheelCir;
    //Speed mm/s -> Speed pulse/s
    double mms2PPS;

public:
    //Movebase Move Parameters
    double currentSpeedMMS;
    double currentDirectionAngle;
    double currentSpeedXMMS;
    double currentSpeedYMMS;
    double currentRotateRADS;
    double currentWheel1SpeedMMS;
    double currentWheel2SpeedMMS;
    double currentWheel3SpeedMMS;
    double currentWheel4SpeedMMS;

    //Function: Movebase
    //Summary: Init Movebase
    //Input: widthMM, lengthMM, wheelRadis, robotMotor1, robotMotor2, robotMotor3, robotMotor4
    //Output: void
    Movebase(double _widthMM, double _lengthMM, double _wheelRadis,
             Motor *_robotMotor1, Motor *_robotMotor2, Motor *_robotMotor3, Motor *_robotMotor4);

    //Function: Move
    //Summary: Move the Robot
    //Input: currentSpeedMMS, currentDirectionAngle
    //Output: void
    void Move(double _currentSpeedMMS, double _currentDirectionAngle);

    //Function: Move
    //Summary: Move the Robot
    //Input: currentSpeedXMMS, currentSpeedYMMS, currentRotateRADS
    //Output: void
    void Move(double _currentSpeedXMMS, double _currentSpeedYMMS, double _currentRotateRADS);

    //Function: Handle
    //Summary: Robot Move Action Handle
    //Input: void
    //Output: void
    //Attention: Must Binding in Loop
    void Handle();
};

#endif