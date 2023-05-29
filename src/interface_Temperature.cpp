

#include "main.h"
#include "Pilote_ADC.h"
#include "interface_Temperature.h"

INTERFACE_Temperature interface_Temperature_Struct;

#define OFFSET -408

void interface_TEMPERATURE_Verification_TEMPERATURE(int valeur);


int interface_TEMPERATURE_Initialise()
{
    interface_Temperature_Struct.niveau_Urgence = NIVEAU_URGENCE_0;
    for(int i = 0; i < GROSSEUR_TAB_MOYENNE; i++)
    {
        interface_Temperature_Struct.tab_Moyenne_Temperature[i] = 25;
    }
    return 0;
}

/**
 * @brief La fonction lit la temperature et met la valeur de la temperature dans le parametre
 * 
 * @param valeur 
 * @return int 
 */
int interface_TEMPERATURE_Read(unsigned char *valeur)
{
    int val = pilote_ADC_AnalogRead(TEMPERATURE);


    for(int i = 0; i < GROSSEUR_TAB_MOYENNE -1; i++)
    {
        interface_Temperature_Struct.tab_Moyenne_Temperature[i] = interface_Temperature_Struct.tab_Moyenne_Temperature[i + 1];
    }

    interface_Temperature_Struct.tab_Moyenne_Temperature[GROSSEUR_TAB_MOYENNE - 1] = val;


    long moyenne = 0;

    for(int i = 0; i < GROSSEUR_TAB_MOYENNE; i++)
    {
        moyenne += (long)interface_Temperature_Struct.tab_Moyenne_Temperature[i];
    }

    moyenne = moyenne / GROSSEUR_TAB_MOYENNE;

    moyenne = (moyenne - 2100 + OFFSET)/-10.76;

    *valeur = (unsigned char)moyenne;
    interface_Temperature_Struct.temperature = (unsigned char)moyenne;

    interface_TEMPERATURE_Verification_TEMPERATURE((int)moyenne);


    return moyenne;
}


/**
 * @brief La fonction determine le niveau d'urgence
 * 
 * @param valeur 
 */
void interface_TEMPERATURE_Verification_TEMPERATURE(int valeur)
{
    if(valeur < TEMPERATURE_MIN)
    {
        interface_Temperature_Struct.niveau_Urgence = NIVEAU_URGENCE_URGENT;
    }
    else if(valeur >= TEMPERATURE_MAX)
    {
        interface_Temperature_Struct.niveau_Urgence = NIVEAU_URGENCE_URGENT;
    }
    else if(valeur >= TEMPERATURE_ELEVEE)
    {
        interface_Temperature_Struct.niveau_Urgence = NIVEAU_URGENCE_MOYEN;
    }
    else
    {
        interface_Temperature_Struct.niveau_Urgence = NIVEAU_URGENCE_0;
    }
}