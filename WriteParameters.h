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
    deviceInformation.ParametersCount = 4;
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
    long data1 = 4;
    char name1[] = "node_id";
    AddParameter(name1, 0x10, &data1, 4);
    //leading controller
    long data2 = 1;
    char name2[] = "lead_controller";
    AddParameter(name2, 0x3, &data2, 4);
    //accuracy
    long data3 = 1000;
    char name3[] = "accuracy";
    AddParameter(name3, 0x10, &data3, 4);
    //code domain
    char data4[120];
    int i = 0;
    for(i; i < 120; i++)
        data4[i] = 0;
    char name4[] = "s_table";
    AddParameter(name4, 0xF, &data4, 120);

    return 1;
}

