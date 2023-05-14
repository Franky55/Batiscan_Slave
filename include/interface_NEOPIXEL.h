/**
 * @file xinterfaceT1.h
 * @author Francis Gratton
 * @brief pour s'interfacer avec le neopixel. 
 * @version 0.1
 * @date 2023-05-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef INTERFACENEOPIXEL_H
#define INTERFACENEOPIXEL_H

//MODULE: interface_NEOPIXEL
//DESCRIPTION: pour s'interfacer avec le neopixel. 

//HISTORIQUE:


//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de requis

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dependances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
void interface_NEOPIXEL_allume(int r, int g, int b);
void interface_NEOPIXEL_eteint(void);
void interface_NEOPIXEL_initialise(void);

//Variables publiques:
//pas de variables publiques

#endif
