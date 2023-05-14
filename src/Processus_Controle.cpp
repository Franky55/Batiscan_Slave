

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "main.h"
#include "Interface_Accelerometre.h"
#include "serviceBaseDeTemps.h"
#include "interface_PWM.h"

#include <stdio.h>
#include "Processus_Controle.h"

unsigned long compteur = 0;
unsigned long compteurPWM = 0;

int cycle = 0;
bool Sense11 = true;


int Processus_Controle_initialise(void)
{
  compteur = 0;
    serviceBaseDeTemps_execute[PROCESSUSCONTROLE_PHASE] = Print_Acc_Data;
    serviceBaseDeTemps_execute[PROCESSUSPWM_PHASE] = MoveServo;
  return 0;

}



void MoveServo()
{
  compteurPWM++;

  if (compteurPWM < 5)
  {
    return;
  }

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


    interface_Write_PWM(cycle);
}




void Print_Acc_Data()
{

    compteur++;
  if (compteur < 1000)
  {
    return;
  }

  compteur =0;

    sensors_event_t a, g, temp;

    Get_Sensor_Event(&a, &g, &temp);


    Serial.print("Acceleration X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");

  Serial.print("Rotation X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");

  Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.println(" degC");

  Serial.println("");

}