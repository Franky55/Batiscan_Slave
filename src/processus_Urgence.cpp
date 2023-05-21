
#include <Arduino.h>
#include "main.h"
#include "serviceBaseDeTemps.h"
#include "interface_Temperature.h"
#include "interface_CapteurEau.h"
#include "interface_Pression.h"
#include "interface_Niveau_Batterie.h"
#include <stdio.h>
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
    bool val2;
    //interface_PRESSION_Read(&val);
    //interface_TEMPERATURE_Read(&val);
    interface_CAPTEUREAU_Read(&val2);

    Serial.print("EAU: ");
    Serial.print(val2);
    Serial.print("\n");
    
}


