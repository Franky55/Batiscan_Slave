#ifndef INTERFACECAPTEUREAU_H
#define INTERFACECAPTEUREAU_H

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
    int tab_Moyenne_eau[GROSSEUR_TAB_MOYENNE];
    bool eau;
}INTERFACE_Niveau_eau;


int interface_CAPTEUREAU_Initialise();
int interface_CAPTEUREAU_Read(bool *valeur);

extern INTERFACE_Niveau_eau interface_Niveau_eau;

#endif