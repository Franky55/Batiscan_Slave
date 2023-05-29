
#include "Arduino.h"
#include "main.h"
#include "service_Protocole_SPI.h"
#include "interface_NEOPIXEL.h"
#include "serviceBaseDeTemps.h"
#include "Processus_Communication.h"

#include <stdio.h>

#define TRAME_SIZE 12

#define START_BYTE 'S'
#define START_BYTE_RECEIVE 'M'

#define POSITION_UNION_BOOL 1
#define POSITION_CAM_SERVO_ANGLE 2
#define POSITION_PRESSURE 3
#define POSITION_TEMPERATURE 5
#define POSITION_PITCH 6
#define POSITION_ROLL 7
#define POSITION_YAW 8
#define POSITION_SPEED 9
#define POSITION_BATTERY 10
#define POSITION_CHECKSUM 11



int service_Protocole_SPI_Read_Data(unsigned char* plane, unsigned char* size);

/**
 * @brief Return 0;
 * 
 * @return int 
 */
int service_Protocole_SPI_initialise(void)
{
    return 0;
}


/**
 * @brief La fonction check le packet recu 
 * 1er check la grosseur: return -3
 * 2e check START_BYTE: return -1
 * 3e check le checkSum: return -2
 * 
 * All good return 0
 * 
 * @param plane 
 * @param size 
 * @return int 
 */
int service_Protocole_SPI_Received(unsigned char* plane, unsigned char* size)
{
    if((*size) < TRAME_SIZE)            //La trame n'est pas asse long
    {
        return -3;
    }

    if(plane[0] != START_BYTE_RECEIVE)  //Pas de start byte
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


/**
 * @brief Met les variable dans la structure des valeurs WANTED
 * 
 * @param plane 
 * @param size 
 * @return int 
 */
int service_Protocole_SPI_Read_Data(unsigned char* plane, unsigned char* size)
{

    processus_Communication_Struct_WANTED_Value.union_Bool.All = plane[POSITION_UNION_BOOL];
    processus_Communication_Struct_WANTED_Value.Camera_Servo_Angle = plane[POSITION_CAM_SERVO_ANGLE];
    processus_Communication_Struct_WANTED_Value.Pressure = (plane[POSITION_PRESSURE+1] << 8) + plane[POSITION_PRESSURE];
    processus_Communication_Struct_WANTED_Value.Temperature = plane[POSITION_TEMPERATURE];
    processus_Communication_Struct_WANTED_Value.Pitch = plane[POSITION_PITCH];
    processus_Communication_Struct_WANTED_Value.Roll = plane[POSITION_ROLL];
    processus_Communication_Struct_WANTED_Value.Yaw = plane[POSITION_YAW];
    processus_Communication_Struct_WANTED_Value.Speed = plane[POSITION_SPEED];
    processus_Communication_Struct_WANTED_Value.Battery = plane[POSITION_BATTERY];

    return 0;
}

/**
 * @brief Prepare une trame a envoyer au master
 * Tous les etats des accesoires sont mis dans la trame
 * 
 * @param plane 
 * @param size 
 * @return int 
 */
int service_Protocole_SPI_Pepare_Trame_Slave_To_Master(unsigned char* plane, unsigned char* size)
{
    *size = TRAME_SIZE;
    

    plane[0] = START_BYTE;
    plane[POSITION_UNION_BOOL] = processus_Communication_Struct_ACTUAL_Value.union_Bool.All;
    plane[POSITION_CAM_SERVO_ANGLE] = processus_Communication_Struct_ACTUAL_Value.Camera_Servo_Angle;
    plane[POSITION_PRESSURE] = processus_Communication_Struct_ACTUAL_Value.Pressure;
    plane[POSITION_PRESSURE + 1] = (processus_Communication_Struct_ACTUAL_Value.Pressure >> 8) & 0x00FF;
    plane[POSITION_TEMPERATURE] = processus_Communication_Struct_ACTUAL_Value.Temperature;
    plane[POSITION_PITCH] = processus_Communication_Struct_ACTUAL_Value.Pitch;
    plane[POSITION_ROLL] = processus_Communication_Struct_ACTUAL_Value.Roll;
    plane[POSITION_YAW] = processus_Communication_Struct_ACTUAL_Value.Yaw;
    plane[POSITION_SPEED] = processus_Communication_Struct_ACTUAL_Value.Speed;
    plane[POSITION_BATTERY] = processus_Communication_Struct_ACTUAL_Value.Battery;

    unsigned char checkSum = 0;
    for (int i = 0; i < TRAME_SIZE-1; i++)
    {
        checkSum += plane[i];
    }

    plane[POSITION_CHECKSUM] = checkSum;
    

    return 0;
}


