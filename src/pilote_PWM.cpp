
#include <Arduino.h>
#include "main.h"
#include <pwmWrite.h>
#include "pilote_PWM.h"




// units in degrees per second
float speed1 = 10.0;
float speed2 = 140.0;
float speed3 = 180.0;


float ke1 = 0.0;
float ke2 = 0.6;
float ke3 = 0.8;


Pwm pwm = Pwm();

int pilote_PWM_Initialise()
{
    digitalWrite(SERVO_X,  LOW);
    digitalWrite(SERVO_GA, LOW);
    digitalWrite(SERVO_GR, LOW);
    digitalWrite(SERVO_DA, LOW);
    digitalWrite(SERVO_DR, LOW);
    digitalWrite(SERVO_H,  LOW);
    digitalWrite(SERVO_S,  LOW);

    digitalWrite(DIRECTION_BALLAST,  HIGH);

    //digitalWrite(DRIVE_MOTEUR,  LOW);

    


    pinMode(SERVO_X,  OUTPUT);
    pinMode(SERVO_GA, OUTPUT);
    pinMode(SERVO_GR, OUTPUT);
    pinMode(SERVO_DA, OUTPUT);
    pinMode(SERVO_DR, OUTPUT);
    pinMode(SERVO_H,  OUTPUT);
    pinMode(SERVO_S,  OUTPUT);

    pinMode(DRIVE_MOTEUR,  OUTPUT);
    pinMode(DRIVE_BALLAST, OUTPUT);
    pinMode(DIRECTION_BALLAST, OUTPUT);
    //write_PWM(DRIVE_MOTEUR, 90);
    //write_PWM_Frequency(DRIVE_MOTEUR, 400);
    // write_PWM_Frequency(DRIVE_MOTEUR, 1500);//1100-1475,   1525-1900
    // write_PWM_Frequency(DRIVE_BALLAST, 1500);

    return 0;
}


float write_PWM(int servoPin, int value)
{
    return pwm.writeServo(servoPin, value);
}

