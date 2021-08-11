#include "PIDControl.h"

PIDControl::PIDControl(double _PIDKp, double _PIDKi, double _PIDKd, int _minOutput, int _maxOutput, unsigned long _PIDTimeInv)
{
    PIDKp = _PIDKp;
    PIDKi = _PIDKi;
    PIDKd = _PIDKd;
    PIDTimeInv = _PIDTimeInv;
    minOutput = _minOutput;
    maxOutput = _maxOutput;
    currentValue = 0;
    targetValue = 0;
    controlValue = 0;
    lastPIDCalcMS = 0;
    lastError = 0;
}

void PIDControl::Calc(int _currentValue)
{
    if (millis() - lastPIDCalcMS >= PIDTimeInv)
    {
        currentValue = _currentValue;
        int currentError = targetValue - currentValue;
        controlValue += PIDKp * (currentError - lastError) + PIDKi * currentError + PIDKd * lastError;
        controlValue = controlValue > 0 ? (controlValue > maxOutput ? maxOutput : controlValue) : (controlValue < minOutput ? minOutput : controlValue);
        lastError = currentError;
        lastPIDCalcMS = millis();
    }
}

int PIDControl::GetControlValue()
{
    return controlValue;
}

PIDControl &PIDControl::operator=(const int op)
{
    targetValue = op;
}
