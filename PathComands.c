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

void TurnOnOrOffRelay(char data)
{
    data = ~data;
    TRISBbits.TRISB9 = 0;//set output on RB8
    TRISBbits.TRISB10 = 0;//set output on RB8
    TRISBbits.TRISB11 = 0;//set output on RB8
    TRISBbits.TRISB12 = 0;//set output on RB8
    TRISBbits.TRISB13 = 0;//set output on RB8
    TRISBbits.TRISB14 = 0;//set output on RB8
    TRISBbits.TRISB15 = 0;//set output on RB8

    LATBbits.LATB9 = data&1; data>>=1;
    LATBbits.LATB10 = data&1; data>>=1;
    LATBbits.LATB11 = data&1; data>>=1;
    LATBbits.LATB12 = data&1; data>>=1;
    LATBbits.LATB13 = data&1; data>>=1;
    LATBbits.LATB14 = data&1; data>>=1;
    LATBbits.LATB15 = data&1; data>>=1;
}