#ifndef PROCESSUSCALCULEACCELEROMETRE_H
#define PROCESSUSCALCULEACCELEROMETRE_H

typedef struct
{
    unsigned char State;
    float Yaw;
    float Pitch;
    float Roll;

    float Orientation_Yaw;
    float Orientation_Pitch;
    float Orientation_Roll;

    unsigned char Wanted_SERVO_GA_angle;
    unsigned char Wanted_SERVO_GR_angle;
    unsigned char Wanted_SERVO_DA_angle;
    unsigned char Wanted_SERVO_DR_angle;
    unsigned char Wanted_SERVO_H_angle;
    unsigned char Wanted_SERVO_S_angle;

    float Wrong_Way_GA_angle;
    float Wrong_Way_GR_angle;
    float Wrong_Way_DA_angle;
    float Wrong_Way_DR_angle;
    float Wrong_Way_H_angle;
    float Wrong_Way_S_angle;

}PROCESSUS_CALCULEACCELEROMETRE;




int processus_Calcule_Accelerometre_initialise();


extern PROCESSUS_CALCULEACCELEROMETRE processus_Calcule_Accelerometre_Struct;
#endif