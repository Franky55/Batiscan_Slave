#include "Arduino.h"
#include "main.h"
#include "serviceBaseDeTemps.h"
#include "interface_GPIO.h"
#include "interface_PWM.h"
#include "Processus_Communication.h"
#include "processusClignotant.h"
#include "Processus_Ballast.h"


#define PROCESSUS_BALLAST_FULL (\
  PROCESSUS_BALLAST_FULL_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /1000.0)

#define PROCESSUS_BALLAST_EMPTY (\
  PROCESSUS_BALLAST_EMPTY_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /1000.0)

  
bool writeONCE = false;


void processus_Ballast_Wait_State();
void processus_Ballast_FILL_UP();
void processus_Ballast_EMPTY_OUT();


PROCESSUS_BALLAST processus_Ballast_Struct;


int processus_Ballast_initialise(void)
{
    processus_Ballast_Struct.limit_Switch_Bas = 0;
    processus_Ballast_Struct.limit_Switch_Haut = 0;
    processus_Ballast_Struct.state = 0;
    processus_Ballast_Struct.timer_Control_Ballast = 0;
    processus_Ballast_Struct.ByPASS = 0;

    digitalWrite(DRIVE_BALLAST, LOW);
    //interface_Analogue_Write(DRIVE_BALLAST, 0);
    interface_GPIO_Write(VALVE, CLOSE_VALVE);

    serviceBaseDeTemps_execute[PROCESSUS_GESTION_BALLAST] = processus_Ballast_Wait_State;
    return 0;
}


/**
 * @brief Fonction qui attend le changement du State
 * 
 */
void processus_Ballast_Wait_State()
{
    processus_Communication_Struct_ACTUAL_Value.union_Bool.bits.Ballast_State = processus_Ballast_Struct.FULL;
    processus_Ballast_Struct.state = processus_Communication_Struct_WANTED_Value.union_Bool.bits.Ballast_State;

    if(processus_Communication_Struct_ACTUAL_Value.union_Bool.bits.In_Emergency == 1 || processus_Ballast_Struct.ByPASS == 1)
    {
        processus_Ballast_Struct.state = STATE_BALLAST_EMPTY_OUT;
    }
    
    // Serial.print("BALLAST: ");
    // Serial.println(processus_Communication_Struct_WANTED_Value.union_Bool.bits.Ballast_State);
    
    switch (processus_Ballast_Struct.state)
    {
        case STATE_BALLAST_FILL_UP:
            
            serviceBaseDeTemps_execute[PROCESSUS_GESTION_BALLAST] = processus_Ballast_FILL_UP;
        break;

        case STATE_BALLAST_EMPTY_OUT:
            
            serviceBaseDeTemps_execute[PROCESSUS_GESTION_BALLAST] = processus_Ballast_EMPTY_OUT;
        break;

    }
}

/**
 * @brief Fonction qui remplie la ballast
 * si la ballast est pleine elle va toujours retourner dans le wait State
 * 
 */
void processus_Ballast_FILL_UP()
{
    if(processus_Ballast_Struct.state != STATE_BALLAST_FILL_UP)                                 //Check si communication a changer le State
    {
        interface_GPIO_Write(VALVE, CLOSE_VALVE);
        digitalWrite(DRIVE_BALLAST, LOW);
        serviceBaseDeTemps_execute[PROCESSUS_GESTION_BALLAST] = processus_Ballast_Wait_State;
        return;
    }


    if(processus_Ballast_Struct.timer_Control_Ballast >= PROCESSUS_BALLAST_FULL)                //Check si timer est trop haut
    {
        interface_GPIO_Write(VALVE, CLOSE_VALVE);
        digitalWrite(DRIVE_BALLAST, LOW);
        processus_Ballast_Struct.FULL = 1;
        processus_Ballast_Struct.state = STATE_BALLAST_WAIT;
        serviceBaseDeTemps_execute[PROCESSUS_GESTION_BALLAST] = processus_Ballast_Wait_State;
        return;
    }

    processus_Ballast_Struct.timer_Control_Ballast++;                                           //augmente le timer

    interface_GPIO_Write(VALVE, OPEN_VALVE);
    digitalWrite(DRIVE_BALLAST, LOW);
    serviceBaseDeTemps_execute[PROCESSUS_GESTION_BALLAST] = processus_Ballast_Wait_State;
}


/**
 * @brief Fonction qui vide la ballast
 * si la ballast est vide elle va toujours retourner dans le wait State
 * 
 */
void processus_Ballast_EMPTY_OUT()
{
    if(processus_Ballast_Struct.state != STATE_BALLAST_EMPTY_OUT)
    {
        // Serial.println("Ballast != STATE_BALLAST_EMPTY_OUT");
        digitalWrite(DRIVE_BALLAST, LOW);
        //interface_Analogue_Write(DRIVE_BALLAST, 0);
        interface_GPIO_Write(VALVE, CLOSE_VALVE);
        serviceBaseDeTemps_execute[PROCESSUS_GESTION_BALLAST] = processus_Ballast_Wait_State;
        return;
    }


    if(processus_Ballast_Struct.timer_Control_Ballast <= PROCESSUS_BALLAST_EMPTY)               //Check si timer est trop bas
    {
        // Serial.println("Ballast <= PROCESSUS_BALLAST_EMPTY");
        digitalWrite(DRIVE_BALLAST, LOW);
        //interface_Analogue_Write(DRIVE_BALLAST, 0);
        interface_GPIO_Write(VALVE, CLOSE_VALVE);
        
        processus_Ballast_Struct.FULL = 0;
        processus_Ballast_Struct.state = STATE_BALLAST_WAIT;
        writeONCE = false;
        serviceBaseDeTemps_execute[PROCESSUS_GESTION_BALLAST] = processus_Ballast_Wait_State;
        return;
    }
    processus_Ballast_Struct.timer_Control_Ballast--;
    digitalWrite(DRIVE_BALLAST, HIGH);
    interface_GPIO_Write(VALVE, OPEN_VALVE);
    // Serial.print("Empty ballast: ");
    // Serial.println(interface_PWM_Struct.Ballast_value);
    serviceBaseDeTemps_execute[PROCESSUS_GESTION_BALLAST] = processus_Ballast_Wait_State;
    return;
}