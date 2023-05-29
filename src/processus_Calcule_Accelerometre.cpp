
#include "Arduino.h"
#include "main.h"
#include "interface_NEOPIXEL.h"
#include "Interface_Accelerometre.h"
#include "serviceBaseDeTemps.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <stdio.h>
#include "processus_Calcule_Accelerometre.h"
#include "Processus_Communication.h"


//http://www.geekmomprojects.com/gyroscopes-and-accelerometers-on-a-chip/

void processus_Calcule_Accelerometre_Offset();
void processus_Calcule_Accelerometre_GetPosition();
void processus_Calcule_Accelerometre_Determine_Servo_Position();
void processus_Calcule_Accelerometre_Check_Under_Value_Cap(float *DA_angle,
float *GA_angle,
float *DR_angle,
float *GR_angle,
float *H_angle, 
float *S_angle);
float map_Float(float x, float in_min, float in_max, float out_min, float out_max) ;

PROCESSUS_CALCULEACCELEROMETRE processus_Calcule_Accelerometre_Struct;


float gyroX = 0;
float gyroY = 0;
float gyroZ = 0;


float elapsedTime, currentTime = 0, previousTime;

int compteur_UpdateVal = 0;

int processus_Calcule_Accelerometre_initialise()
{
    processus_Calcule_Accelerometre_Struct.Wrong_Way_GA_angle = (float)1.0;
    processus_Calcule_Accelerometre_Struct.Wrong_Way_GR_angle = (float)1.0;
    processus_Calcule_Accelerometre_Struct.Wrong_Way_DA_angle = (float)-1.0;
    processus_Calcule_Accelerometre_Struct.Wrong_Way_DR_angle = (float)-1.0;
    processus_Calcule_Accelerometre_Struct.Wrong_Way_H_angle = (float)1.0;
    processus_Calcule_Accelerometre_Struct.Wrong_Way_S_angle = (float)-1.0;


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

   
    //Connaitre l'orientation
    processus_Calcule_Accelerometre_Struct.Orientation_Pitch = 0.96 * (processus_Calcule_Accelerometre_Struct.Orientation_Pitch + ((float)g.gyro.x  + 0.054113) * elapsedTime) + 0.04 * a.acceleration.x;
    processus_Calcule_Accelerometre_Struct.Orientation_Roll = 0.96 * (processus_Calcule_Accelerometre_Struct.Orientation_Roll + ((float)g.gyro.y  + 0.026281) * elapsedTime) + 0.04 * a.acceleration.y;
    processus_Calcule_Accelerometre_Struct.Orientation_Yaw =  processus_Calcule_Accelerometre_Struct.Orientation_Yaw + ((float)g.gyro.z + 0.008106);

    


    //Permet de rotationner
    gyroX = processus_Calcule_Accelerometre_Struct.Roll + ((float)g.gyro.x  + 0.054113     ) * elapsedTime + ((float)processus_Communication_Struct_WANTED_Value.Roll/1000.0 * elapsedTime); // deg/s * s = deg
    gyroY = processus_Calcule_Accelerometre_Struct.Pitch + ((float)g.gyro.y  + 0.026281     ) * elapsedTime + ((float)processus_Communication_Struct_WANTED_Value.Pitch/1000.0 * elapsedTime);
    processus_Calcule_Accelerometre_Struct.Yaw =  processus_Calcule_Accelerometre_Struct.Yaw + ((float)g.gyro.z + 0.008106) * elapsedTime + ((float)processus_Communication_Struct_WANTED_Value.Yaw/1000.0 * elapsedTime);
    // Complementary filter - combine acceleromter and gyro angle values
    processus_Calcule_Accelerometre_Struct.Roll = 0.96 * gyroX + 0.04 * a.acceleration.x;
    processus_Calcule_Accelerometre_Struct.Pitch =  0.96 * gyroY + 0.04 * a.acceleration.y;
    

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
    compteur_UpdateVal++;
    if(compteur_UpdateVal > 100)
    {
        processus_Communication_Struct_ACTUAL_Value.Pitch = (signed char)map_Float(processus_Calcule_Accelerometre_Struct.Orientation_Pitch, -1.0, 1.0, 0.0, 180.0);
        processus_Communication_Struct_ACTUAL_Value.Roll = (signed char)map_Float(processus_Calcule_Accelerometre_Struct.Orientation_Roll, -1.0, 1.0, 0.0, 180.0);
        processus_Communication_Struct_ACTUAL_Value.Yaw = (signed char)map_Float(processus_Calcule_Accelerometre_Struct.Orientation_Yaw, -1.0, 1.0, 0.0, 180.0);
        compteur_UpdateVal = 0;
    }

    float DA_angle = processus_Calcule_Accelerometre_Struct.Pitch - processus_Calcule_Accelerometre_Struct.Roll;
    float GA_angle = processus_Calcule_Accelerometre_Struct.Pitch - processus_Calcule_Accelerometre_Struct.Roll;

    float DR_angle = (-1*processus_Calcule_Accelerometre_Struct.Pitch) + processus_Calcule_Accelerometre_Struct.Roll;
    float GR_angle = (-1*processus_Calcule_Accelerometre_Struct.Pitch) + processus_Calcule_Accelerometre_Struct.Roll;

    float H_angle = processus_Calcule_Accelerometre_Struct.Yaw + processus_Calcule_Accelerometre_Struct.Roll;
    float S_angle = processus_Calcule_Accelerometre_Struct.Yaw - processus_Calcule_Accelerometre_Struct.Roll;


    //je m'assure de ne pas depasser la val max ou min
    processus_Calcule_Accelerometre_Check_Under_Value_Cap(&DA_angle,&GA_angle,&DR_angle,&GR_angle,&H_angle, &S_angle);


 

    processus_Calcule_Accelerometre_Struct.Wanted_SERVO_DA_angle = (unsigned char)map_Float((float)processus_Calcule_Accelerometre_Struct.Wrong_Way_DA_angle * DA_angle, -1.0, 1.0, 0.0, 180.0);
    processus_Calcule_Accelerometre_Struct.Wanted_SERVO_GA_angle = (unsigned char)map_Float((float)processus_Calcule_Accelerometre_Struct.Wrong_Way_GA_angle * GA_angle, -1.0, 1.0, 0.0, 180.0);

    processus_Calcule_Accelerometre_Struct.Wanted_SERVO_DR_angle = (unsigned char)map_Float((float)processus_Calcule_Accelerometre_Struct.Wrong_Way_DR_angle * DR_angle, -1.0, 1.0, 0.0, 180.0);
    processus_Calcule_Accelerometre_Struct.Wanted_SERVO_GR_angle = (unsigned char)map_Float((float)processus_Calcule_Accelerometre_Struct.Wrong_Way_GR_angle * GR_angle, -1.0, 1.0, 0.0, 180.0);

    processus_Calcule_Accelerometre_Struct.Wanted_SERVO_H_angle =  (unsigned char)map_Float((float)processus_Calcule_Accelerometre_Struct.Wrong_Way_H_angle * H_angle, -1.0, 1.0, 0.0, 180.0);
    processus_Calcule_Accelerometre_Struct.Wanted_SERVO_S_angle =  (unsigned char)map_Float((float)processus_Calcule_Accelerometre_Struct.Wrong_Way_S_angle * S_angle, -1.0, 1.0, 0.0, 180.0);

}


void processus_Calcule_Accelerometre_Check_Under_Value_Cap(float *DA_angle,
float *GA_angle,
float *DR_angle,
float *GR_angle,
float *H_angle, 
float *S_angle)
{
    ////////////////////////// DA_angle
    if(*DA_angle > 1.0)
    {
        *DA_angle = 1.0;
    }
    if(*DA_angle < -1.0)
    {
        *DA_angle = -1.0;
    }

    ////////////////////////// GA_angle
    if(*GA_angle > 1.0)
    {
        *GA_angle = 1.0;
    }
    if(*GA_angle < -1.0)
    {
        *GA_angle = -1.0;
    } 

    ////////////////////////// DR_angle
    if(*DR_angle > 1.0)
    {
        *DR_angle = 1.0;
    }
    if(*DR_angle < -1.0)
    {
        *DR_angle = -1.0;
    } 

    ////////////////////////// GR_angle
    if(*GR_angle > 1.0)
    {
        *GR_angle = 1.0;
    }
    if(*GR_angle < -1.0)
    {
        *GR_angle = -1.0;
    } 

    ////////////////////////// H_angle
    if(*H_angle > 1.0)
    {
        *H_angle = 1.0;
    }
    if(*H_angle < -1.0)
    {
        *H_angle = -1.0;
    }  

    ////////////////////////// S_angle
    if(*S_angle > 1.0)
    {
        *S_angle = 1.0;
    }
    if(*S_angle < -1.0)
    {
        *S_angle = -1.0;
    }  
}



float map_Float(float x, float in_min, float in_max, float out_min, float out_max) 
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}