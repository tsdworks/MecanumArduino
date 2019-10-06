#include "Mecanum.h"

Movebase::Movebase(double _widthMM, double _lengthMM, double _wheelRadis,
                   Motor *_robotMotor1, Motor *_robotMotor2, Motor *_robotMotor3, Motor *_robotMotor4)
{
    halfWidthMM = _widthMM / 2;
    halfLengthMM = _lengthMM / 2;
    wheelRadis = _wheelRadis;
    wheelCir = 2 * PI * wheelRadis;
    robotMotor1 = _robotMotor1;
    robotMotor2 = _robotMotor2;
    robotMotor3 = _robotMotor3;
    robotMotor4 = _robotMotor4;
    //Image that All Motors Are the Same
    mms2PPS = robotMotor1->motorPPR * SQRT2 / wheelCir;
}

void Movebase::Move(double _currentSpeedMMS, double _currentDirectionAngle)
{
    currentSpeedMMS = _currentSpeedMMS;
    currentDirectionAngle = _currentDirectionAngle;
    currentWheel1SpeedMMS = currentSpeedMMS * sin(currentDirectionAngle) + currentSpeedMMS * cos(currentDirectionAngle);
    currentWheel2SpeedMMS = currentSpeedMMS * sin(currentDirectionAngle) - currentSpeedMMS * cos(currentDirectionAngle);
    currentWheel3SpeedMMS = currentSpeedMMS * sin(currentDirectionAngle) - currentSpeedMMS * cos(currentDirectionAngle);
    currentWheel4SpeedMMS = currentSpeedMMS * sin(currentDirectionAngle) + currentSpeedMMS * cos(currentDirectionAngle);
    (*robotMotor1) = (int)(currentWheel1SpeedMMS * mms2PPS);
    (*robotMotor2) = (int)(currentWheel2SpeedMMS * mms2PPS);
    (*robotMotor3) = (int)(currentWheel3SpeedMMS * mms2PPS);
    (*robotMotor4) = (int)(currentWheel4SpeedMMS * mms2PPS);
}

void Movebase::Move(double _currentSpeedXMMS, double _currentSpeedYMMS, double _currentRotateRADS)
{
    currentSpeedXMMS = _currentSpeedXMMS;
    currentSpeedYMMS = _currentSpeedYMMS;
    currentRotateRADS = _currentRotateRADS;
    currentWheel1SpeedMMS = currentSpeedXMMS + currentSpeedYMMS - currentRotateRADS * (halfWidthMM + halfLengthMM);
    currentWheel2SpeedMMS = -currentSpeedXMMS + currentSpeedYMMS + currentRotateRADS * (halfWidthMM + halfLengthMM);
    currentWheel3SpeedMMS = -currentSpeedXMMS + currentSpeedYMMS - currentRotateRADS * (halfWidthMM + halfLengthMM);
    currentWheel4SpeedMMS = currentSpeedXMMS + currentSpeedYMMS + currentRotateRADS * (halfWidthMM + halfLengthMM);
    (*robotMotor1) = (int)(currentWheel1SpeedMMS * mms2PPS);
    (*robotMotor2) = (int)(currentWheel2SpeedMMS * mms2PPS);
    (*robotMotor3) = (int)(currentWheel3SpeedMMS * mms2PPS);
    (*robotMotor4) = (int)(currentWheel4SpeedMMS * mms2PPS);
}

void Movebase::Handle()
{
    robotMotor1->Handle();
    robotMotor2->Handle();
    robotMotor3->Handle();
    robotMotor4->Handle();
}