
#ifndef INTERFACETEMPERATURE_H
#define INTERFACETEMPERATURE_H


typedef struct 
{
    unsigned char unite;
    int tab_Moyenne_Temperature[GROSSEUR_TAB_MOYENNE];
    int temperature;
}INTERFACE_Temperature;

int interface_TEMPERATURE_Initialise();
int interface_TEMPERATURE_Read(int *valeur);


extern INTERFACE_Temperature interface_Temperature_Struct;


#endif