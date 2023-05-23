#ifndef INTERFACEGPIO_H
#define INTERFACEGPIO_H


typedef struct
{
    bool Lumiere_D;
    bool Lumiere_G;

    bool Control_Cam;

}INTERFACE_GPIO;


int interface_GPIO_Initialise();
int interface_GPIO_Write(int pin, bool etat);
int interface_GPIO_Read(int pin, bool * etat);


extern INTERFACE_GPIO interface_GPIO_Struct;

#endif