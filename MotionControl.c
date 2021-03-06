#include "MotionControl.h"

char VSL = 0;
char VSP = 0;
char regim1 = 0;
char regim2 = 0;
char vsl[3];
char vsp[3];
char reg1[3];
char reg2[3];
char TP = 0;
char tp[3];
char VBTRK = 0;
char SKARK = 0;
char vbtrk[3];
char skark[3];
short v[3];
char IRS = 0;

void MakeControl(char inputData, char outputData)
{
    inputData = ~inputData;
    char PON = inputData&0x1;
    char POV = inputData&0x2;
    char SKARV = inputData&0x4;
    char SKARN = inputData&0x8;
    char PUSK = inputData&0x10;
    char RKZD = inputData&0x40;
    outputData = ~outputData;
    char V = outputData&0x2;
    char N = outputData&0x4;
    char RZD = outputData&0x8;
    char RTR = outputData&0x10;
    //V - vpered
    if(!N && POV && (VSL || (regim1==0 && regim2==0)) && ((SKARV && ((regim1==0 && regim2>0) || (regim1==0 && regim2==0))) || ((regim1>0 && regim2==0)&& (V || (PUSK && !VSP)))) && TP)
    {
        WriteOutSignals(0b00000010, 0b00000010);
        V = 1;
    }
    else
    {
        WriteOutSignals(0b00000010, 0b00000000);
        V = 0;
    }
    //N - nazad
    if(!V && PON && (VSP || (regim1==0 && regim2==0)) && ((SKARN && ((regim1==0 && regim2>0) || (regim1==0 && regim2==0))) || ((regim1>0 && regim2==0)&& (N || (PUSK && !VSL)))) && TP)
    {
        WriteOutSignals(0b00000100, 0b00000100);
        N = 1;
    }
    else
    {
        WriteOutSignals(0b00000100, 0b00000000);
        N = 0;
    }
    //RZD
    if((V || N) && ((regim1==0 && regim2>0) || (RKZD && VBTRK && SKARK)) && TP)
    {
        WriteOutSignals(0b00001000, 0b00001000);
        RZD = 1;
    }
    else
    {
        WriteOutSignals(0b00001000, 0b00000000);
        RZD = 0;
    }
    //RTR
    if(((RZD && (V || N)) || (VSL && VSP && IRS)) && TP)
    {
        WriteOutSignals(0b00010000, 0b00010000);
        RTR = 1;
    }
    else
    {
        WriteOutSignals(0b00010000, 0b00000000);
        RTR = 0;
    }
}

void ParseTPDO2(unsigned int sid, unsigned char* data)
{
    if((sid&0x780)!=0x280)//if it's not TPDO2
        return;
    short* speed = 0;
    char buf[2] = {data[2], data[3]};
    speed = buf;
    //*distance=(*distance)/256;
    if((sid&0x3) == 0x1)
        v[0] = *speed;
    if((sid&0x3) == 0x2)
        v[1] = *speed;
    if((sid&0x3) == 0x3)
        v[2] = *speed;
    int i = 0;
    for(i; i < 3; i++)
        if(v[i] < 0)
            v[i] *= -1;
    if((v[0] <= 500 && v[1] <= 500) || (v[0] <= 500 && v[2] <= 500) || (v[1] <= 500 && v[2] <= 500))
    {
        IRS = 0;
        WriteOutSignals(0b00100000, 0b00000000);
    }
    else
    {
        IRS = 1;
        WriteOutSignals(0b00100000, 0b00100000);
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

void ParseTPDO4(unsigned int sid, unsigned char* data)
{
    if((sid&0x780)!=0x480)//if it's not TPDO4
        return;
    if((sid&0x7)==0x7)//if it's FPK3
    {
        char vio0 = ~data[0];
        tp[2] = tp[1]; tp[1] = tp[0]; tp[0] = vio0&0x1;
        if(tp[1] == tp[0] || tp[0] == tp[2])
            TP = tp[0];
        else if(tp[2] == tp[1])
            TP = tp[1];
        vbtrk[2] = vbtrk[1]; vbtrk[1] = vbtrk[0]; vbtrk[0] = vio0&0x2;
        if(vbtrk[1] == vbtrk[0] || vbtrk[0] == vbtrk[2])
            VBTRK = vbtrk[0];
        else if(vbtrk[2] == vbtrk[1])
            VBTRK = vbtrk[1];
        skark[2] = skark[1]; skark[1] = skark[0]; skark[0] = vio0&0x4;
        if(skark[1] == skark[0] || skark[0] == skark[2])
            SKARK = skark[0];
        else if(skark[2] == skark[1])
            SKARK = skark[1];
    }
}
