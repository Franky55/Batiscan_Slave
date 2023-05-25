
#include <Arduino.h>
#include "main.h"
#include "pilote_PWM.h"
#include "interface_PWM.h"
#include "serviceBaseDeTemps.h"


#define INTERFACE_PWM_TEMPS_UPDATE (\
  INTERFACE_PWM_TEMPS_UPDATE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /1000.0)


INTERFACE_PWM interface_PWM_Struct;

int interface_PWM_compteur = 0;

void interface_PWM_Update_Avant();
void interface_PWM_Update_Arriere();
void interface_PWM_Update_Cam();
void interface_PWM_Update_Ya();
void interface_PWM_Update_Moteur();


int interface_PWM_Initialise()
{
    serviceBaseDeTemps_execute[INTERFACE_UPDATE_PWM] = interface_PWM_Update_Moteur;
    
    return 0;
}

void interface_PWM_Update_Moteur()
{
    interface_PWM_compteur++;
    if (interface_PWM_compteur < INTERFACE_PWM_TEMPS_UPDATE)
    {
        return;
    }
    interface_PWM_compteur = 0;
 

    write_PWM(DRIVE_MOTEUR, interface_PWM_Struct.Drive_value);
    analogWrite(DRIVE_BALLAST, interface_PWM_Struct.Ballast_value);

    serviceBaseDeTemps_execute[INTERFACE_UPDATE_PWM] = interface_PWM_Update_Avant;
}


void interface_PWM_Update_Avant()
{
    interface_PWM_compteur++;
    if (interface_PWM_compteur < INTERFACE_PWM_TEMPS_UPDATE)
    {
        return;
    }
    interface_PWM_compteur = 0;

    write_PWM(SERVO_GA, interface_PWM_Struct.SERVO_GA_angle);
    write_PWM(SERVO_DA, interface_PWM_Struct.SERVO_DA_angle);
        
        

    serviceBaseDeTemps_execute[INTERFACE_UPDATE_PWM] = interface_PWM_Update_Arriere;
}

void interface_PWM_Update_Arriere()
{
    interface_PWM_compteur++;
    if (interface_PWM_compteur < INTERFACE_PWM_TEMPS_UPDATE)
    {
        return;
    }
    interface_PWM_compteur = 0;

    write_PWM(SERVO_GR, interface_PWM_Struct.SERVO_GR_angle);
    write_PWM(SERVO_DR, interface_PWM_Struct.SERVO_DR_angle);

    serviceBaseDeTemps_execute[INTERFACE_UPDATE_PWM] = interface_PWM_Update_Cam;
}


void interface_PWM_Update_Cam()
{
    // if(CamOFF)
    // {
    //     serviceBaseDeTemps_execute[INTERFACE_UPDATE_PWM] = interface_PWM_Update_Ya;
    //     return;
    // }

    interface_PWM_compteur++;
    if (interface_PWM_compteur < INTERFACE_PWM_TEMPS_UPDATE)
    {
        return;
    }
    interface_PWM_compteur = 0;

    write_PWM(SERVO_H,  interface_PWM_Struct.SERVO_H_angle);
    write_PWM(SERVO_S,  interface_PWM_Struct.SERVO_S_angle);

    serviceBaseDeTemps_execute[INTERFACE_UPDATE_PWM] = interface_PWM_Update_Ya;
}


void interface_PWM_Update_Ya()
{
    interface_PWM_compteur++;
    if (interface_PWM_compteur < INTERFACE_PWM_TEMPS_UPDATE)
    {
        return;
    }
    interface_PWM_compteur = 0;

    write_PWM(SERVO_H,  interface_PWM_Struct.SERVO_H_angle);
    write_PWM(SERVO_S,  interface_PWM_Struct.SERVO_S_angle);

    serviceBaseDeTemps_execute[INTERFACE_UPDATE_PWM] = interface_PWM_Update_Moteur;
}






void interface_PWM_Write(int servoPin, int value)
{
    switch (servoPin)
    {
    case SERVO_X:
        interface_PWM_Struct.SERVO_X_angle = value;
    break;
    case SERVO_GA:
        interface_PWM_Struct.SERVO_GA_angle = value;
    break;
    case SERVO_GR:
        interface_PWM_Struct.SERVO_GR_angle = value;
    break;
    case SERVO_DA:
        interface_PWM_Struct.SERVO_DA_angle = value;
    break;
    case SERVO_DR:
        interface_PWM_Struct.SERVO_DR_angle = value;
    break;
    case SERVO_H:
        interface_PWM_Struct.SERVO_H_angle = value;
    break;
    case SERVO_S:
        interface_PWM_Struct.SERVO_S_angle = value;
    break;
    case DRIVE_BALLAST:
        interface_PWM_Struct.Ballast_value = value;
    break;
    case DRIVE_MOTEUR:
        interface_PWM_Struct.Drive_value = value;
    break;
    }

    write_PWM(servoPin, value);
}

void interface_Analogue_Write(int servoPin, int value)
{

    switch (servoPin)
    {
    case SERVO_X:
        interface_PWM_Struct.SERVO_X_angle = value;
    break;
    case SERVO_GA:
        interface_PWM_Struct.SERVO_GA_angle = value;
    break;
    case SERVO_GR:
        interface_PWM_Struct.SERVO_GR_angle = value;
    break;
    case SERVO_DA:
        interface_PWM_Struct.SERVO_DA_angle = value;
    break;
    case SERVO_DR:
        interface_PWM_Struct.SERVO_DR_angle = value;
    break;
    case SERVO_H:
        interface_PWM_Struct.SERVO_H_angle = value;
    break;
    case SERVO_S:
        interface_PWM_Struct.SERVO_S_angle = value;
    break;
    case DRIVE_BALLAST:
        interface_PWM_Struct.Ballast_value = value;
    break;
    case DRIVE_MOTEUR:
        interface_PWM_Struct.Drive_value = value;
    break;
    }

    analogWrite(servoPin, value);
}
