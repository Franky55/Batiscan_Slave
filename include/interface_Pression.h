#ifndef INTERFACEPRESSION_H
#define INTERFACEPRESSION_H

/**
 * @brief Les différent unités:
 * 0 - Bar
 * 1 - Pascal
 * 2 - Pounds per square inch
 * 
 */
typedef struct 
{
    unsigned char niveau_Urgence;
    unsigned char unite;
    int tab_Moyenne_Pression[GROSSEUR_TAB_MOYENNE];
    int pression;
}INTERFACE_Pression;



int interface_PRESSION_Initialise();
int interface_PRESSION_Read(int *valeur);


extern INTERFACE_Pression interface_Pression_Struct;

#endif