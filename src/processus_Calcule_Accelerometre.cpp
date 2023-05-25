
#include "Arduino.h"
#include "main.h"
#include "interface_NEOPIXEL.h"
#include "Interface_Accelerometre.h"
#include "serviceBaseDeTemps.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <stdio.h>
#include "processus_Calcule_Accelerometre.h"


void processus_Calcule_Accelerometre_Offset();
void processus_Calcule_Accelerometre_GetPosition();
void processus_Calcule_Accelerometre_Determine_Servo_Position();
float map_Float(float x, float in_min, float in_max, float out_min, float out_max) ;

PROCESSUS_CALCULEACCELEROMETRE processus_Calcule_Accelerometre_Struct;



float gyroX = 0;
float gyroY = 0;
float gyroZ = 0;


float elapsedTime, currentTime = 0, previousTime;

int processus_Calcule_Accelerometre_initialise()
{
    processus_Calcule_Accelerometre_Struct.Wrong_Way_GA_angle = (float)1.0;
    processus_Calcule_Accelerometre_Struct.Wrong_Way_GR_angle = (float)1.0;
    processus_Calcule_Accelerometre_Struct.Wrong_Way_DA_angle = (float)-1.0;
    processus_Calcule_Accelerometre_Struct.Wrong_Way_DR_angle = (float)-1.0;
    processus_Calcule_Accelerometre_Struct.Wrong_Way_H_angle = (float)1.0;
    processus_Calcule_Accelerometre_Struct.Wrong_Way_S_angle = (float)1.0;


    processus_Calcule_Accelerometre_Offset();
    serviceBaseDeTemps_executeDansLoop[PROCESSUS_CALCULE_ACCELEROMETRE_PHASE] = processus_Calcule_Accelerometre_GetPosition;
    serviceBaseDeTemps_execute[PROCESSUS_CALCULE_ACCELERATION] = processus_Calcule_Accelerometre_Determine_Servo_Position;
    return 0;
}


void processus_Calcule_Accelerometre_Offset()
{
    // sensors_event_t a;
    // sensors_event_t g;
    // sensors_event_t temp;
    // int c = 0;
    // while(c < 200)
    // {

    //     Get_Sensor_Event(&a, &g, &temp);
    //     gyro_X_OFFSET = gyro_X_OFFSET + (double)g.gyro.x;
    //     gyro_Y_OFFSET = gyro_Y_OFFSET + (double)g.gyro.y;
    //     gyro_Z_OFFSET = gyro_Z_OFFSET + (double)g.gyro.z;
    //     c++;
    // }

    // gyro_X_OFFSET = gyro_X_OFFSET / 200.0;
    // gyro_Y_OFFSET = gyro_Y_OFFSET / 200.0;
    // gyro_Z_OFFSET = gyro_Z_OFFSET / 200.0;

    //serviceBaseDeTemps_execute[PROCESSUS_CALCULE_ACCELEROMETRE_PHASE] = processus_Calcule_Accelerometre_Affiche;

}


void processus_Calcule_Accelerometre_GetPosition() 
{
    sensors_event_t a;
    sensors_event_t g;
    sensors_event_t temp;


    Get_Sensor_Event(&a, &g, &temp);

    
    previousTime = currentTime;        // Previous time is stored before the actual time read
    currentTime = millis();            // Current time actual time read
    elapsedTime = (currentTime - previousTime) / 1000; // Divide by 1000 to get seconds

    gyroX = gyroX + ((float)g.gyro.x  + 0.054113     ) * elapsedTime; // deg/s * s = deg
    gyroY = gyroY + ((float)g.gyro.y  + 0.026281     ) * elapsedTime;
    processus_Calcule_Accelerometre_Struct.Yaw =  processus_Calcule_Accelerometre_Struct.Yaw + ((float)g.gyro.z     + 0.008106       )   * elapsedTime;
    // Complementary filter - combine acceleromter and gyro angle values
    processus_Calcule_Accelerometre_Struct.Roll = 0.96 * gyroX + 0.04 * a.acceleration.x;
    processus_Calcule_Accelerometre_Struct.Pitch =  0.96 * gyroY + 0.04 * a.acceleration.y;
    //interface_Accelerometre_Rotation();
    

    // Serial.print(processus_Calcule_Accelerometre_Struct.Roll);
    // Serial.print("/");
    // Serial.print(processus_Calcule_Accelerometre_Struct.Pitch);//pas bon
    // Serial.print("/");
    // Serial.println(processus_Calcule_Accelerometre_Struct.Yaw);

    // last_Pithc = processus_Calcule_Accelerometre_Struct.Pitch;
    // last_Roll = processus_Calcule_Accelerometre_Struct.Roll;
    // last_Yaw = yaw;

    // compt42++;
    
}



void processus_Calcule_Accelerometre_Determine_Servo_Position()
{
    // float wanted_Servo_Pitch = map_Float(processus_Calcule_Accelerometre_Struct.Pitch, -10.0, 10.0, 0.0, 180.0);
    // float wanted_Servo_Roll = map_Float(processus_Calcule_Accelerometre_Struct.Roll, -10.0, 10.0, 0.0, 180.0);
    // float wanted_Servo_Yaw = map_Float(processus_Calcule_Accelerometre_Struct.Yaw, -10.0, 10.0, 0.0, 180.0);


    float DA_angle = processus_Calcule_Accelerometre_Struct.Pitch - processus_Calcule_Accelerometre_Struct.Roll;
    float GA_angle = processus_Calcule_Accelerometre_Struct.Pitch - processus_Calcule_Accelerometre_Struct.Roll;

    float DR_angle = (-1*processus_Calcule_Accelerometre_Struct.Pitch) + processus_Calcule_Accelerometre_Struct.Roll;
    float GR_angle = (-1*processus_Calcule_Accelerometre_Struct.Pitch) + processus_Calcule_Accelerometre_Struct.Roll;

    float H_angle = processus_Calcule_Accelerometre_Struct.Yaw + processus_Calcule_Accelerometre_Struct.Roll;
    float S_angle = processus_Calcule_Accelerometre_Struct.Yaw - processus_Calcule_Accelerometre_Struct.Roll;






 

    processus_Calcule_Accelerometre_Struct.Wanted_SERVO_DA_angle = (unsigned char)map_Float((float)processus_Calcule_Accelerometre_Struct.Wrong_Way_DA_angle * DA_angle, -1.0, 1.0, 0.0, 180.0);
    processus_Calcule_Accelerometre_Struct.Wanted_SERVO_GA_angle = (unsigned char)map_Float((float)processus_Calcule_Accelerometre_Struct.Wrong_Way_GA_angle * GA_angle, -1.0, 1.0, 0.0, 180.0);

    processus_Calcule_Accelerometre_Struct.Wanted_SERVO_DR_angle = (unsigned char)map_Float((float)processus_Calcule_Accelerometre_Struct.Wrong_Way_DR_angle * DR_angle, -1.0, 1.0, 0.0, 180.0);
    processus_Calcule_Accelerometre_Struct.Wanted_SERVO_GR_angle = (unsigned char)map_Float((float)processus_Calcule_Accelerometre_Struct.Wrong_Way_GR_angle * GR_angle, -1.0, 1.0, 0.0, 180.0);

    processus_Calcule_Accelerometre_Struct.Wanted_SERVO_H_angle =  (unsigned char)map_Float((float)processus_Calcule_Accelerometre_Struct.Wrong_Way_H_angle * H_angle, -1.0, 1.0, 0.0, 180.0);
    processus_Calcule_Accelerometre_Struct.Wanted_SERVO_S_angle =  (unsigned char)map_Float((float)processus_Calcule_Accelerometre_Struct.Wrong_Way_S_angle * S_angle, -1.0, 1.0, 0.0, 180.0);

}



float map_Float(float x, float in_min, float in_max, float out_min, float out_max) 
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}