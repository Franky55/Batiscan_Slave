
#include "main.h"
#include "Pilote_ADC.h"
#include "interface_Niveau_Batterie.h"


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

    return 0;
}