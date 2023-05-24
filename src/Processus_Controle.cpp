

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "main.h"
#include "Interface_Accelerometre.h"
#include "serviceBaseDeTemps.h"
#include "interface_PWM.h"

#include <stdio.h>
#include "Processus_Controle.h"
#include "processus_Calcule_Accelerometre.h"

unsigned long compteur = 0;
unsigned long compteurPWM = 0;

int cycle = 0;
bool Sense11 = true;

void Processus_Controle_Adjuste_Servo();

int Processus_Controle_initialise(void)
{
  compteur = 0;
    serviceBaseDeTemps_execute[PROCESSUSCONTROLE_PHASE] = Processus_Controle_Adjuste_Servo;
    //serviceBaseDeTemps_execute[PROCESSUSPWM_PHASE] = MoveServo;
  return 0;

}

void Processus_Controle_Adjuste_Servo()
{
  interface_PWM_Struct.SERVO_GA_angle = (unsigned char)processus_Calcule_Accelerometre_Struct.Wanted_SERVO_GA_angle;
  interface_PWM_Struct.SERVO_GR_angle = (unsigned char)processus_Calcule_Accelerometre_Struct.Wanted_SERVO_GR_angle;
  interface_PWM_Struct.SERVO_DA_angle = (unsigned char)processus_Calcule_Accelerometre_Struct.Wanted_SERVO_DA_angle;
  interface_PWM_Struct.SERVO_DR_angle = (unsigned char)processus_Calcule_Accelerometre_Struct.Wanted_SERVO_DR_angle;
  interface_PWM_Struct.SERVO_H_angle =  (unsigned char)processus_Calcule_Accelerometre_Struct.Wanted_SERVO_H_angle;
  interface_PWM_Struct.SERVO_S_angle =  (unsigned char)processus_Calcule_Accelerometre_Struct.Wanted_SERVO_S_angle;
}



void MoveServo()
{
  compteurPWM++;

  

  compteurPWM =0;

  if(Sense11 == true)
    {
      cycle = cycle + 1;
      if(cycle >= 180)
      {
        Sense11 = false;
      }
    }
    else
    {
      cycle = cycle - 1;
      if(cycle <= 0)
      {
        Sense11 = true;
      }
    }


    interface_PWM_Struct.SERVO_DA_angle = cycle;
    interface_PWM_Struct.SERVO_DR_angle = cycle;
    interface_PWM_Struct.SERVO_GA_angle = cycle;
    interface_PWM_Struct.SERVO_GR_angle = cycle;
    interface_PWM_Struct.SERVO_H_angle = cycle;
    interface_PWM_Struct.SERVO_S_angle = cycle;
    interface_PWM_Struct.SERVO_X_angle = cycle;
}




