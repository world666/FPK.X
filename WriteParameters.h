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
    deviceInformation.ParametersCount = 19;
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
    //s_point_up
    data = -50000;
    char name4[] = "s_point_up1";
    AddParameter(name4, 0x10, &data, 4);
    data = -20000;
    char name5[] = "s_point_up2";
    AddParameter(name5, 0x10, &data, 4);
    data = 0;
    char name6[] = "s_point_up3";
    AddParameter(name6, 0x10, &data, 4);
    data = 5000;
    char name7[] = "s_point_up4";
    AddParameter(name7, 0x10, &data, 4);
    data = 10000;
    char name8[] = "s_point_up5";
    AddParameter(name8, 0x10, &data, 4);
    data = 20000;
    char name9[] = "s_point_up6";
    AddParameter(name9, 0x10, &data, 4);
    data = 30000;
    char name10[] = "s_point_up7";
    AddParameter(name10, 0x10, &data, 4);
    data = 40000;
    char name11[] = "s_point_up8";
    AddParameter(name11, 0x10, &data, 4);
    //s_point_down
    data = -150000;
    char name12[] = "s_point_down1";
    AddParameter(name12, 0x10, &data, 4);
    data = -200000;
    char name13[] = "s_point_down2";
    AddParameter(name13, 0x10, &data, 4);
    data = -210000;
    char name14[] = "s_point_down3";
    AddParameter(name14, 0x10, &data, 4);
    data = -220000;
    char name15[] = "s_point_down4";
    AddParameter(name15, 0x10, &data, 4);
    data = -230000;
    char name16[] = "s_point_down5";
    AddParameter(name16, 0x10, &data, 4);
    data = -240000;
    char name17[] = "s_point_down6";
    AddParameter(name17, 0x10, &data, 4);
    data = -245000;
    char name18[] = "s_point_down7";
    AddParameter(name18, 0x10, &data, 4);
    data = -250000;
    char name19[] = "s_point_down8";
    AddParameter(name19, 0x10, &data, 4);

    return 1;
}

