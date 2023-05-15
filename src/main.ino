//#############################################################################
/**
 * @file main.c
 * @author Francis Gratton
 * @brief
 * Program file containing the code defined in xmain.h
 * Please refer to this other file for information necessary in order to make this work.
 * @version 0.1
 * @date 2023-05-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
//#############################################################################


//INCLUSIONS
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_NeoPixel.h>
#include "main.h"

#include "PWM_Control.h"

// inlcude des pilotes

#include "piloteEntree1.h"
#include "pilote_NEOPIXEL.h"
#include "Pilote_I2C.h"
#include "pilote_PWM.h"
#include "pilote_GPIO.h"
//#include "pilote_SPI.h"


// Include des Services
#include "serviceTaskServer.h"
#include "serviceBaseDeTemps.h"

// Inlude des interfaces
#include "interfaceEntree1.h"
#include "interface_NEOPIXEL.h"
#include "Interface_Accelerometre.h"
#include "interface_PWM.h"
#include "interface_SPI_Slave.h"
#include "interface_GPIO.h"

// Include des processus
#include "processusClignotant.h"
#include "Processus_Controle.h"
#include "Processus_Communication.h"

//Definitions privees
//pas de definitions privees
//#include <Adafruit_NeoPixel.h>




/// @brief Fonction qui fait l'initialisation de tout les modules permettant
//   au fonctionnement global du véhicule.
/// @param void
void main_initialise(void);

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:

void main_initialise(void)
{
  serviceTaskServer_initialise();
  serviceBaseDeTemps_initialise();

  piloteEntree1_initialise();
  pilote_NEOPIXEL_initialise(); 
  pilote_I2C_Initialise();
  pilote_PWM_Initialise();
  pilote_GPIO_Initialise();

  //interfaceEntree1_initialise();
  interface_NEOPIXEL_initialise();
  interface_Accelerometre_initialise();
  interface_PWM_Initialise();
  interface_GPIO_Initialise();
  interface_SPI_SLAVE_initialise();

  processusClignotant_initialise();
  Processus_Controle_initialise();
  Processus_Communication_initialise();
}

void setup(void) 
{
  Serial.begin(115200);
  main_initialise();
  

  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif
  // END of Trinket-specific code.

  

  serviceTaskServer_DemarreLesTachesALaTouteFinDeSetup();
}

void loop(void) 
{
  serviceTaskServer_gestion.execute();
  serviceBaseDeTemps_gereDansLoop();   
}

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:
//pas de fonctions publiques
