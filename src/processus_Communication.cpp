#include "Arduino.h"
#include "main.h"
#include "interface_NEOPIXEL.h"
#include "interface_SPI_Slave.h"
#include "interface_GPIO.h"
#include "serviceBaseDeTemps.h"
#include "service_Protocole_SPI.h"
#include <stdio.h>
#include "Processus_Communication.h"

// if udp:         https://gist.github.com/santolucito/70ecb94ce297eb1b8b8034f78683447b

void processus_Communication_Att_Lire();
void processus_Communication_Lire();
void processus_Communication_Set_New_Com();

int compt_Since_Last_Trame = 0;

PROCESSUS_COMMUNICATION processus_Communication_Struct_WANTED_Value;
PROCESSUS_COMMUNICATION processus_Communication_Struct_ACTUAL_Value;

/**
 * @brief La fonction initialise le processus de la communication
 * Met la LED bleu
 * -> processus_Communication_Set_New_Com
 * 
 * @return int 
 */
int Processus_Communication_initialise(void)
{
    processus_Communication_Struct_WANTED_Value.Is_Communicating = 1;
    processus_Communication_Struct_WANTED_Value.Pitch = 0;
    processus_Communication_Struct_WANTED_Value.Roll = 0;
    processus_Communication_Struct_WANTED_Value.Yaw = 0;

    processus_Communication_Struct_WANTED_Value.union_Bool.All = 0;



    interface_NEOPIXEL_allume(0, 0, 100);
    serviceBaseDeTemps_execute[PROCESSUSCOMMUNICATION] = processus_Communication_Set_New_Com;
    
    return 0;
}

/**
 * @brief Cette fonction check interface_SPI_Struct.etatDuModule
 * une fois que c'est egale a 1, il devrait avoir du data de disponnible
 * -> processus_Communication_Lire
 * 
 */
void processus_Communication_Att_Lire()
{
    compt_Since_Last_Trame++;
    if(interface_SPI_Struct.etatDuModule != 1)
    {
        if(compt_Since_Last_Trame > 100)    // 100 ms
        {
            processus_Communication_Struct_WANTED_Value.Is_Communicating = 0;
            interface_SPI_SLAVE_initialise();// cela va reset le master
        }
        if(compt_Since_Last_Trame > 2000)   // 2000 ms
        {
            processus_Communication_Struct_WANTED_Value.union_Bool.bits.In_Emergency = 1;
            processus_Communication_Struct_ACTUAL_Value.union_Bool.bits.In_Emergency = 1;
            interface_SPI_SLAVE_initialise();// cela va reset le master
        }

        return;
    }
    compt_Since_Last_Trame = 0;
    processus_Communication_Struct_WANTED_Value.Is_Communicating = 1;
    serviceBaseDeTemps_execute[PROCESSUSCOMMUNICATION] = processus_Communication_Lire;

}

/**
 * @brief Cette fonction permet de lire le data
 * J'appelle la fonction service_Protocole_SPI_Received:
 * Cette fonction update les valeurs si tous les parametres font du sense
 * interface_SPI_Struct.etatDuModule = 0
 * -> processus_Communication_Set_New_Com
 * 
 */
void processus_Communication_Lire()
{

    service_Protocole_SPI_Received(interface_SPI_Struct.spi_slave_rx_buf, &interface_SPI_Struct.spi_message_size);

    interface_SPI_Struct.etatDuModule = 0;


    serviceBaseDeTemps_execute[PROCESSUSCOMMUNICATION] = processus_Communication_Set_New_Com;
}

/**
 * @brief Prepare une trame de communication
 * Utilise la fonction: service_Protocole_SPI_Pepare_Trame_Slave_To_Master
 * interface_SPI_Struct.trameReady = 1
 * -> processus_Communication_Att_Lire
 * 
 */
void processus_Communication_Set_New_Com()
{
    
    service_Protocole_SPI_Pepare_Trame_Slave_To_Master(interface_SPI_Struct.spi_slave_tx_buf, &interface_SPI_Struct.spi_message_size);
    interface_SPI_Struct.trameReady = 1;
    serviceBaseDeTemps_execute[PROCESSUSCOMMUNICATION] = processus_Communication_Att_Lire;
}

