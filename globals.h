/* 
 * File:   globals.h
 * Author: Æåíÿ
 *
 * Created on 24 ??????? 2014 ?., 12:27
 */

int _nodeId;
int _leadingController;
long _accuracy;//mm ; accuracy between s1, s2, s3
long _highEdge;
long _lowEdge;
long _sPointUp[8];
long _sPointDown[8];

void ReadGlobalVars()
{
    long _sPoint[8];
    ReadParameterValue(0x2001, &_nodeId);
    ReadParameterValue(0x2002, &_leadingController);
    ReadParameterValue(0x2003, &_accuracy);
    ReadParameterValue(0x2004, &_highEdge);
    ReadParameterValue(0x2005, &_lowEdge);
    int i = 0;
    for(i; i < 8; i++)
        ReadParameterValue(0x2006 + i, &_sPoint[i]);
    i = 0;
    for(i; i < 8; i++)
    {
       _sPointUp[i] =  _highEdge - _sPoint[i];
       _sPointDown[i] =  _lowEdge + _sPoint[i];
    }
}