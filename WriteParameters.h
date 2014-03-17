/* 
 * File:   WriteParameters.h
 * Author: Æåíÿ
 *
 * Created on 21 ??????? 2014 ?., 10:22
 */

unsigned char WriteAllParameters()
{
    Formatting(); // write FAT system to FRAM
    char name[] = "inf";
    DeviceInformation deviceInformation;
    deviceInformation.ObjectCount = 7;
    deviceInformation.ParametersCount = 14;
    deviceInformation.SystemName[0] = 0;
    strcat(deviceInformation.SystemName, "don_avto_1");
     deviceInformation.DeviceName[0] = 0;
    strcat(deviceInformation.DeviceName,"fpk1");
    deviceInformation.DeviceVersion[0] = 0;
    strcat(deviceInformation.DeviceVersion,"v1.0");
    deviceInformation.SoftVersion[0] = 0;
    strcat(deviceInformation.SoftVersion,"1.0");
    deviceInformation.CanVersion[0] = 0;
    strcat(deviceInformation.CanVersion,"can1");

    if(!AddParameter(name,0xF,&deviceInformation,28))
        return 0;
    
    //node id
    long data = 4;
    char name1[] = "node_id";
    AddParameter(name1, 0x10, &data, 4);
    //leading controller
    data = 1;
    char name2[] = "lead_controller";
    AddParameter(name2, 0x3, &data, 4);
    //accuracy
    data = 1000;
    char name3[] = "accuracy";
    AddParameter(name3, 0x10, &data, 4);
    //highEdge
    data = 50000;
    char name4[] = "high_edge";
    AddParameter(name4, 0x10, &data, 4);
    //lowEdge
    data = -250000;
    char name5[] = "low_edge";
    AddParameter(name5, 0x10, &data, 4);
    //s_point
    data = 100000;
    char name6[] = "s_point1";
    AddParameter(name6, 0x10, &data, 4);
    data = 50000;
    char name7[] = "s_point2";
    AddParameter(name7, 0x10, &data, 4);
    data = 40000;
    char name8[] = "s_point3";
    AddParameter(name8, 0x10, &data, 4);
    data = 30000;
    char name9[] = "s_point4";
    AddParameter(name9, 0x10, &data, 4);
    data = 20000;
    char name10[] = "s_point5";
    AddParameter(name10, 0x10, &data, 4);
    data = 10000;
    char name11[] = "s_point6";
    AddParameter(name11, 0x10, &data, 4);
    data = 5000;
    char name12[] = "s_point7";
    AddParameter(name12, 0x10, &data, 4);
    data = 0;
    char name13[] = "s_point8";
    AddParameter(name13, 0x10, &data, 4);
    

    return 1;
}

