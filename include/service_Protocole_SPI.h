
#ifndef SERVICEPROTOCOLESPI_H
#define SERVICEPROTOCOLESPI_H




int service_Protocole_SPI_initialise(void);
int service_Protocole_SPI_Received(unsigned char* plane, unsigned char* size);
int service_Protocole_SPI_Pepare_Trame_Slave(unsigned char* plane, unsigned char* size);


#endif