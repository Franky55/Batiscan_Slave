#ifndef PROCESSUSBALLAST_H
#define PROCESSUSBALLAST_H

#define STATE_BALLAST_WAIT 0
#define STATE_BALLAST_FILL_UP 1
#define STATE_BALLAST_EMPTY_OUT 2

typedef struct
{
    unsigned char state;
    int timer_Control_Ballast;
    bool limit_Switch_Haut;
    bool limit_Switch_Bas;

}PROCESSUS_BALLAST;




int processus_Ballst_initialise(void);

extern PROCESSUS_BALLAST processus_Ballast_Struct;
#endif