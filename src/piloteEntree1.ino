/**
 * @file piloteEntree1.ino
 * @author Francis Gratton
 * @brief Pilote qui permet la lecture d'une broche d'un microcontrôleur 
 * 
 * @version 0.1
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//INCLUSIONS
#include <Arduino.h>
#include "main.h"
#include "piloteEntree1.h"

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

/// @brief Fonction qui permet de savoir l'état logique d'une BROCHE d'un micocontrôleur
/// @param Aucun \ref PILOTEENTREE1_BROCHE est une définition dans \ref xmain.h  
/// @return Valeur de la PIN de 1 ou 0 sur un unsigned char  
unsigned char piloteEntree1_lit(void)
{
  //return digitalRead(PILOTEENTREE1_BROCHE);
  return 0;
}
/// @brief Foncion qui initialise la lecture de la Broche du microcontrôleur
/// @param Aucun \ref PILOTEENTREE1_BROCHE est une définition dans \ref xmain.h  
void piloteEntree1_initialise(void)
{

}
