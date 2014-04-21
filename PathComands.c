#include <xc.h>
#include "Majorization.h"
#include "PathComands.h"

//global vars
extern long _sPointUp[8];
extern long _sPointDown[8];

unsigned char GetPathComandsUpDown()
{
    int countPoints = 8;
    unsigned char relayData = 0;
    int i = 0;
    for(i; i < countPoints; i++)
    {
        if(MajorizationGetCurrentS() <= _sPointDown[i])
        {
            unsigned char buf = 0b00000001;
            buf <<= i;
            relayData |= buf;
        }
    }
    i = 0;
    for(i; i < countPoints; i++)
    {
        if(MajorizationGetCurrentS() >= _sPointUp[i])
        {
            unsigned char buf = 0b00000001;
            buf <<= i;
            relayData |= buf;
        }
    }
    return relayData;
}