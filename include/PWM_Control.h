

#ifndef PWMCONTROL_H
#define PWMCONTROL_H



class PWM_Control
{
    private:
    

    public:
    PWM_Control();
    //void PWM_Control();

    float write_PWM(int servoPin, int position);

};



#endif