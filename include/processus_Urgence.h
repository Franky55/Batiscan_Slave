
#ifndef PROCESSUSURGENCE_H
#define PROCESSUSURGENCE_H


/**
 * @brief Les niveaux d'urgences
 * 0: 
 * 
 */
typedef struct 
{
    unsigned char Urgence_Temperature;
    unsigned char Urgence_Pression;
    unsigned char Urgence_DectectionEau;
}PROCESSUS_Urgence;



int Processus_Urgence_initialise();
void Print_Acc_Data();
void MoveServo();

extern PROCESSUS_Urgence processus_Urgence_struct;

#endif