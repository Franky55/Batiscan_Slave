#include <Arduino.h>
#include "main.h"
#include <SPI.h>
#include "interface_SPI_Slave.h"




SPIClass interfaceSPI_Slave(HSPI);


int interface_SPI_SLAVE_initialise()
{
    pinMode(SPI_CS1, OUTPUT);

    digitalWrite(SPI_CS1, LOW);

    interfaceSPI_Slave.begin(SPI_CLK, SPI_MISO, SPI_MOSI, SPI_CS1);
    //interfaceSPI_Slave.setClockDivider(1);
    //interfaceSPI_Slave.setDataMode();
    //interfaceSPI_Slave.setBitOrder();
    // interfaceSPI_Slave.setFrequency(10000000);
    return 0;
}


int interface_SPI_SLAVE_Transaction(const unsigned char * data, unsigned char * out, unsigned long size)
{
    interfaceSPI_Slave.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));

    digitalWrite(SPI_CS1, LOW);  // Select the slave device
  
  // Send each character of the command string
  for (size_t i = 0; i < size; i++) {
    interfaceSPI_Slave.transfer(data[i]);
  }

  digitalWrite(SPI_CS1, HIGH);  // Deselect the slave device
    interfaceSPI_Slave.endTransaction();
    Serial.print("Data Sending:     ");

    for(int i = 0; i < size; i++)
    {
        Serial.print((char)data[i]);
    }

    Serial.print("Data Sending:     ");

    for(int i = 0; i < size; i++)
    {
        Serial.print((char)data[i]);
    }


    Serial.print("\nData receiving:     ");

    for(int i = 0; i < size; i++)
    {
        Serial.print((char)out[i]);
    }

    return 0;
}