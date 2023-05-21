#ifndef PROCESSUSBALLAST_H
#define PROCESSUSBALLAST_H

typedef struct
{
    unsigned char action_a_Faire;
    int timer_Control_Ballast;
    bool limit_Switch_Haut;
    bool limit_Switch_Bas;

}PROCESSUS_BALLAST;




int processus_Ballst_initialise(void);

extern PROCESSUS_BALLAST processus_Ballast_Struct;
#endif