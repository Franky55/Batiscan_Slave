#ifndef INTERFACENIVEAUBATTERIE_H
#define INTERFACENIVEAUBATTERIE_H

/**
 * @brief Les différent unités:
 * 0 - Bar
 * 1 - Pascal
 * 2 - Pounds per square inch
 * 
 */
typedef struct 
{
    unsigned char unite;
    int batterie;
}INTERFACE_Niveau_Batterie;



int interface_NIVEAUBATTERIE_Initialise();
int interface_NIVEAUBATTERIE_Read(int *valeur);


extern INTERFACE_Niveau_Batterie interface_Niveau_Batterie_Struct;

#endif