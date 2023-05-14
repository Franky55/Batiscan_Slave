
#include <Arduino.h>
#include "main.h"
#include "pilote_PWM.h"
#include "interface_PWM.h"


int interface_PWM_Initialise()
{
    return 0;
}



void interface_Write_PWM(int position)
{
    write_PWM(SERVO_AXE_X, position);
}


