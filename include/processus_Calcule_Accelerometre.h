#ifndef PROCESSUSCALCULEACCELEROMETRE_H
#define PROCESSUSCALCULEACCELEROMETRE_H

typedef struct
{
    unsigned char State;
    float Yaw;
    float Pitch;
    float Roll;

    unsigned char Wanted_SERVO_GA_angle;
    unsigned char Wanted_SERVO_GR_angle;
    unsigned char Wanted_SERVO_DA_angle;
    unsigned char Wanted_SERVO_DR_angle;
    unsigned char Wanted_SERVO_H_angle;
    unsigned char Wanted_SERVO_S_angle;

}PROCESSUS_CALCULEACCELEROMETRE;




int processus_Calcule_Accelerometre_initialise();


extern PROCESSUS_CALCULEACCELEROMETRE processus_Calcule_Accelerometre_Struct;
#endif