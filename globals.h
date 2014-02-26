/* 
 * File:   globals.h
 * Author: Æåíÿ
 *
 * Created on 24 ??????? 2014 ?., 12:27
 */

int _nodeId;
int _leadingController;
long _accuracy;//mm ; accuracy between s1, s2, s3
long _sPointUp[8];
long _sPointDown[8];

void ReadGlobalVars()
{
    ReadParameterValue(0x2001, &_nodeId);
    ReadParameterValue(0x2002, &_leadingController);
    ReadParameterValue(0x2003, &_accuracy);
    int i = 0;
    for(i; i < 8; i++)
        ReadParameterValue(0x2004 + i, &_sPointUp[i]);
    i = 0;
    for(i; i < 8; i++)
        ReadParameterValue(0x200C + i, &_sPointDown[i]);
}