#ifndef PIDCONTROL_H
#define PIDCONTROL_H

#include "Arduino.h"

class PIDControl
{
private:
    //PID Parameters
    double PIDKp;
    double PIDKi;
    double PIDKd;
    int minOutput;
    int maxOutput;
    //PID Time Inv (ms)
    unsigned long PIDTimeInv;
    unsigned long lastPIDCalcMS;
    //PID State & Value
    int currentValue;
    int targetValue;
    int controlValue;
    //PID Last Error
    int lastError;

public:
    //Function PIDControl
    //Summary: Init PIDControl
    //Input: Kp, Ki, Kd, PID_Interval
    //Output: void
    PIDControl(double _PIDKp, double _PIDKi, double _PIDKd, int _minOutput, int _maxOutput, unsigned long _PIDTimeInv);

    //Function Calc
    //Summary: Calc PID Control Value
    //Input: currentValue
    //Outpu: void
    //Attention: Must Binding in Loop
    void Calc(int _currentValue);

    //Function GetControlValue
    //Summary: Get PID Control Value
    //Input: void
    //Outpu: controlValue
    int GetControlValue();

    //Function operator= PIDControl <- targetValue
    PIDControl &operator=(const int op);
};

#endif