#include "MotionControl.h"

char VSL = 0;
char VSP = 0;
char regim1 = 0;
char regim2 = 0;

void MakeControl(char inputData, char outputData)
{
    inputData = ~inputData;
    char PON = inputData&0x1;
    char POV = inputData&0x2;
    char SKARV = inputData&0x4;
    char SKARN = inputData&0x8;
    char PUSK = inputData&0x10;
    outputData = ~outputData;
    char V = outputData&0x2;
    char N = outputData&0x4;
    //V - ??????
    if(!N && POV && (VSL || (regim1==0 && regim2==0)) && ((SKARV && (regim1==0 && regim2>0)) || ((regim1>0 && regim2==0)&& (V || (PUSK && !VSP)))))
    {
        if(V == 0)
            WriteOutSignals(0b00000010, 0b00000010);
        V = 1;
    }
    else
    {
        if(V > 0)
            WriteOutSignals(0b00000010, 0b00000000);
        V = 0;
    }
    //N - ?????
    if(!V && PON && (VSP || (regim1==0 && regim2==0)) && ((SKARN && (regim1==0 && regim2>0)) || ((regim1>0 && regim2==0)&& (N || (PUSK && !VSL)))))
    {
        if(N == 0)
            WriteOutSignals(0b00000100, 0b00000100);
        N = 1;
    }
    else
    {
        if(N > 0)
            WriteOutSignals(0b00000100, 0b00000000);
        N = 0;
    }
}

void ParseTPDO3(unsigned int sid, unsigned char* data)
{
    if((sid&0x780)!=0x380)//if it's not TPDO3
        return;
    char vio0 = ~data[0];
    VSL = vio0&0x1;
    VSP = vio0&0x2;
    regim1 = vio0&0x8;
    regim2 = vio0&0x10;
}
