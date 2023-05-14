
#ifndef INTERFACESPISLAVE_H
#define INTERFACESPISLAVE_H

int interface_SPI_SLAVE_initialise();
int interface_SPI_SLAVE_Transaction(const unsigned char * data, unsigned char * out, unsigned long size);

#endif