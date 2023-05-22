
#include "main.h"
#include "Pilote_ADC.h"
#include "interface_CapteurEau.h"
#include "interface_GPIO.h"

void interface_CapteurEau_Verification_eau(bool valeur);


INTERFACE_Niveau_eau interface_Niveau_eau;

int interface_CAPTEUREAU_Initialise()
{
    return 0;
}


int interface_CAPTEUREAU_Read(bool *valeur)
{
    
    interface_GPIO_Read(EAU, valeur);    

    interface_CapteurEau_Verification_eau(valeur);
    interface_Niveau_eau.eau = valeur;

    return 0;
}



/**
 * @brief La fonction determine le niveau d'urgence
 * 
 * @param valeur 
 */
void interface_CapteurEau_Verification_eau(bool valeur)
{
    switch (valeur)
    {
    case 1:
        interface_Niveau_eau.niveau_Urgence = NIVEAU_URGENCE_0;
    break;
    
    case 0 :
        interface_Niveau_eau.niveau_Urgence = NIVEAU_URGENCE_URGENT;
    break;
    
    }
}