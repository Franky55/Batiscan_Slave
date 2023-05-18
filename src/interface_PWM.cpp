
#include <Arduino.h>
#include "main.h"
#include "pilote_PWM.h"
#include "interface_PWM.h"

int comptPWM = 0;

int interface_PWM_Initialise()
{
    return 0;
}



void interface_Write_PWM(int position)
{
    //write_PWM_Frequency(SERVO_AXE_X, position);
    

    switch (comptPWM)
    {
    case 0:
        write_PWM(SERVO_GA, position);
        //break;
        //case 100:
        write_PWM(SERVO_GR, position);
        //break;
        //case 200:
        write_PWM(SERVO_DA, position);
        //break;
        //case 300:
        write_PWM(SERVO_DR, position);
        //break;
        //case 400:
        write_PWM(SERVO_H,  position);
        //break;
        //case 500:
        write_PWM(SERVO_S,  180-position);
        break;
        
        case 600:
        
        comptPWM = 0;
        break;

    
    
    }
    comptPWM++;
    
    
    
    
    

    //write_drive_moteur(1700);
    //write_PWM_Frequency(DRIVE_BALLAST, 127);
}


