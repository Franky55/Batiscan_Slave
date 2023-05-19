

#include "main.h"
#include "Pilote_ADC.h"
#include "interface_Temperature.h"

INTERFACE_Temperature interface_Temperature_Struct;

#define OFFSET -408

int interface_TEMPERATURE_Initialise()
{
    return 0;
}

/**
 * @brief La fonction met la valeur de la temperature dans le parametre
 * 
 * @param valeur 
 * @return int 
 */
int interface_TEMPERATURE_Read(int *valeur)
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

    *valeur = (int)moyenne;
    interface_Temperature_Struct.temperature = (int)moyenne;


    switch(interface_Temperature_Struct.unite)
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
