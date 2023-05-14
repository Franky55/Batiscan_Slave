/**
 * @file interfaceT1.ino
 * @author Francis Gratton
 * @brief Interface qui contrôle la del su Board Adafruit ESP32 feather
 * @version 0.1
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//INCLUSIONS
#include "main.h"
#include "pilote_NEOPIXEL.h"
#include "interface_NEOPIXEL.h"

//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:
//pas de fonction privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
//pas de variables publiques
int i=0;
bool Sense = true;

//Definitions de fonctions publiques:
void interface_NEOPIXEL_allume(int r, int g, int b)
{
  pilote_NEOPIXEL_metA(r, g, b);
}



void interface_NEOPIXEL_eteint(void)
{
  pilote_NEOPIXEL_Clear();
}

void interface_NEOPIXEL_initialise(void)
{
  
}
