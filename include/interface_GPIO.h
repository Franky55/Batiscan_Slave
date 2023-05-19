#ifndef INTERFACEGPIO_H
#define INTERFACEGPIO_H


int interface_GPIO_Initialise();
int interface_GPIO_Write(int pin, bool etat);
int interface_GPIO_Read(int pin, bool * etat);

#endif