#include "Wireless.h"

WirelessSerial::WirelessSerial(char _streamStartSym, char _streamEndSym, char _streamFilSym)
{
    streamStartSym = _streamStartSym;
    streamEndSym = _streamEndSym;
    streamFilSym = _streamFilSym;
    memset(serialStream, 0, sizeof(serialStream));
    memset(streamData, 0, sizeof(streamData));
    dataCount = 0;
    streamPos = 0;
}

int Str2Int(const char *dataStr, int startPos, int endPos)
{
    int retValue = 0;
    bool numNegative = false;
    if (dataStr[startPos] == '-')
    {
        numNegative = true;
        startPos++;
    }
    for (int i = startPos; i <= endPos; i++)
    {
        retValue *= 10;
        retValue += dataStr[i] - '0';
    }
    retValue = numNegative ? -1 * retValue : retValue;
    return retValue;
}

bool WirelessSerial::Handle()
{
    bool retValue = false;
    while (Serial.available() > 0)
    {
        char tempData = (char)Serial.read();
        if (tempData == streamStartSym || streamPos >= STREAM_LENGTH)
        {
            streamPos = 0;
        }
        serialStream[streamPos++] = tempData;
        //If End Symbol Meets
        if (tempData == streamEndSym)
        {
            int filterPos = 1;
            dataCount = 0;
            for (int i = 1; i < streamPos; i++)
                if (serialStream[i] == streamFilSym || serialStream[i] == streamEndSym)
                {
                    streamData[dataCount++] = Str2Int(serialStream, filterPos, i - 1);
                    filterPos = i + 1;
                }
            retValue = true;
        }
    }
    return retValue;
}
