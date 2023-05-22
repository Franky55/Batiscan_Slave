#ifndef PROCESSUSCALCULEACCELEROMETRE_H
#define PROCESSUSCALCULEACCELEROMETRE_H

typedef struct
{
    unsigned char State;
    unsigned char tabReceived[255];
    int DataToRead;
    int DataToSend;
    int DataToSendSPI;
}PROCESSUS_CALCULEACCELEROMETRE;




int processus_Calcule_Accelerometre_initialise();
void processus_Calcule_Accelerometre_Affiche();

extern PROCESSUS_CALCULEACCELEROMETRE processus_Calcule_Accelerometre_Struct;
#endif