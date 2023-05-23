
#include "Arduino.h"
#include "main.h"
#include "interface_NEOPIXEL.h"
#include "Interface_Accelerometre.h"
#include "serviceBaseDeTemps.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
//#include "BFIO"
#include <stdio.h>
#include "processus_Calcule_Accelerometre.h"


void processus_Calcule_Accelerometre_Offset();

PROCESSUS_CALCULEACCELEROMETRE processus_Calcule_Accelerometre_Struct;

double gyro_X_OFFSET = 0;
double gyro_Y_OFFSET = 0;
double gyro_Z_OFFSET = 0;

float gyroX = 0;
float gyroY = 0;
float gyroZ = 0;

float yaw = 0;

int compt42 = 0;

float last_Pithc = 0;
float last_Roll = 0;
float last_Yaw = 0;

float elapsedTime, currentTime = 0, previousTime;

int processus_Calcule_Accelerometre_initialise()
{
    processus_Calcule_Accelerometre_Offset();
    serviceBaseDeTemps_executeDansLoop[PROCESSUS_CALCULE_ACCELEROMETRE_PHASE] = processus_Calcule_Accelerometre_Affiche;
    return 0;
}


void processus_Calcule_Accelerometre_Offset()
{
    sensors_event_t a;
    sensors_event_t g;
    sensors_event_t temp;
    int c = 0;
    while(c < 200)
    {

        Get_Sensor_Event(&a, &g, &temp);
        gyro_X_OFFSET = gyro_X_OFFSET + (double)g.gyro.x;
        gyro_Y_OFFSET = gyro_Y_OFFSET + (double)g.gyro.y;
        gyro_Z_OFFSET = gyro_Z_OFFSET + (double)g.gyro.z;
        c++;
    }

    gyro_X_OFFSET = gyro_X_OFFSET / 200.0;
    gyro_Y_OFFSET = gyro_Y_OFFSET / 200.0;
    gyro_Z_OFFSET = gyro_Z_OFFSET / 200.0;

    //serviceBaseDeTemps_execute[PROCESSUS_CALCULE_ACCELEROMETRE_PHASE] = processus_Calcule_Accelerometre_Affiche;

}


void processus_Calcule_Accelerometre_Affiche() 
{
    sensors_event_t a;
    sensors_event_t g;
    sensors_event_t temp;


    Get_Sensor_Event(&a, &g, &temp);

    
    previousTime = currentTime;        // Previous time is stored before the actual time read
    currentTime = millis();            // Current time actual time read
    elapsedTime = (currentTime - previousTime) / 1000; // Divide by 1000 to get seconds

    gyroX = gyroX + ((double)g.gyro.x  + 0.054113     ) * elapsedTime; // deg/s * s = deg
    gyroY = gyroY + ((double)g.gyro.y  + 0.026281     ) * elapsedTime;
    yaw =  yaw + ((double)g.gyro.z     + 0.008106       )   * elapsedTime;
    // Complementary filter - combine acceleromter and gyro angle values
    float roll = 0.96 * gyroX + 0.04 * a.acceleration.x;
    float pitch =  0.96 * gyroY + 0.04 * a.acceleration.y;
    //interface_Accelerometre_Rotation();
    

    // Serial.print(roll);
    // Serial.print("/");
    // Serial.print(pitch);//pas bon
    // Serial.print("/");
    // Serial.println(yaw);

    last_Pithc = pitch;
    last_Roll = roll;
    last_Yaw = yaw;

    compt42++;
    
}
