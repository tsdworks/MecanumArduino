#include "Arduino.h"
#include "Mecanum.h"
#include "Wireless.h"

//Define Motor PID Controller
PIDControl motor1PIDControl(0.1, 0.02, 0, -255, 255, 20);
PIDControl motor2PIDControl(0.1, 0.02, 0, -255, 255, 20);
PIDControl motor3PIDControl(0.1, 0.02, 0, -255, 255, 20);
PIDControl motor4PIDControl(0.1, 0.02, 0, -255, 255, 20);

//Define Motor Encoder Manager
MotorState(motor1State, motor1EncoderISP, 2, A1, 700, LEFT_SIDE);
MotorState(motor2State, motor2EncoderISP, 3, 49, 700, RIGHT_SIDE);
MotorState(motor3State, motor3EncoderISP, 18, 31, 700, LEFT_SIDE);
MotorState(motor4State, motor4EncoderISP, 19, 38, 700, RIGHT_SIDE);

//Define Motor
Motor robotMotor1(A5, A4, 5, &motor1State, &motor1PIDControl);
Motor robotMotor2(42, 43, 9, &motor2State, &motor2PIDControl);
Motor robotMotor3(35, 34, 12, &motor3State, &motor3PIDControl);
Motor robotMotor4(36, 37, 8, &motor4State, &motor4PIDControl);

//Define Movebase
Movebase currentMovebase(26, 16, 30, &robotMotor1, &robotMotor2, &robotMotor3, &robotMotor4);

//Define Remote
WirelessSerial wirelessControlOpenMV(&Serial2, 115200, '(', ')', ' ');
WirelessSerial wirelessControlWireless(&Serial3, 19200, '(', ')', ' ');

void setup()
{
    //PWM Freq 970Hz
    TCCR1A = _BV(WGM10);
    TCCR1B = _BV(CS11) | _BV(CS10) | _BV(WGM12);
    TCCR2A = _BV(WGM21) | _BV(WGM20);
    TCCR2B = _BV(CS22);
    TCCR3A = _BV(WGM30);
    TCCR3B = _BV(CS31) | _BV(CS30) | _BV(WGM32);
    TCCR4A = _BV(WGM40);
    TCCR4B = _BV(CS41) | _BV(CS40) | _BV(WGM42);
    //Enable Power Supply
    pinMode(A0, OUTPUT);
    digitalWrite(A0, HIGH);
}

void loop()
{
    //Control by Wireless
    if (wirelessControlWireless.Handle())
    {
        if (wirelessControlWireless.streamData[0] == 0)
        {
            if (wirelessControlWireless.dataCount > 2)
                currentMovebase.Move(wirelessControlWireless.streamData[1],
                                     wirelessControlWireless.streamData[2] * PI / 180);
        }
        else if (wirelessControlWireless.streamData[0] == 1)
        {
            if (wirelessControlWireless.dataCount > 3)
                currentMovebase.Move(wirelessControlWireless.streamData[1],
                                     wirelessControlWireless.streamData[2], wirelessControlWireless.streamData[3]);
        }
        else if (wirelessControlWireless.streamData[0] == 2)
        {
            currentMovebase.Move(0, 0);
        }
    }
    //Control by OpenMV
    if (wirelessControlOpenMV.Handle())
    {
        if (wirelessControlOpenMV.streamData[0] == 0)
        {
            if (wirelessControlOpenMV.dataCount > 2)
                currentMovebase.Move(wirelessControlOpenMV.streamData[1],
                                     wirelessControlOpenMV.streamData[2] * PI / 180);
        }
        else if (wirelessControlOpenMV.streamData[0] == 1)
        {
            if (wirelessControlOpenMV.dataCount > 3)
                currentMovebase.Move(wirelessControlOpenMV.streamData[1],
                                     wirelessControlOpenMV.streamData[2], wirelessControlOpenMV.streamData[3]);
        }
        else if (wirelessControlOpenMV.streamData[0] == 2)
        {
            currentMovebase.Move(0, 0);
        }
    }
    PostbackMotorDebugInfo(&Serial2, robotMotor1, robotMotor2, robotMotor3, robotMotor4, 500);
    currentMovebase.Handle();
}
