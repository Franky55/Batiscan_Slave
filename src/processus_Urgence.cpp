
#include <Arduino.h>
#include "main.h"
#include "serviceBaseDeTemps.h"
#include "interface_Temperature.h"
#include "interface_CapteurEau.h"
#include "interface_Pression.h"
#include "interface_Niveau_Batterie.h"
#include <stdio.h>
#include "Processus_Communication.h"
#include "processus_Urgence.h"


#define PROCESSUSURGENCE_LECTURE_UPDATE  (\
  PROCESSUSURGENCE_LECTURE_UPDATE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /1000.0)


void processus_Urgence_Lecture_Capteur();




PROCESSUS_Urgence processus_Urgence_struct;

int compteur_Update = 0;

int Processus_Urgence_initialise()
{
    compteur_Update = 0;
    serviceBaseDeTemps_execute[PROCESSUS_URGENCE_PHASE] = processus_Urgence_Lecture_Capteur;
    return 0;
}


void processus_Urgence_Lecture_Capteur()
{
    compteur_Update++;

    if(compteur_Update < PROCESSUSURGENCE_LECTURE_UPDATE)
    {
        return;
    }
    
    compteur_Update = 0;

    int val = 0;
    unsigned char ucVal = 0;
    bool val2;
    interface_PRESSION_Read(&val);


    interface_TEMPERATURE_Read(&ucVal);
    processus_Communication_Struct_ACTUAL_Value.Temperature = (signed char)interface_Temperature_Struct.temperature;

    interface_CAPTEUREAU_Read(&val2);
    processus_Communication_Struct_ACTUAL_Value.union_Bool.bits.Water_Detection= interface_Niveau_eau.eau;

    interface_NIVEAUBATTERIE_Read(&val);
    processus_Communication_Struct_ACTUAL_Value.Battery = interface_Niveau_Batterie_Struct.batterie;
    
    
    // Serial.print("EAU: ");
    // Serial.print(val2);
    // Serial.print("\n");
    
}


