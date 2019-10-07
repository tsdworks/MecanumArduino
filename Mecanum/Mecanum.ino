#include "Arduino.h"
#include "Mecanum.h"
#include "Wireless.h"

//Used
//2, 3, 4, 5, 7, 8, 9, 11, 12
//A0 A1 A2 A3 A4 A5
//Unused
//6, 10

//Define Motor PID Controller
PIDControl motor1PIDControl(0.2, 0.04, 0, -255, 255, 20);
PIDControl motor2PIDControl(0.2, 0.04, 0, -255, 255, 20);
PIDControl motor3PIDControl(0.2, 0.04, 0, -255, 255, 20);
PIDControl motor4PIDControl(0.2, 0.04, 0, -255, 255, 20);

//Define Motor Encoder Manager
MotorState(motor1State, motor1EncoderISP, 18, 19, 320, LEFT_SIDE);
MotorState(motor2State, motor2EncoderISP, 4, 5, 320, RIGHT_SIDE);
MotorState(motor3State, motor3EncoderISP, 16, 17, 320, LEFT_SIDE);
MotorState(motor4State, motor4EncoderISP, 14, 15, 320, RIGHT_SIDE);

//Define Motor
Motor robotMotor1(7, 10, &motor1State, &motor1PIDControl);
Motor robotMotor2(2, 3, &motor2State, &motor2PIDControl);
Motor robotMotor3(8, 9, &motor3State, &motor3PIDControl);
Motor robotMotor4(12, 11, &motor4State, &motor4PIDControl);

//Define Movebase
Movebase currentMovebase(22, 30, 30, &robotMotor1, &robotMotor2, &robotMotor3, &robotMotor4);

//Define Wireless
WirelessSerial wirelessControl('(', ')', ' ');

void setup()
{
    Serial.begin(19200);
    TCCR1B = TCCR1B & 0xf8 | 0x01; // Pin9,Pin10 PWM 31250Hz
    TCCR2B = TCCR2B & 0xf8 | 0x01; // Pin3,Pin11 PWM 31250Hz
}

void loop()
{
    if (wirelessControl.Handle())
    {
        if (wirelessControl.streamData[0] == 0)
        {
            if (wirelessControl.dataCount > 2)
                currentMovebase.Move(wirelessControl.streamData[1],
                                     wirelessControl.streamData[2] * PI / 180);
        }
        else if (wirelessControl.streamData[0] == 1)
        {
            if (wirelessControl.dataCount > 3)
                currentMovebase.Move(wirelessControl.streamData[1],
                                     wirelessControl.streamData[2], wirelessControl.streamData[3]);
        }
        else if (wirelessControl.streamData[0] == 2)
        {
            currentMovebase.Move(0, 0);
        }
    }
    PostbackMotorDebugInfo(robotMotor1, robotMotor2, robotMotor3, robotMotor4, 500);
    currentMovebase.Handle();
}
