
#include "main.h"
#include "Pilote_ADC.h"
#include "interface_CapteurEau.h"
#include "interface_GPIO.h"

int interface_CAPTEUREAU_Initialise()
{
    return 0;
}


int interface_CAPTEUREAU_Read(bool *valeur)
{
    
    interface_GPIO_Read(EAU, valeur);    

    return 0;
}