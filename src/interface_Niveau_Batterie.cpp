
#include "main.h"
#include "Pilote_ADC.h"
#include "interface_Niveau_Batterie.h"

#define MAX_VALUE_BAT 3207

void interface_Niveau_Batterie_Verification_Batterie(int valeur);

INTERFACE_Niveau_Batterie interface_Niveau_Batterie_Struct;


int interface_NIVEAUBATTERIE_Initialise()
{
    interface_Niveau_Batterie_Struct.niveau_Urgence = NIVEAU_URGENCE_0;
    for(int i = 0; i < GROSSEUR_TAB_MOYENNE; i++)
    {
        interface_Niveau_Batterie_Struct.tab_Moyenne_batterie_Pourcentage[i] = 100;
    }

    return 0;
}


/**
 * @brief La fonction met la valeur de la batterie dans le parametre
 * 
 * @param valeur 
 * @return int 
 */
int interface_NIVEAUBATTERIE_Read(int *valeur)
{
    int val = pilote_ADC_AnalogRead(POWER_BAT);


    for(int i = 0; i < GROSSEUR_TAB_MOYENNE -1; i++)
    {
        interface_Niveau_Batterie_Struct.tab_Moyenne_batterie_Pourcentage[i] = interface_Niveau_Batterie_Struct.tab_Moyenne_batterie_Pourcentage[i + 1];
    }

    //Il faut dire le ratio pour le pourcentage


    interface_Niveau_Batterie_Struct.tab_Moyenne_batterie_Pourcentage[GROSSEUR_TAB_MOYENNE - 1] = 100 * (val-2290) / (MAX_VALUE_BAT-2290);


    int moyenne = 0;

    for(int i = 0; i < GROSSEUR_TAB_MOYENNE; i++)
    {
        moyenne += interface_Niveau_Batterie_Struct.tab_Moyenne_batterie_Pourcentage[i];
    }

    moyenne = moyenne / GROSSEUR_TAB_MOYENNE;


    *valeur = moyenne;
    interface_Niveau_Batterie_Struct.batterie = moyenne;
    
    interface_Niveau_Batterie_Verification_Batterie(val);

    return 0;
}




/**
 * @brief La fonction determine le niveau d'urgence
 * 
 * @param valeur 
 */
void interface_Niveau_Batterie_Verification_Batterie(int valeur)
{
    if(valeur > POWER_BAT_MAX)
    {
        interface_Niveau_Batterie_Struct.niveau_Urgence = NIVEAU_URGENCE_URGENT;
    }
    else if(valeur < POWER_BAT_MIN)
    {
        interface_Niveau_Batterie_Struct.niveau_Urgence = NIVEAU_URGENCE_URGENT;
    }
    else if(valeur >= POWER_BAT_MOY)
    {
        interface_Niveau_Batterie_Struct.niveau_Urgence = NIVEAU_URGENCE_0;
    }
    else if(valeur < POWER_BAT_MOY)
    {
        interface_Niveau_Batterie_Struct.niveau_Urgence = NIVEAU_URGENCE_HAUT;
    }
}