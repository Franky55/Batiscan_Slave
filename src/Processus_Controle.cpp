

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "main.h"
#include "Interface_Accelerometre.h"
#include "serviceBaseDeTemps.h"
#include "interface_PWM.h"
#include "interface_GPIO.h"

#include <stdio.h>
#include "Processus_Controle.h"
#include "Processus_Communication.h"
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

  interface_PWM_Struct.SERVO_X_angle = (unsigned char)processus_Communication_Struct_WANTED_Value.Camera_Servo_Angle;

  interface_PWM_Struct.Drive_value = (unsigned char)map((long)processus_Communication_Struct_WANTED_Value.Speed, -127, 127, 52, 132);

  interface_GPIO_Struct.Control_Cam = processus_Communication_Struct_WANTED_Value.union_Bool.bits.Camera_State;
  interface_GPIO_Struct.Lumiere_D = processus_Communication_Struct_WANTED_Value.union_Bool.bits.Right_Light_State;
  interface_GPIO_Struct.Lumiere_G = processus_Communication_Struct_WANTED_Value.union_Bool.bits.Left_Light_State;


  //update Wanted
  processus_Communication_Struct_ACTUAL_Value.union_Bool.bits.Left_Light_State = interface_GPIO_Struct.Lumiere_G;
  processus_Communication_Struct_ACTUAL_Value.union_Bool.bits.Right_Light_State = interface_GPIO_Struct.Lumiere_D;
  processus_Communication_Struct_ACTUAL_Value.union_Bool.bits.Camera_State = interface_GPIO_Struct.Control_Cam;

  processus_Communication_Struct_ACTUAL_Value.Speed = (signed char)map((long)interface_PWM_Struct.Drive_value, 52, 132, -127, 127);

  // Serial.print("Speed: ");
  // Serial.println(interface_PWM_Struct.Drive_Value_SlowChange);

}




