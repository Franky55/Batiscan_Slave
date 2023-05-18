#include <Arduino.h>
#include "main.h"
#include "interface_NEOPIXEL.h"
#include "interface_SPI_Slave.h"
#include "serviceBaseDeTemps.h"
#include <ESP32SPISlave.h>

#define INTERFACEGPIO10_COMPTE  (\
  GPIO10_TEMPS_POUR_RESET_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /1000.0)

void interface_SPI_WaitForMaster();
void interface_SPI_Queue_Transaction();
void interface_SPI_Data_Available();
void interface_SPI_ReadData();


ESP32SPISlave slave;
INTERFACESPISTRUCT interface_SPI_Struct;

unsigned char RAW_RX_buf[SPI_BUFFER_SIZE] {0};
unsigned long interface_Compteur_Master_Connecte = 0;

int interface_SPI_SLAVE_initialise()
{
    pinMode(INTERFACE_SPI_CS1, OUTPUT);

    digitalWrite(INTERFACE_SPI_CS1, LOW);
    interface_Compteur_Master_Connecte = 0;
    interface_SPI_Struct.etatDuModule = 0;
    memset(interface_SPI_Struct.spi_slave_rx_buf, 0, SPI_BUFFER_SIZE);
    memset(interface_SPI_Struct.spi_slave_tx_buf, 0, SPI_BUFFER_SIZE);
    
    serviceBaseDeTemps_executeDansLoop[INTERFACESPI_TRANSACTION] = interface_SPI_WaitForMaster;
    
    return 0;
}

void interface_SPI_WaitForMaster()
{
    interface_Compteur_Master_Connecte++;
    digitalWrite(GPIO10, LOW);
    //interface_NEOPIXEL_allume(50, 10, 0);
    if (interface_Compteur_Master_Connecte < INTERFACEGPIO10_COMPTE)
    {
        return;
    }
    //digitalWrite(GPIO10, HIGH);
    pinMode(INTERFACE_SPI_CS1, INPUT);
    pinMode(SPI_CLK, INPUT);
    pinMode(SPI_MOSI, INPUT);
    //interface_NEOPIXEL_allume(0, 100, 0);

    interface_Compteur_Master_Connecte = 0;
    slave.setDataMode(SPI_MODE0);
    slave.begin(SPI3_HOST, SPI_CLK, SPI_MISO, SPI_MOSI, INTERFACE_SPI_CS1);
    serviceBaseDeTemps_executeDansLoop[INTERFACESPI_TRANSACTION] = interface_SPI_Queue_Transaction;
}

void interface_SPI_Queue_Transaction()
{
    //interface_NEOPIXEL_allume(0, 10, 0);


    
    slave.queue(RAW_RX_buf, interface_SPI_Struct.spi_slave_tx_buf, 3);
    
    

    serviceBaseDeTemps_executeDansLoop[INTERFACESPI_TRANSACTION] = interface_SPI_Data_Available;
 
}


void interface_SPI_Data_Available()
{
    //interface_NEOPIXEL_allume(100, 0, 0);

    //Serial.println(digitalRead(GPIO10));
    //interface_NEOPIXEL_allume(100, 0, 0);

    if(slave.available())
    {
        //interface_NEOPIXEL_allume(0, 100, 100);
        serviceBaseDeTemps_executeDansLoop[INTERFACESPI_TRANSACTION] = interface_SPI_ReadData;
    }
    
  
}


void interface_SPI_ReadData()
{
    //interface_NEOPIXEL_allume(0, 100, 0);
    interface_SPI_Struct.spi_message_size = slave.size();
    for(int i = 0; i < interface_SPI_Struct.spi_message_size; i++)
    {
        interface_SPI_Struct.spi_slave_rx_buf[i] = RAW_RX_buf[i];
    }

    memset(RAW_RX_buf, 0, SPI_BUFFER_SIZE);

    // you should pop the received packet
    slave.pop();

    interface_SPI_Struct.etatDuModule = 1;
    

    

    serviceBaseDeTemps_executeDansLoop[INTERFACESPI_TRANSACTION] = interface_SPI_Queue_Transaction;

  
}

