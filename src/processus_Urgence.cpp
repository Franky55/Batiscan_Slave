
#include <Arduino.h>
#include "main.h"
#include "serviceBaseDeTemps.h"
#include "interface_Temperature.h"
#include "interface_CapteurEau.h"
#include "interface_Pression.h"
#include "interface_Niveau_Batterie.h"
#include "interface_NEOPIXEL.h"
#include <stdio.h>
#include "Processus_Communication.h"
#include "Processus_Ballast.h"
#include "processus_Urgence.h"


#define PROCESSUSURGENCE_LECTURE_UPDATE  (\
  PROCESSUSURGENCE_LECTURE_UPDATE_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /1000.0)


void processus_Urgence_Lecture_Capteur();
void Check_Emergencies();



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
    processus_Communication_Struct_ACTUAL_Value.Pressure = interface_Pression_Struct.pression;

    

    interface_TEMPERATURE_Read(&ucVal);
    processus_Communication_Struct_ACTUAL_Value.Temperature = (signed char)interface_Temperature_Struct.temperature;

    // Serial.print("TEMPERATURE: ");
    // Serial.print(ucVal);
    // Serial.print("\n");

    interface_CAPTEUREAU_Read(&val2);
    processus_Communication_Struct_ACTUAL_Value.union_Bool.bits.Water_Detection = !interface_Niveau_eau.eau;

    interface_NIVEAUBATTERIE_Read(&val);
    processus_Communication_Struct_ACTUAL_Value.Battery = interface_Niveau_Batterie_Struct.batterie;

    serviceBaseDeTemps_execute[PROCESSUS_URGENCE_PHASE] = Check_Emergencies;
    
}


void Check_Emergencies()
{
    if(interface_Pression_Struct.niveau_Urgence == 4)
    {
        Serial.println("PRESSION URGENT");
        processus_Communication_Struct_ACTUAL_Value.union_Bool.bits.In_Emergency = 1;
        
    }
    else
    if(interface_Temperature_Struct.niveau_Urgence == 4)
    {
        Serial.println("TEMPERATURE URGENT");
        processus_Communication_Struct_ACTUAL_Value.union_Bool.bits.In_Emergency = 1;
        
    }
    else
    if(interface_Niveau_eau.niveau_Urgence == 4)
    {
        Serial.println("WATER URGENT");
        processus_Communication_Struct_ACTUAL_Value.union_Bool.bits.In_Emergency = 1;
        
    }
    else
    if(interface_Niveau_Batterie_Struct.niveau_Urgence == 4)
    {
        Serial.println("BATTERIE URGENT");
        processus_Communication_Struct_ACTUAL_Value.union_Bool.bits.In_Emergency = 1;
        
    }
    else
    {
        processus_Communication_Struct_ACTUAL_Value.union_Bool.bits.In_Emergency = 0;
    }
    


    if(interface_Niveau_Batterie_Struct.niveau_Urgence == 3)
    {
        processus_Communication_Struct_ACTUAL_Value.union_Bool.bits.Low_Battery = 1;
    }
    

    if(processus_Communication_Struct_ACTUAL_Value.union_Bool.bits.In_Emergency == 1)
    {
        processus_Ballast_Struct.state = STATE_BALLAST_EMPTY_OUT;
        interface_NEOPIXEL_allume(50, 0, 0);
    }
    


    serviceBaseDeTemps_execute[PROCESSUS_URGENCE_PHASE] = processus_Urgence_Lecture_Capteur;
}


