#include "MotionControl.h"

char VSL = 0;
char VSP = 0;
char regim1 = 0;
char regim2 = 0;
char vsl[3];
char vsp[3];
char reg1[3];
char reg2[3];

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
        //if(V == 0)
        WriteOutSignals(0b00000010, 0b00000010);
        V = 1;
    }
    else
    {
        //if(V > 0)
        WriteOutSignals(0b00000010, 0b00000000);
        V = 0;
    }
    //N - ?????
    if(!V && PON && (VSP || (regim1==0 && regim2==0)) && ((SKARN && (regim1==0 && regim2>0)) || ((regim1>0 && regim2==0)&& (N || (PUSK && !VSL)))))
    {
        //if(N == 0)
        WriteOutSignals(0b00000100, 0b00000100);
        N = 1;
    }
    else
    {
        //if(N > 0)
        WriteOutSignals(0b00000100, 0b00000000);
        N = 0;
    }
}

void ParseTPDO3(unsigned int sid, unsigned char* data)
{
    if((sid&0x780)!=0x380)//if it's not TPDO3
        return;
    char vio0 = ~data[0];
    vsl[2] = vsl[1]; vsl[1] = vsl[0]; vsl[0] = vio0&0x1;
    if(vsl[1] == vsl[0] || vsl[0] == vsl[2])
        VSL = vsl[0];
    else if(vsl[2] == vsl[1])
        VSL = vsl[1];
    vsp[2] = vsp[1]; vsp[1] = vsp[0]; vsp[0] = vio0&0x2;
    if(vsp[1] == vsp[0] || vsp[0] == vsp[2])
        VSP = vsp[0];
    else if(vsp[2] == vsp[1])
        VSP = vsp[1];
    reg1[2] = reg1[1]; reg1[1] = reg1[0]; reg1[0] = vio0&0x8;
    if(reg1[1] == reg1[0] || reg1[0] == reg1[2])
        regim1 = reg1[0];
    else if(reg1[2] == reg1[1])
        regim1 = reg1[1];
    reg2[2] = reg2[1]; reg2[1] = reg2[0]; reg2[0] = vio0&0x10;
    if(reg2[1] == reg2[0] || reg2[0] == reg2[2])
        regim2 = reg2[0];
    else if(reg2[2] == reg2[1])
        regim2 = reg2[1];
}
