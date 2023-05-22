 
#include <Arduino.h>
#include "main.h"
#include "pilote_GPIO.h"

int pilote_GPIO_Initialise()
{
    pinMode(47, OUTPUT);
    digitalWrite(47, LOW);

    pinMode(VALVE, OUTPUT);
    digitalWrite(VALVE, LOW);

    pinMode(LUMIERE_D, OUTPUT);
    digitalWrite(LUMIERE_D, LOW);

    pinMode(LUMIERE_G, OUTPUT);
    digitalWrite(LUMIERE_G, LOW);

    pinMode(DIRECTION_BALLAST, OUTPUT);
    digitalWrite(DIRECTION_BALLAST, HIGH);//dit la direction de la ballast

    return 0;
}


int pilote_GPIO_Write(int pin, bool etat)
{
    digitalWrite(pin, etat);
    return 0;
}