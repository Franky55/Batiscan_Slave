
#include "main.h"
#include "Pilote_ADC.h"
#include "interface_Pression.h"

#define PRESSION_OFFSET 50

void interface_PRESSION_Verification_Pression(int valeur);


INTERFACE_Pression interface_Pression_Struct;





int interface_PRESSION_Initialise()
{
    interface_Pression_Struct.niveau_Urgence = NIVEAU_URGENCE_0;
    for(int i = 0; i < GROSSEUR_TAB_MOYENNE; i++)
    {
        interface_Pression_Struct.tab_Moyenne_Pression[i] = 331;
    }
    return 0;
}


/**
 * @brief La fonction met la valeur de la pression dans le parametre
 * 
 * @param valeur 
 * @return int 
 */
int interface_PRESSION_Read(int *valeur)
{
    int val = pilote_ADC_AnalogRead(PRESSION);

    for(int i = 0; i < GROSSEUR_TAB_MOYENNE -1; i++)
    {
        interface_Pression_Struct.tab_Moyenne_Pression[i] = interface_Pression_Struct.tab_Moyenne_Pression[i + 1];
    }
    //pascal e2
    interface_Pression_Struct.tab_Moyenne_Pression[GROSSEUR_TAB_MOYENNE - 1] = 8000 * (val + PRESSION_OFFSET) / 2993;


    int moyenne = 0;

    for(int i = 0; i < GROSSEUR_TAB_MOYENNE; i++)
    {
        moyenne += interface_Pression_Struct.tab_Moyenne_Pression[i];
    }

    moyenne = moyenne / GROSSEUR_TAB_MOYENNE;



    *valeur = moyenne;
    interface_Pression_Struct.pression = moyenne;

    interface_PRESSION_Verification_Pression(moyenne);

    return moyenne;
}


/**
 * @brief La fonction determine le niveau d'urgence
 * 
 * @param valeur 
 */
void interface_PRESSION_Verification_Pression(int valeur)
{

    if(valeur > PRESSION_MAX)
    {
        interface_Pression_Struct.niveau_Urgence = NIVEAU_URGENCE_URGENT;
    }
    else if(valeur < PRESSION_MIN)
    {
        interface_Pression_Struct.niveau_Urgence = NIVEAU_URGENCE_URGENT;
    }
    else
    {
        interface_Pression_Struct.niveau_Urgence = NIVEAU_URGENCE_0;
    }
}