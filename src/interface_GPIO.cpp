#include <Arduino.h>
#include "main.h"
#include "pilote_GPIO.h"
#include "interface_GPIO.h"
#include "serviceBaseDeTemps.h"

void interface_GPIO_update();

INTERFACE_GPIO interface_GPIO_Struct;

int interface_GPIO_Update_Compt = 0;

int interface_GPIO_Initialise()
{
    interface_GPIO_Update_Compt = 0;

    pinMode(47, OUTPUT);
    digitalWrite(47, LOW);

    serviceBaseDeTemps_execute[INTERFACE_UPDATE_GPIO] = interface_GPIO_update;

    return 0;
}

void interface_GPIO_update()
{
    interface_GPIO_Update_Compt++;

    if(interface_GPIO_Update_Compt < 100)
    {
        return;
    }

    interface_GPIO_Update_Compt = 0;

    pilote_GPIO_Write(LUMIERE_D, interface_GPIO_Struct.Lumiere_D);
    pilote_GPIO_Write(LUMIERE_G, interface_GPIO_Struct.Lumiere_G);
    pilote_GPIO_Write(CONTROL_POWER_CAM, interface_GPIO_Struct.Control_Cam);
}



int interface_GPIO_Write(int pin, bool etat)
{
    digitalWrite(pin, etat);
    return 0;
}

int interface_GPIO_Read(int pin, bool * etat)
{
    *etat = digitalRead(pin);
    return 0;
}