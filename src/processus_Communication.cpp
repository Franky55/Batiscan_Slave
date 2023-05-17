#include "Arduino.h"
#include "main.h"
#include "interface_NEOPIXEL.h"
#include "interface_SPI_Slave.h"
#include "serviceBaseDeTemps.h"
//#include "BFIO"
#include <stdio.h>
#include "Processus_Communication.h"

// if udp:         https://gist.github.com/santolucito/70ecb94ce297eb1b8b8034f78683447b

void processus_Communication_Att_Lire();
void processus_Communication_Lire();
void processus_Communication_Set_New_Com();

int compt = 0;



int Processus_Communication_initialise(void)
{

    interface_NEOPIXEL_allume(0, 0, 100);
    serviceBaseDeTemps_execute[PROCESSUSCOMMUNICATION] = processus_Communication_Set_New_Com;
    
    return 0;
}

void processus_Communication_Att_Lire()
{
    if(interface_SPI_Struct.etatDuModule != 1)
    {
        return;
    }

    serviceBaseDeTemps_execute[PROCESSUSCOMMUNICATION] = processus_Communication_Lire;

}


void processus_Communication_Lire()
{
    Serial.print("Data Received: ");
    for(int i = 0; i < interface_SPI_Struct.spi_message_size; i++)
    {
        Serial.print(interface_SPI_Struct.spi_slave_rx_buf[i]);
    }
    Serial.println("");

    interface_SPI_Struct.etatDuModule = 0;


    serviceBaseDeTemps_execute[PROCESSUSCOMMUNICATION] = processus_Communication_Set_New_Com;
}


void processus_Communication_Set_New_Com()
{
    for(int i = 0; i < SPI_BUFFER_SIZE; i++)
    {
        interface_SPI_Struct.spi_slave_tx_buf[i] = 'A';
    }

    serviceBaseDeTemps_execute[PROCESSUSCOMMUNICATION] = processus_Communication_Att_Lire;
}

