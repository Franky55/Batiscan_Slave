/**
 * @file piloteIOT1.ino
 * @author Francis Gratton
 * @brief Pilote qui contrôle la broche d'un microcontrôleur en utilisant
 *  la librairie Arduino. (digitalWrite et pinMode)
 * 
 * @version 0.1
 * @date 2022-11-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
//piloteIOT1:
//Historique: 
// 2021-04-07, Yves Roy, creation

//INCLUSIONS
#include <Arduino.h>
#include "main.h"
#include <Adafruit_NeoPixel.h>
#include "pilote_NEOPIXEL.h"

//Definitions privees
//pas de definitions privees

//Declarations de fonctions privees:
//pas de fonctions privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
//pas de variables publiques

//Definitions de fonctions publiques:




Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIXEL, NEO_GRB + NEO_KHZ800);


/**
 * @brief Fonciton qui met la LED NEOPIXEL par la pin \ref PIN_NEOPIXEL
 *   au niveau passé en paramètre: r, g, b
 * 
 * @param r 
 * @param g 
 * @param b 
 */
void pilote_NEOPIXEL_metA(int r, int g, int b)
{
  pixels.setPixelColor(0, pixels.Color(r, g, b));
  pixels.show();   // Send the updated pixel colors to the hardware.
}

void pilote_NEOPIXEL_Clear()
{
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();   // Send the updated pixel colors to the hardware.
}





/**
 * @brief Fonction d'initialisation de la broche \ref PIN_NEOPIXEL
 *  du mirocontrôleur. Met la broche du microcontrôleur en sortie et assigne
 *  sa valeur initial éteindu
 * 
 */
void pilote_NEOPIXEL_initialise(void)
{
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.setPixelColor(0, pixels.Color(10, 10, 10));
}
