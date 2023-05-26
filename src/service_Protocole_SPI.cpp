
#include "Arduino.h"
#include "main.h"
#include "service_Protocole_SPI.h"
#include "interface_NEOPIXEL.h"
#include "serviceBaseDeTemps.h"
#include "Processus_Communication.h"

#include <stdio.h>

#define TRAME_SIZE 12

#define START_BYTE 'M'

#define POSITION_UNION_BOOL 1
#define POSITION_CAM_SERVO_ANGLE 2
#define POSITION_PRESSURE 3
#define POSITION_TEMPERATURE 5
#define POSITION_PITCH 6
#define POSITION_ROLL 7
#define POSITION_YAW 8
#define POSITION_SPEED 9
#define POSITION_BATTERY 10



int service_Protocole_SPI_Read_Data(unsigned char* plane, int* size);


int service_Protocole_SPI_initialise(void)
{
    return 0;
}

int service_Protocole_SPI_Received(unsigned char* plane, int* size)
{
    if(plane[0] != START_BYTE)  //Pas de start byte
    {
        return -1;
    }

    unsigned char CheckSum = 0;
    for(int i = 0; i < (*size) - 1; i++)
    {
        CheckSum = CheckSum + plane[i];
    }

    if(CheckSum != plane[(*size)-1])    //Pas bon check sum
    {
        return -2;
    }

    return service_Protocole_SPI_Read_Data(plane, size); //update les valeurs
}

int service_Protocole_SPI_Read_Data(unsigned char* plane, unsigned char* size)
{
    if(*size < TRAME_SIZE)
    {
        return -1;
    }
    processus_Communication_Struct_ACTUAL_Value.union_Bool.All = plane[POSITION_UNION_BOOL];
    processus_Communication_Struct_ACTUAL_Value.Camera_Servo_Angle = plane[POSITION_CAM_SERVO_ANGLE];
    processus_Communication_Struct_ACTUAL_Value.Pressure = (plane[POSITION_PRESSURE+1] << 8) + plane[POSITION_PRESSURE];
    processus_Communication_Struct_ACTUAL_Value.Temperature = plane[POSITION_TEMPERATURE];
    processus_Communication_Struct_ACTUAL_Value.Pitch = plane[POSITION_PITCH];
    processus_Communication_Struct_ACTUAL_Value.Roll = plane[POSITION_ROLL];
    processus_Communication_Struct_ACTUAL_Value.Yaw = plane[POSITION_YAW];
    processus_Communication_Struct_ACTUAL_Value.Speed = plane[POSITION_SPEED];
    processus_Communication_Struct_ACTUAL_Value.Battery = plane[POSITION_BATTERY];

    return 0;
}

int service_Protocole_SPI_Pepare_Trame_Slave(unsigned char* plane, unsigned char* size)
{
    
    plane[POSITION_UNION_BOOL] = processus_Communication_Struct_WANTED_Value.union_Bool.All;
    plane[POSITION_CAM_SERVO_ANGLE] = processus_Communication_Struct_WANTED_Value.Camera_Servo_Angle;
    plane[POSITION_PRESSURE] = processus_Communication_Struct_WANTED_Value.Pressure;
    plane[POSITION_PRESSURE + 1] = (processus_Communication_Struct_WANTED_Value.Pressure >> 8) & 0x00FF;
    plane[POSITION_TEMPERATURE] = processus_Communication_Struct_WANTED_Value.Temperature;
    plane[POSITION_PITCH] = processus_Communication_Struct_WANTED_Value.Pitch;
    plane[POSITION_ROLL] = processus_Communication_Struct_WANTED_Value.Roll;
    plane[POSITION_YAW] = processus_Communication_Struct_WANTED_Value.Yaw;
    plane[POSITION_SPEED] = processus_Communication_Struct_WANTED_Value.Speed;
    plane[POSITION_BATTERY] = processus_Communication_Struct_WANTED_Value.Battery;


    return 0;
}


