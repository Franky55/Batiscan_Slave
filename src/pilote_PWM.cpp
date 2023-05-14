
#include <Arduino.h>
#include "main.h"
#include <pwmWrite.h>
#include "pilote_PWM.h"



// units in degrees per second
float speed1 = 70.0;
float speed2 = 140.0;
float speed3 = 180.0;


float ke1 = 0.0;
float ke2 = 0.6;
float ke3 = 0.8;


Pwm pwm = Pwm();

int pilote_PWM_Initialise()
{
    return 0;
}



float write_PWM(int servoPin, int position)
{

    return pwm.writeServo(servoPin, position, speed1, ke1);

}