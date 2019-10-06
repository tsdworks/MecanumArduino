#ifndef WIRELESS_H
#define WIRELESS_H

#define STREAM_LENGTH 64
#define STREAM_DATA_LENGTH 16

#include "Arduino.h"

class WirelessSerial
{
private:
    char streamStartSym;
    char streamEndSym;
    char streamFilSym;
    char serialStream[STREAM_LENGTH];
    int streamPos;

public:
    int dataCount;
    int streamData[STREAM_DATA_LENGTH];
    //Function: WirelessSerial
    //Summary: Init WirelessSerial
    //Input: streamStartSym, streamEndSym, streamFilSym
    //Output: void
    WirelessSerial(char _streamStartSym, char _streamEndSym, char _streamFilSym);

    //Function: Handle
    //Summary: If Have Recieved a Stream Pack
    //Input: void
    //Output: Recieved
    //Attention: Must Binding in Loop
    bool Handle();
};

#endif