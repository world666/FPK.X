#include <xc.h>
#include <math.h>
#include "Majorization.h"

//global vars
extern int _leadingController;
extern long _accuracy;

long s[3] = {100000,300000,500000}; // parameters S from 3 controllers

void ParseTPDO1(unsigned int sid, unsigned char* data)
{
    if((sid&0x780)!=0x180)//if it's not TPDO1
        return;
    long* distance = 0;
    /*distance += data[5]<<8;
    distance=distance<<8;
    distance+=data[4]<<8;
    distance+=data[3];*/
    char buf[4] = {0, data[3], data[4], data[5]};
    distance = buf;
    *distance=(*distance)/256;
    if((sid&0x3) == 0x1)
    {
        s[0] = *distance;
    }
    if((sid&0x3) == 0x2)
    {
        s[1] = *distance;
    }
    if((sid&0x3) == 0x3)
    {
        s[2] = *distance;
    }
}

void Majorization()
{
    long accuracy = _accuracy;
    long dif;
    char er_count[3] ={0,0,0};
    int i = 0;
    for(i; i < 3; i++)
    {
        int j=0;
        for(j; j < 3; j++)
        {
            if(i == j)
                continue;
            if((s[i] < s[j] - accuracy) || (s[i] > s[j] + accuracy))
                er_count[i]++;
        }
    }
    if(er_count[0] == 2 && er_count[1] == 2 && er_count[2] == 2)// two controllers failed
        TurnOffRelay();
    else
        TurnOnRelay();
    if(er_count[0] == 2 && er_count[1] == 1 && er_count[2] == 1)
        ChangeLeadingController(1);
    if(er_count[0] == 1 && er_count[1] == 2 && er_count[2] == 1)
        ChangeLeadingController(2);
    if(er_count[0] == 1 && er_count[1] == 1 && er_count[2] == 2)
        ChangeLeadingController(3);
    s[0] = 100000;
    s[1] = 300000;
    s[2] = 500000;
}

void ChangeLeadingController(unsigned int FailedControllerNum)
{
    if(FailedControllerNum!=_leadingController)
        return;
    if((FailedControllerNum + 1) <= 3)
        _leadingController = FailedControllerNum + 1;
    else
        _leadingController = 1;
    EditParameterValue(0x2002, &_leadingController, 2);
}

void TurnOnRelay()
{
    TRISBbits.TRISB8 = 0;//set output on RB8
    LATBbits.LATB8 = 0;
}
void TurnOffRelay()
{
    TRISBbits.TRISB8 = 0;//set output on RB8
    LATBbits.LATB8 = 1;
}