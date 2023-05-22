
#ifndef INTERFACEPWM_H
#define INTERFACEPWM_H


typedef struct
{
    unsigned char SERVO_X_angle;

    unsigned char SERVO_GA_angle;
    unsigned char SERVO_GR_angle;
    unsigned char SERVO_DA_angle;
    unsigned char SERVO_DR_angle;
    unsigned char SERVO_H_angle;
    unsigned char SERVO_S_angle;

    unsigned char Drive_value;
    unsigned char Ballast_value;
}INTERFACE_PWM;


int interface_PWM_Initialise();
void interface_PWM_Write(int servoPin, int value);
void interface_Analogue_Write(int servoPin, int value);


extern INTERFACE_PWM interface_PWM_Struct;

#endif