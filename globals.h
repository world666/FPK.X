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

long _sPoint[8];// buf

//parameters ids
#define NODE_ID 0x2001
#define LEADING_CONTROLLER 0x2002
#define ACCURACY 0x2003
#define HIGH_EDGE 0x2004
#define LOW_EDGE 0x2005
#define S_POINT 0x2006

void ReadConfig()
{
    ReadParameterValue(NODE_ID, &_nodeId);
    ReadParameterValue(LEADING_CONTROLLER, &_leadingController);
    ReadParameterValue(ACCURACY, &_accuracy);
    ReadParameterValue(HIGH_EDGE, &_highEdge);
    ReadParameterValue(LOW_EDGE, &_lowEdge);
    int i = 0;
    for(i; i < 8; i++)
        ReadParameterValue(S_POINT + i, &_sPoint[i]);
    i = 0;
    for(i; i < 8; i++)
    {
       _sPointUp[i] =  _highEdge - _sPoint[i];
       _sPointDown[i] =  _lowEdge + _sPoint[i];
    }
}

void UpdateConfig(int parameterId)
{
    switch(parameterId)
    {
        case NODE_ID:
            ReadParameterValue(NODE_ID,&_nodeId);
            break;
        case LEADING_CONTROLLER:
            ReadParameterValue(LEADING_CONTROLLER, &_leadingController);
            break;
        case ACCURACY:
            ReadParameterValue(ACCURACY, &_accuracy);
            break;
        case HIGH_EDGE:
            ReadParameterValue(HIGH_EDGE,&_highEdge);
            int i = 0;
            for(i; i < 8; i++)
            {
                _sPointUp[i] =  _highEdge - _sPoint[i];
                _sPointDown[i] =  _lowEdge + _sPoint[i];
            }
            break;
        case LOW_EDGE:
            ReadParameterValue(LOW_EDGE,&_lowEdge);
            int j = 0;
            for(j; j < 8; j++)
            {
                _sPointUp[j] =  _highEdge - _sPoint[j];
                _sPointDown[j] =  _lowEdge + _sPoint[j];
            }
            break;
        case S_POINT:
            ReadParameterValue(S_POINT, &_sPoint[0]);
            _sPointUp[0] =  _highEdge - _sPoint[0];
            _sPointDown[0] =  _lowEdge + _sPoint[0];
            break;
        case S_POINT + 1:
            ReadParameterValue(S_POINT + 1, &_sPoint[1]);
            _sPointUp[1] =  _highEdge - _sPoint[1];
            _sPointDown[1] =  _lowEdge + _sPoint[1];
            break;
        case S_POINT + 2:
            ReadParameterValue(S_POINT + 2, &_sPoint[2]);
            _sPointUp[2] =  _highEdge - _sPoint[2];
            _sPointDown[2] =  _lowEdge + _sPoint[2];
            break;
        case S_POINT + 3:
            ReadParameterValue(S_POINT + 3, &_sPoint[3]);
            _sPointUp[3] =  _highEdge - _sPoint[3];
            _sPointDown[3] =  _lowEdge + _sPoint[3];
            break;
        case S_POINT + 4:
            ReadParameterValue(S_POINT + 4, &_sPoint[4]);
            _sPointUp[4] =  _highEdge - _sPoint[4];
            _sPointDown[4] =  _lowEdge + _sPoint[4];
            break;
        case S_POINT + 5:
            ReadParameterValue(S_POINT + 5, &_sPoint[5]);
            _sPointUp[5] =  _highEdge - _sPoint[5];
            _sPointDown[5] =  _lowEdge + _sPoint[5];
            break;
        case S_POINT + 6:
            ReadParameterValue(S_POINT + 6, &_sPoint[6]);
            _sPointUp[6] =  _highEdge - _sPoint[6];
            _sPointDown[6] =  _lowEdge + _sPoint[6];
            break;
        case S_POINT + 7:
            ReadParameterValue(S_POINT + 7, &_sPoint[7]);
            _sPointUp[7] =  _highEdge - _sPoint[7];
            _sPointDown[7] =  _lowEdge + _sPoint[7];
            break;
    }
}