
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
    write_PWM(SERVO_X,  90);
    
    write_PWM(SERVO_GA, 90);
    write_PWM(SERVO_GR, 90);
    write_PWM(SERVO_DA, 90);
    write_PWM(SERVO_DR, 90);
    write_PWM(SERVO_H,  90);
    write_PWM(SERVO_S,  90);

    write_PWM_Frequency(DRIVE_MOTEUR, 1500);//1100-1475,   1525-1900
    write_PWM_Frequency(DRIVE_BALLAST, 1500);

    return 0;
}


float write_PWM(int servoPin, int position)
{
    return pwm.writeServo(servoPin, position, speed1, ke1);
}


/**
 * @brief La fonction va mettre la bonne frequence demande et retourne la valeur de la frequence
 * 
 * @param servoPin 
 * @param frequency 
 * @return float 
 */
float write_PWM_Frequency(int servoPin, int frequency)
{
    return pwm.write(servoPin, 0, frequency, 8);
}