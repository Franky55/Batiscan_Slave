
#include "main.h"
#include "Pilote_ADC.h"
#include "interface_Niveau_Batterie.h"


void interface_Niveau_Batterie_Verification_Batterie(int valeur);

INTERFACE_Niveau_Batterie interface_Niveau_Batterie_Struct;


int interface_NIVEAUBATTERIE_Initialise()
{
    return 0;
}


/**
 * @brief La fonction met la valeur de la pression dans le parametre
 * 
 * @param valeur 
 * @return int 
 */
int interface_NIVEAUBATTERIE_Read(int *valeur)
{
    int val = pilote_ADC_AnalogRead(POWER_BAT);

    *valeur = val;
    interface_Niveau_Batterie_Struct.batterie = val;
    
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
        interface_Niveau_Batterie_Struct.niveau_Urgence = NIVEAU_URGENCE_MOYEN;
    }
}