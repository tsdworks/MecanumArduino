#include "Motor.h"

Motor::Motor(int _pinDir, int _pinPWM, long _motorPPR, bool _motorLeft,
             struct MotorEncoderManager *_motorEncoderManager, PIDControl *_motorPID)
{
    motorEncoderManager = _motorEncoderManager;
    motorLeft = _motorLeft;

    //Setup Pins
    pinDir = _pinDir;
    pinPWM = _pinPWM;
    motorPPR = _motorPPR;
    pinMode(pinDir, OUTPUT);
    pinMode(pinPWM, OUTPUT);
    pinMode(motorEncoderManager->pinEncoderPinA, INPUT);
    pinMode(motorEncoderManager->pinEncoderPinB, INPUT);

    //Attach Interrputs
    if (motorEncoderManager->pinEncoderPinA == 2 || motorEncoderManager->pinEncoderPinA == 3)
        attachInterrupt(motorEncoderManager->pinEncoderPinA - 2, motorEncoderManager->EncoderISP, CHANGE);
    else
        PCattachInterrupt(motorEncoderManager->pinEncoderPinA, motorEncoderManager->EncoderISP, CHANGE);

    //Setup PID Control
    motorPID = _motorPID;

    //Reset Motor
    (*this) = 0;
}

void Motor::SetPWM(int pwmValue)
{
    digitalWrite(pinDir, pwmValue >= 0 ? motorLeft : !motorLeft);
    pwmValue = pwmValue < 0 ? -1 * pwmValue : pwmValue;
    analogWrite(pinPWM, pwmValue);
}

void Motor::SetSpeedRPM(int targetSpeed)
{
    SetSpeedPPS((int)((long)(targetSpeed * motorPPR) / SEC_PER_MIN));
}

void Motor::SetSpeedPPS(int targetSpeed)
{
    motorEncoderManager->motorTargetSpeedPPS = targetSpeed;
}

int Motor::GetSpeedRPM()
{
    return (int)((long)(motorEncoderManager->motorSpeedPPS * SEC_PER_MIN / motorPPR));
}

int Motor::GetSpeedPPS()
{
    return motorEncoderManager->motorSpeedPPS;
}

void Motor::Handle()
{
    if (millis() - motorEncoderManager->lastSampleTime > 100)
    {
        if (motorEncoderManager->lastPulseCounter == motorEncoderManager->pulseCounter)
        {
            motorEncoderManager->firstPulse = true;
            motorEncoderManager->motorSpeedPPS = 0;
        }
        motorEncoderManager->lastPulseCounter = motorEncoderManager->pulseCounter;
        motorEncoderManager->lastSampleTime = millis();
    }
    (*motorPID) = motorEncoderManager->motorTargetSpeedPPS;
    motorPID->Calc(motorEncoderManager->motorSpeedPPS);
    SetPWM(motorPID->GetControlValue());
}

Motor &Motor::operator=(const int op)
{
    SetSpeedPPS(op);
}

void PostbackMotorDebugInfo(Motor &m1, Motor &m2, Motor &m3, Motor &m4, int timeInv)
{
    static long lastTime = 0;
    if (millis() - lastTime > timeInv)
    {
        Serial.print("M1 ");
        Serial.print(m1.GetSpeedRPM());
        Serial.print(" ");
        Serial.print("M2 ");
        Serial.print(m2.GetSpeedRPM());
        Serial.print(" ");
        Serial.print("M3 ");
        Serial.print(m3.GetSpeedRPM());
        Serial.print(" ");
        Serial.print("M4 ");
        Serial.print(m4.GetSpeedRPM());
        Serial.println(" ");
        lastTime = millis();
    }
}