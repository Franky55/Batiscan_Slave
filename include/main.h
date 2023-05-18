/**
 * @file xmain.h
 * @author Francis Gratton 
 * 
 * @brief Le fichier xmain.h est nécessaire pour les includions global qui
 *   contien les defines essentiel au fonctionnement. Le processeur utilisé
 *  pour la gestion du véhicule est un ESP32-S3. Voir le document de projet
 *  pour plus d'information sur le fonctionnement.
 *      
 *  Le programme suivant fonctionne avec une base de temps et des machine d'état.
 * 
 *   
 * @version 0.0.1
 * @date 2023-05-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef MAIN_H
#define MAIN_H

//PROGRAMME: Batiscan
//DESCRIPTION: programme qui va permettre le bon fonctionnement d'un sous-marin

//HISTORIQUE:
/* Historique du programme gèrer par git et publier sur github au lien suivant
*
*       https://github.com/Franky55/Template
*/
  
//  *** INFORMATION PUBLIQUE ***


//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles:




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//                                                  WIFI

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#define WIFI_SSID "Batiscan"
#define WIFI_PASSWORD "BATISCAN"





#define GPIO10 10
#define GPIO10_TEMPS_POUR_RESET_EN_MS 5000


#define POWER_BAT 4
#define PRESSION 5
#define TEMPERATURE 6
#define INT 9
#define DRIVE_MOTEUR 15
#define DRIVE_BALLAST 16
#define DIRECTION_BALLAST 1
#define SERVO_X 17
#define SERVO_Y 18
#define SERVO_GA 21
#define SERVO_GR 35
#define SERVO_DA 36
#define SERVO_DR 37
#define SERVO_H 38
#define SERVO_S 39
#define EAU 40
#define LUMIERE_D 41
#define LUMIERE_G 42
#define VALVE 46
#define CONTROL_POWER_CAM 47






/***  DÉFINITION POUR LES SERVOS MOTEURS  ***/

//Les pins utilisés
#define SERVO1 39
#define SERVO_AXE_X 17



//Pin utilisé pour la communication I2C
#define I2C_SDA 8
#define I2C_SCL 7


//#define MISO 7
//#define MOSI 8
//#define CLK 6
//#define CS1 9

#define SPI_MISO 13
#define SPI_MOSI 11
#define SPI_CLK 12
#define INTERFACE_SPI_CS1 10
#define INTERFACE_SPI_CS2 14

#define SPI_BUFFER_SIZE 255

//Utlisation de la LED Neopixel
#define NEOPIXEL  45
#define NUMPIXELS 1 


/***  DÉFINITION NÉCESSAIRE À LA BASE DE TEMPS  ***/
/**
 * @brief Période en microsecondes à laquelle le TaskServer exécute sa fonction 
 *  qui fait apelle au service Base de temps pour gêrer plusieur tache a la fois
 * 
 */
#define SERVICETASKSERVER_PERIODE_EN_US (1000L)
/**
 * @brief Fréquence en Hz de la base de temps
 * 
 */
#define SERVICEBASEDETEMPS_FREQUENCE_EN_HZ 1000
/**
 * @brief Nombre de phase dans une période de la base de temps (1 si pas utilisé)
 */
#define SERVICEBASEDETEMPS_NOMBRE_DE_PHASES_DANS_LOOP 2



/**
 * @brief Phase pour la communication SPI
 * 
 */
#define INTERFACESPI_TRANSACTION 1
















/**
 * @brief Nombre de phase de la base de temps \ref xserviceBaseDeTemps.h
 * 
 */
#define SERVICEBASEDETEMPS_NOMBRE_DE_PHASES 5




/**
 * @brief Numéro de phase du processus clignotant
 */
#define PROCESSUSCLIGNOTANT_PHASE 0

/**
 * @brief Numéro de phase du processus Controle
 */
#define PROCESSUSCONTROLE_PHASE 1

/**
 * @brief Numéro de phase du processus PWM
 */
#define PROCESSUSPWM_PHASE 2


/**
 * @brief Phase pour la communication
 * 
 */
#define PROCESSUSCOMMUNICATION 3


/**
 * @brief Phase pour update les servos moteurs
 * 
 */
#define INTERFACE_UPDATE_PWM 4


#define INTERFACE_PWM_TEMPS_UPDATE_EN_MS 100

#define PROCESSUSCLIGNOTANT_TEMPS_ALLUME_EN_MS 5000
#define PROCESSUSCLIGNOTANT_TEMPS_ETEINT_EN_MS 5000


#endif