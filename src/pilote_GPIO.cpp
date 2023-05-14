 
#include <Arduino.h>
#include "main.h"
#include "pilote_GPIO.h"

int pilote_GPIO_Initialise()
{
    pinMode(47, OUTPUT);
    digitalWrite(47, LOW);
    return 0;
}


int pilote_GPIO_Write(int pin, bool etat)
{
    digitalWrite(pin, etat);
    return 0;
}