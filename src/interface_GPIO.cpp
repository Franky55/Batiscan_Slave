#include <Arduino.h>
#include "main.h"
#include "interface_GPIO.h"

int interface_GPIO_Initialise()
{
    pinMode(47, OUTPUT);
    digitalWrite(47, LOW);
    return 0;
}


int interface_GPIO_Write(int pin, bool etat)
{
    digitalWrite(pin, etat);
    return 0;
}