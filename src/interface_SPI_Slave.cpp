#include <Arduino.h>
#include "main.h"
#include "interface_NEOPIXEL.h"
#include "interface_SPI_Slave.h"
#include "serviceBaseDeTemps.h"
#include <ESP32SPISlave.h>
//#include <ESP32DMASPISlave.h>

#define INTERFACEGPIO10_COMPTE  (\
  GPIO10_TEMPS_POUR_RESET_EN_MS * SERVICEBASEDETEMPS_FREQUENCE_EN_HZ \
  /1000.0)
#define INTERFACE_RESET_MASTER 100


void interface_SPI_Reset_Master();
void interface_SPI_Start_SPI();
void interface_SPI_Queue_Transaction();
void interface_SPI_Data_Available();
void interface_SPI_ReadData();


ESP32SPISlave slave;
INTERFACESPISTRUCT interface_SPI_Struct;

unsigned char RAW_RX_buf[SPI_BUFFER_SIZE] {0};
unsigned long interface_Compteur_Master_Connecte = 0;

int spi_compt_available = 0;


int interface_SPI_SLAVE_initialise()
{
    pinMode(INTERFACE_SPI_CS1, OUTPUT);
    interface_Compteur_Master_Connecte = 0;
    interface_SPI_Struct.etatDuModule = 0;
    interface_SPI_Struct.trameReady = 0;
    memset(interface_SPI_Struct.spi_slave_rx_buf, 0, SPI_BUFFER_SIZE);
    memset(interface_SPI_Struct.spi_slave_tx_buf, 0, SPI_BUFFER_SIZE);
    
    serviceBaseDeTemps_executeDansLoop[INTERFACESPI_TRANSACTION] = interface_SPI_Reset_Master;
    
    return 0;
}

void interface_SPI_Reset_Master()
{
    interface_Compteur_Master_Connecte++;
    
    digitalWrite(INTERFACE_SPI_CS1, LOW);
    //interface_NEOPIXEL_allume(50, 10, 0);
    if (interface_Compteur_Master_Connecte < INTERFACE_RESET_MASTER)
    {
        digitalWrite(GPIO_NUM_48, LOW);
        return;
    }

    digitalWrite(GPIO_NUM_48, HIGH);

    if (interface_Compteur_Master_Connecte < INTERFACEGPIO10_COMPTE)
    {
        return;
    }
    interface_Compteur_Master_Connecte = 0;
    serviceBaseDeTemps_executeDansLoop[INTERFACESPI_TRANSACTION] = interface_SPI_Start_SPI;
}

void interface_SPI_Start_SPI()
{
  
    //digitalWrite(GPIO10, HIGH);
    pinMode(INTERFACE_SPI_CS1, INPUT);
    pinMode(SPI_CLK, INPUT);
    pinMode(SPI_MOSI, INPUT);

    //interface_NEOPIXEL_allume(0, 100, 0);

    interface_Compteur_Master_Connecte = 0;
    slave.setDataMode(SPI_MODE0);
    slave.begin(SPI2_HOST, SPI_CLK, SPI_MISO, SPI_MOSI, INTERFACE_SPI_CS1);
    slave.setQueueSize(1);
    serviceBaseDeTemps_executeDansLoop[INTERFACESPI_TRANSACTION] = interface_SPI_Queue_Transaction;
}

void interface_SPI_Queue_Transaction()
{
    //interface_NEOPIXEL_allume(0, 10, 0);
    if(interface_SPI_Struct.trameReady == 0)
    {
        return;
    }
    
    slave.end();
    slave.setDataMode(SPI_MODE0);
    slave.begin(SPI2_HOST, SPI_CLK, SPI_MISO, SPI_MOSI, INTERFACE_SPI_CS1);
    slave.setQueueSize(1);
    interface_SPI_Struct.trameReady = 0;

    slave.queue(RAW_RX_buf, interface_SPI_Struct.spi_slave_tx_buf, 4);

    Serial.println("Trame Ready");
    

    serviceBaseDeTemps_executeDansLoop[INTERFACESPI_TRANSACTION] = interface_SPI_Data_Available;
 
}

int compt_CAVE = 0;

void interface_SPI_Data_Available()
{
    //interface_NEOPIXEL_allume(100, 0, 0);

    //Serial.println(digitalRead(GPIO10));
    //interface_NEOPIXEL_allume(100, 0, 0);
    // compt_CAVE++;
    // if(compt_CAVE < 500)
    // {
    //     return;
    // }
    // compt_CAVE = 0;
    // Serial.print("Sizeof: ");
    // Serial.println(slave.available());

    if(slave.available())
    {
        //interface_NEOPIXEL_allume(0, 100, 100);
        sleep(0);
        interface_SPI_ReadData();
        
        //serviceBaseDeTemps_executeDansLoop[INTERFACESPI_TRANSACTION] = interface_SPI_ReadData;
    }
    
  
}


void interface_SPI_ReadData()
{
    //interface_NEOPIXEL_allume(0, 100, 0);
    
    interface_SPI_Struct.spi_message_size = (unsigned char)slave.size();

    
    // Serial.print("Data Received ");
    // Serial.print(interface_SPI_Struct.spi_message_size);
    // Serial.print(" : ");

    for(int i = 0; i < interface_SPI_Struct.spi_message_size; i++)
    {
        // Serial.print((char)RAW_RX_buf[i]);
        interface_SPI_Struct.spi_slave_rx_buf[i] = RAW_RX_buf[i];
    }
    // Serial.println("");
    memset(RAW_RX_buf, 0, SPI_BUFFER_SIZE);

    // you should pop the received packet
    slave.pop();

    while(slave.available())
    {
        compt_CAVE++;
        slave.pop();
    }
    // Serial.print("compt_CAVE: ");
    // Serial.println(compt_CAVE);

    compt_CAVE =0;

    interface_SPI_Struct.etatDuModule = 1;
    

    

    serviceBaseDeTemps_executeDansLoop[INTERFACESPI_TRANSACTION] = interface_SPI_Queue_Transaction;

  
}

