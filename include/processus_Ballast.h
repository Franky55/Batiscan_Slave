#ifndef PROCESSUSBALLAST_H
#define PROCESSUSBALLAST_H

#define STATE_BALLAST_WAIT 2
#define STATE_BALLAST_FILL_UP 1
#define STATE_BALLAST_EMPTY_OUT 0

typedef struct
{
    unsigned char state;
    int timer_Control_Ballast;
    bool limit_Switch_Haut;
    bool limit_Switch_Bas;
    bool FULL;

}PROCESSUS_BALLAST;




int processus_Ballast_initialise(void);

extern PROCESSUS_BALLAST processus_Ballast_Struct;
#endif