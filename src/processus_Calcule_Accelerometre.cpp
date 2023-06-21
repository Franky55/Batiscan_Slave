
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


#define MAX_FLOAT_ACC 10.0
#define MIN_FLOAT_ACC -10.0

#define MIN_ORIENTATION -127
#define MID_ORIENTATION 0
#define MAX_ORIENTATION 127

//http://www.geekmomprojects.com/gyroscopes-and-accelerometers-on-a-chip/

void processus_Calcule_Accelerometre_Offset();
void processus_Calcule_Accelerometre_GetPosition();
void processus_Calcule_Accelerometre_Determine_Servo_Position();
void processus_Calcule_Accelerometre_Calcule_Orientation(sensors_event_t a,
    sensors_event_t g,
    sensors_event_t temp);
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
    processus_Calcule_Accelerometre_Struct.Wrong_Way_H_angle = (float)-1.0;
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

/**
 * @brief Cette fonction se fait dans le gere loop du main
 * Il prend le data de l'accélérometre et le gyroscope
 * 
 */
void processus_Calcule_Accelerometre_GetPosition() 
{
    /*
    Shawn si finalement le PCB se trouve en l'envers il faudra modifier le code.

    Je n'ai pas fait de modification dans le code, mais je crois qu'il faudrait juste faire *-1 devant les variables suivante:
    a.acceleration.x
    a.acceleration.y
    a.acceleration.z

    il y a aussi peut etre, mais je ne crois pas:
    g.gyro.x 
    g.gyro.y
    g.gyro.z


    */


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
    processus_Calcule_Accelerometre_Struct.Orientation_Yaw =  processus_Calcule_Accelerometre_Struct.Orientation_Yaw + (((float)g.gyro.z + 0.008106) * elapsedTime);

    


    //Permet de rotationner
    gyroX = processus_Calcule_Accelerometre_Struct.Pitch + ((float)g.gyro.x  + 0.054113     ) * elapsedTime + ((float)processus_Communication_Struct_WANTED_Value.Pitch * elapsedTime); // deg/s * s = deg
    gyroY = processus_Calcule_Accelerometre_Struct.Roll + ((float)g.gyro.y  + 0.026281     ) * elapsedTime + ((float)processus_Communication_Struct_WANTED_Value.Roll * elapsedTime);
    processus_Calcule_Accelerometre_Struct.Yaw =  (processus_Calcule_Accelerometre_Struct.Yaw + ((float)g.gyro.z + 0.008106) * elapsedTime);// - ((float)processus_Communication_Struct_WANTED_Value.Yaw/100.0 * elapsedTime));
    // Complementary filter - combine acceleromter and gyro angle values
    processus_Calcule_Accelerometre_Struct.Pitch = 0.96 * gyroX + 0.04 * a.acceleration.x;
    processus_Calcule_Accelerometre_Struct.Roll =  0.96 * gyroY + 0.04 * a.acceleration.y;
    


    compteur_UpdateVal++;
    if(compteur_UpdateVal > 100)
    {
        processus_Calcule_Accelerometre_Calcule_Orientation(a, g, temp);
        compteur_UpdateVal = 0;
    }

 
    
}


/**
 * @brief Cette fonction prend le data récupéré pour déterminer l'angle des servos moteurs
 * Cette fonction est dans la base de temps
 * 
 */
void processus_Calcule_Accelerometre_Determine_Servo_Position()
{
    

    float DA_angle = (-1*processus_Calcule_Accelerometre_Struct.Pitch) - processus_Calcule_Accelerometre_Struct.Roll;
    float GA_angle = (-1*processus_Calcule_Accelerometre_Struct.Pitch) + processus_Calcule_Accelerometre_Struct.Roll;

    float DR_angle = (-1*processus_Calcule_Accelerometre_Struct.Pitch) - processus_Calcule_Accelerometre_Struct.Roll;
    float GR_angle = (-1*processus_Calcule_Accelerometre_Struct.Pitch) + processus_Calcule_Accelerometre_Struct.Roll;

    float H_angle = map_Float((float)processus_Calcule_Accelerometre_Struct.Wrong_Way_H_angle * (float)processus_Communication_Struct_WANTED_Value.Yaw, 127, -127, MIN_FLOAT_ACC, MAX_FLOAT_ACC) + processus_Calcule_Accelerometre_Struct.Roll;
    float S_angle = map_Float((float)processus_Calcule_Accelerometre_Struct.Wrong_Way_S_angle * (float)processus_Communication_Struct_WANTED_Value.Yaw, 127, -127, MIN_FLOAT_ACC, MAX_FLOAT_ACC) + processus_Calcule_Accelerometre_Struct.Roll;
    

    //je m'assure de ne pas depasser la val max ou min
    processus_Calcule_Accelerometre_Check_Under_Value_Cap(&DA_angle,&GA_angle,&DR_angle,&GR_angle,&H_angle, &S_angle);


 

    processus_Calcule_Accelerometre_Struct.Wanted_SERVO_DA_angle = (unsigned char)map_Float((float)processus_Calcule_Accelerometre_Struct.Wrong_Way_DA_angle * DA_angle, MIN_FLOAT_ACC, MAX_FLOAT_ACC, 0.0, 180.0);
    processus_Calcule_Accelerometre_Struct.Wanted_SERVO_GA_angle = (unsigned char)map_Float((float)processus_Calcule_Accelerometre_Struct.Wrong_Way_GA_angle * GA_angle, MIN_FLOAT_ACC, MAX_FLOAT_ACC, 0.0, 180.0);

    processus_Calcule_Accelerometre_Struct.Wanted_SERVO_DR_angle = (unsigned char)map_Float((float)processus_Calcule_Accelerometre_Struct.Wrong_Way_DR_angle * DR_angle, MIN_FLOAT_ACC, MAX_FLOAT_ACC, 0.0, 180.0);
    processus_Calcule_Accelerometre_Struct.Wanted_SERVO_GR_angle = (unsigned char)map_Float((float)processus_Calcule_Accelerometre_Struct.Wrong_Way_GR_angle * GR_angle, MIN_FLOAT_ACC, MAX_FLOAT_ACC, 0.0, 180.0);

    processus_Calcule_Accelerometre_Struct.Wanted_SERVO_H_angle =  (unsigned char)map_Float(H_angle, MIN_FLOAT_ACC, MAX_FLOAT_ACC, 0.0, 180.0);
    processus_Calcule_Accelerometre_Struct.Wanted_SERVO_S_angle =  (unsigned char)map_Float(S_angle, MIN_FLOAT_ACC, MAX_FLOAT_ACC, 0.0, 180.0);


    // Serial.print(processus_Calcule_Accelerometre_Struct.Wanted_SERVO_DA_angle);
    // Serial.print("/");
    // Serial.print(processus_Calcule_Accelerometre_Struct.Wanted_SERVO_GA_angle);//pas bon
    // Serial.print("/");
    // Serial.print(processus_Calcule_Accelerometre_Struct.Wanted_SERVO_DR_angle);
    // Serial.print("/");
    // Serial.print(processus_Calcule_Accelerometre_Struct.Wanted_SERVO_GR_angle);
    // Serial.print("/");
    // Serial.print(processus_Calcule_Accelerometre_Struct.Wanted_SERVO_H_angle);
    // Serial.print("/");
    // Serial.println(processus_Calcule_Accelerometre_Struct.Wanted_SERVO_S_angle);


}


void processus_Calcule_Accelerometre_Calcule_Orientation(sensors_event_t a,
    sensors_event_t g,
    sensors_event_t temp)
{
    processus_Calcule_Accelerometre_Struct.Orientation_Rho =  atan2f(a.acceleration.x, sqrt(pow(a.acceleration.y,2) + pow(a.acceleration.z,2)));
    processus_Calcule_Accelerometre_Struct.Orientation_Phi =  atan2f(a.acceleration.y, sqrt(pow(a.acceleration.x,2) + pow(a.acceleration.z,2)));
    //processus_Calcule_Accelerometre_Struct.Orientation_Teta = atan2f(sqrt(pow(a.acceleration.x,2) + pow(a.acceleration.y,2)), a.acceleration.z);
    
    float _yaw = processus_Calcule_Accelerometre_Struct.Orientation_Yaw;

    //yaw
    if(processus_Calcule_Accelerometre_Struct.Orientation_Yaw < 0)
    {
        _yaw = _yaw * -1;
    }

    while(_yaw > 2*3.14)
    {
        _yaw -= _yaw;
    }
    //_yaw = _yaw + 1.70;
    //yaw
    if(processus_Calcule_Accelerometre_Struct.Orientation_Yaw < 0)
    {
        processus_Communication_Struct_ACTUAL_Value.Yaw = (signed char)map_Float(2 * 3.14 - _yaw, 0, 2 * 3.14, MIN_ORIENTATION, MAX_ORIENTATION) ;
    }
    else
    {
        processus_Communication_Struct_ACTUAL_Value.Yaw = (signed char)map_Float(_yaw, 0, 2 * 3.14, MIN_ORIENTATION, MAX_ORIENTATION);
    }
    processus_Communication_Struct_ACTUAL_Value.Yaw = processus_Communication_Struct_ACTUAL_Value.Yaw + 67;

    if(a.acceleration.z < 0)
    {
        processus_Communication_Struct_ACTUAL_Value.Pitch =  (signed char)map_Float(-1*processus_Calcule_Accelerometre_Struct.Orientation_Rho, -(3.14/2), (3.14/2), MID_ORIENTATION, MAX_ORIENTATION);
        processus_Communication_Struct_ACTUAL_Value.Roll =  (signed char)map_Float(-1*processus_Calcule_Accelerometre_Struct.Orientation_Phi, -(3.14/2), (3.14/2), MID_ORIENTATION, MAX_ORIENTATION);
        //processus_Communication_Struct_ACTUAL_Value.Yaw = (signed char)map_Float(-1*processus_Calcule_Accelerometre_Struct.Orientation_Yaw, -(3.14/2), (3.14/2), MID_ORIENTATION, MAX_ORIENTATION) ;

        // Serial.print(processus_Communication_Struct_ACTUAL_Value.Pitch);
        // Serial.print("/");
        // Serial.print(processus_Communication_Struct_ACTUAL_Value.Roll);
        // Serial.print("/");
        // Serial.print(processus_Communication_Struct_ACTUAL_Value.Yaw);
        // Serial.println("\t/");
    }
    else
    {
        processus_Communication_Struct_ACTUAL_Value.Pitch =  (signed char)map_Float(processus_Calcule_Accelerometre_Struct.Orientation_Rho, -(3.14/2), (3.14/2), MIN_ORIENTATION, MID_ORIENTATION);
        processus_Communication_Struct_ACTUAL_Value.Roll =  (signed char)map_Float(processus_Calcule_Accelerometre_Struct.Orientation_Phi, -(3.14/2), (3.14/2), MIN_ORIENTATION, MID_ORIENTATION);
        //processus_Communication_Struct_ACTUAL_Value.Yaw = (signed char)map_Float(processus_Calcule_Accelerometre_Struct.Orientation_Yaw, -(3.14/2), (3.14/2), MIN_ORIENTATION, MID_ORIENTATION);

        // Serial.print(processus_Communication_Struct_ACTUAL_Value.Pitch);
        // Serial.print("/");
        // Serial.print(processus_Communication_Struct_ACTUAL_Value.Roll);
        // Serial.print("/");
        // Serial.print(processus_Communication_Struct_ACTUAL_Value.Yaw);
        // Serial.println("\t/");
    }
    //processus_Communication_Struct_ACTUAL_Value.Yaw = -60;


    // Serial.print(processus_Communication_Struct_ACTUAL_Value.Pitch);
    // Serial.print("/");
    // Serial.print(processus_Communication_Struct_ACTUAL_Value.Roll);//pas bon
    // Serial.print("/");
    // Serial.println(processus_Communication_Struct_ACTUAL_Value.Yaw);

}



void processus_Calcule_Accelerometre_Check_Under_Value_Cap(float *DA_angle,
float *GA_angle,
float *DR_angle,
float *GR_angle,
float *H_angle, 
float *S_angle)
{
    ////////////////////////// DA_angle
    if(*DA_angle > MAX_FLOAT_ACC)
    {
        *DA_angle = MAX_FLOAT_ACC;
    }
    if(*DA_angle < MIN_FLOAT_ACC)
    {
        *DA_angle = MIN_FLOAT_ACC;
    }

    ////////////////////////// GA_angle
    if(*GA_angle > MAX_FLOAT_ACC)
    {
        *GA_angle = MAX_FLOAT_ACC;
    }
    if(*GA_angle < MIN_FLOAT_ACC)
    {
        *GA_angle = MIN_FLOAT_ACC;
    } 

    ////////////////////////// DR_angle
    if(*DR_angle > MAX_FLOAT_ACC)
    {
        *DR_angle = MAX_FLOAT_ACC;
    }
    if(*DR_angle < MIN_FLOAT_ACC)
    {
        *DR_angle = MIN_FLOAT_ACC;
    } 

    ////////////////////////// GR_angle
    if(*GR_angle > MAX_FLOAT_ACC)
    {
        *GR_angle = MAX_FLOAT_ACC;
    }
    if(*GR_angle < MIN_FLOAT_ACC)
    {
        *GR_angle = MIN_FLOAT_ACC;
    } 

    ////////////////////////// H_angle
    if(*H_angle > MAX_FLOAT_ACC)
    {
        *H_angle = MAX_FLOAT_ACC;
    }
    if(*H_angle < MIN_FLOAT_ACC)
    {
        *H_angle = MIN_FLOAT_ACC;
    }  

    ////////////////////////// S_angle
    if(*S_angle > MAX_FLOAT_ACC)
    {
        *S_angle = MAX_FLOAT_ACC;
    }
    if(*S_angle < MIN_FLOAT_ACC)
    {
        *S_angle = MIN_FLOAT_ACC;
    }  
}



float map_Float(float x, float in_min, float in_max, float out_min, float out_max) 
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}