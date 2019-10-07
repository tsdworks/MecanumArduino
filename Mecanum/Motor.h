#ifndef MOTOR_H
#define MOTOR_H

#include "Arduino.h"
#include "PIDControl.h"
#include "PinChangeInt.h"

#define MICROS_PER_SEC 1000000L
#define SEC_PER_MIN 60L
#define LEFT_SIDE 1
#define RIGHT_SIDE 0

struct MotorEncoderManager
{
    //Function EncoderISP
    //Input: void
    //Output: void
    //Attention: Must Binding in Interrupts
    void (*EncoderISP)();
    volatile unsigned char pinEncoderPinA;
    volatile unsigned char pinEncoderPinB;
    long motorPPR;
    bool motorLeft;
    volatile bool firstPulse;
    volatile unsigned long pulseCounter;
    volatile int motorSpeedPPS;
    volatile int motorTargetSpeedPPS;
    volatile unsigned long lastPulseCounter;
    volatile unsigned long lastSampleTime;
};

#define MotorState(x, y, a, b, c, d)                                                             \
    void y();                                                                                    \
    struct MotorEncoderManager x = {y, a, b, c, d, 1, 0, 0, 0, 0, 0};                            \
    void y()                                                                                     \
    {                                                                                            \
        static bool currentDirection = true;                                                     \
        static unsigned long pulseStartMicros = micros();                                        \
        static unsigned long pulseEndMicros = micros();                                          \
        pulseEndMicros = micros();                                                               \
        if (!x.firstPulse && pulseEndMicros > pulseStartMicros)                                  \
        {                                                                                        \
            x.motorSpeedPPS = MICROS_PER_SEC / (pulseEndMicros - pulseStartMicros);              \
            currentDirection = !(digitalRead(x.pinEncoderPinA) ^ digitalRead(x.pinEncoderPinB)); \
            currentDirection = x.motorLeft ? !currentDirection : currentDirection;               \
            x.motorSpeedPPS = currentDirection ? x.motorSpeedPPS : -1 * x.motorSpeedPPS;         \
            x.pulseCounter++;                                                                    \
        }                                                                                        \
        else                                                                                     \
        {                                                                                        \
            x.firstPulse = false;                                                                \
        }                                                                                        \
        pulseStartMicros = pulseEndMicros;                                                       \
    }

class Motor
{
private:
    //Input Pins for Motor
    unsigned char pinDir;
    unsigned char pinPWM;
    //PID Control for Motor
    PIDControl *motorPID;

public:
    //Motor Encoder Parameters
    struct MotorEncoderManager *motorEncoderManager;

    //Function Motor
    //Summary: Init Motor
    //Input: pinDir, pinPWM, motorEncoderManager, motorPID
    //Output: void
    Motor(int _pinDir, int _pinPWM,
          struct MotorEncoderManager *_motorEncoderManager, PIDControl *_motorPID);

    //Function SetPWM
    //Summary: Set Motor PWM Value
    //Input: pwmValue
    //Output: void
    void SetPWM(int pwmValue);

    //Function SetSpeedRPM
    //Summary: Set Motor Speed in RPM
    //Input: targetSpeed
    //Output: void
    void SetSpeedRPM(int targetSpeed);

    //Function SetSpeedPPS
    //Summary: Set Motor Speed in PPS
    //Input: targetSpeed
    //Output: void
    void SetSpeedPPS(int targetSpeed);

    //Function GetSpeedRPM
    //Summary: Get Motor Speed in RPM
    //Input: void
    //Output: speedRPM
    int GetSpeedRPM();

    //Function GetSpeedPPS
    //Summary: Get Motor Speed in PPS
    //Input: void
    //Output: speedPPS
    int GetSpeedPPS();

    //Function Handle
    //Summary: Motor PID Handle
    //Input: void
    //Output: void
    //Attention: Must Binding in Loop
    void Handle();

    //Function operator= Motor <- speedPPS
    Motor &operator=(const int op);
};

//Function PostbackMotorDebugInfo
//Summary: Postback/Output Motor Debug Info
//Input: Motor1, Motor2, Motor3, Motor4, timeInv
//Output: void
//Attention: Must Binding in Loop
void PostbackMotorDebugInfo(Motor &m1, Motor &m2, Motor &m3, Motor &m4, int timeInv);

#endif