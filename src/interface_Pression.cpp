
#include "main.h"
#include "Pilote_ADC.h"
#include "interface_Pression.h"


INTERFACE_Pression interface_Pression_Struct;





int interface_PRESSION_Initialise()
{
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

    interface_Pression_Struct.tab_Moyenne_Pression[GROSSEUR_TAB_MOYENNE - 1] = val;


    int moyenne = 0;

    for(int i = 0; i < GROSSEUR_TAB_MOYENNE; i++)
    {
        moyenne += interface_Pression_Struct.tab_Moyenne_Pression[i];
    }

    moyenne = moyenne / GROSSEUR_TAB_MOYENNE;



    *valeur = moyenne;
    interface_Pression_Struct.pression = moyenne;

    switch(interface_Pression_Struct.unite)
    {
        case 0:

        // interface_Pression_Struct = 
        // *valeur = 
        break;

        case 1:
        break;

        case 2:
        break;
    }



    
    return moyenne;
}