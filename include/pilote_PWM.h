

#ifndef PILOTEPWM_H
#define PILOTEPWM_H



int pilote_PWM_Initialise();
float write_PWM(int servoPin, int position);
float write_PWM_Frequency(int servoPin, int frequency);

#endif