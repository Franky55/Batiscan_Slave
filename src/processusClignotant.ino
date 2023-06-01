//processusClignotant:
//Historique: 
// 2023-05-03, Camille Fortin

//INCLUSIONS
#include "Arduino.h"
#include "main.h"
#include "interface_GPIO.h"
#include "interface_NEOPIXEL.h"
#include "serviceBaseDeTemps.h"
#include "interface_PWM.h"

#include "processusClignotant.h"
#include <stdio.h>

//Definitions privees
#define PROCESSUSCLIGNOTANT_COMPTE_POUR_ALLUME (\
  PROCESSUSCLIGNOTANT_TEMPS_ALLUME_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /1000.0)

#define PROCESSUSCLIGNOTANT_COMPTE_POUR_ETEINDRE  (\
  PROCESSUSCLIGNOTANT_TEMPS_ETEINT_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /1000.0)

   
//Declarations de fonctions privees:
//pas de fonction privees

//Definitions de variables privees:
unsigned long processusClignotant_compteur;

//Definitions de fonctions privees:

void processusClignotant_attendAvantDEteindreLeTemoinLumineux();

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:
void processusClignotant_attendAvantDAllumerLeTemoinLumineux()
{
  processusClignotant_compteur++;
  
  if (processusClignotant_compteur < PROCESSUSCLIGNOTANT_COMPTE_POUR_ALLUME)
  {
    return;
  }
  // Test Code Go here

  
  interface_Analogue_Write(DRIVE_BALLAST, 255);
  interface_GPIO_Write(VALVE, OPEN_VALVE);


  // END test Code 
  interface_NEOPIXEL_allume(10, 10, 10);

  //interface_PWM_Struct.Drive_value = 110;
  //digitalWrite(SPI_CS1, HIGH);
  //Serial.println("ALLUME");
  processusClignotant_compteur = 0;
  serviceBaseDeTemps_execute[PROCESSUSCLIGNOTANT_PHASE] = processusClignotant_attendAvantDEteindreLeTemoinLumineux;
}

void processusClignotant_attendAvantDEteindreLeTemoinLumineux()
{ 
  processusClignotant_compteur++;
  if (processusClignotant_compteur < PROCESSUSCLIGNOTANT_COMPTE_POUR_ETEINDRE)
  {
    return;
  }

  
  // Test Code Go here

  interface_Analogue_Write(DRIVE_BALLAST, 0);
  interface_GPIO_Write(VALVE, CLOSE_VALVE);

  // END test Code 


  interface_NEOPIXEL_eteint();

  //interface_PWM_Struct.Drive_value = 92;
  //Serial.println("ETEINT");
  processusClignotant_compteur = 0;
  serviceBaseDeTemps_execute[PROCESSUSCLIGNOTANT_PHASE] = processusClignotant_attendAvantDAllumerLeTemoinLumineux;
}

void processusClignotant_initialise(void)
{
  processusClignotant_compteur = 0;
  //interface_NEOPIXEL_eteint();
  serviceBaseDeTemps_execute[PROCESSUSCLIGNOTANT_PHASE] = processusClignotant_attendAvantDAllumerLeTemoinLumineux;
}
