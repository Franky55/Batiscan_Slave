
#ifndef INTERFACETEMPERATURE_H
#define INTERFACETEMPERATURE_H


typedef struct 
{
    unsigned char niveau_Urgence;
    unsigned char unite;
    int tab_Moyenne_Temperature[GROSSEUR_TAB_MOYENNE];
    unsigned char temperature;
}INTERFACE_Temperature;

int interface_TEMPERATURE_Initialise();
int interface_TEMPERATURE_Read(unsigned char *valeur);


extern INTERFACE_Temperature interface_Temperature_Struct;


#endif