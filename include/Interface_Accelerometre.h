
#ifndef INTERFACEACCELEROMETRE_H
#define INTERFACEACCELEROMETRE_H

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
int interface_Accelerometre_initialise(void);
int Get_Sensor_Event(sensors_event_t *a, sensors_event_t *g, sensors_event_t *temp);
int interface_Accelerometre_Accelerometre(float *accAngleX, float *accAngleY);
int interface_Accelerometre__Gyroscope(float *GyroX, float *GyroY, float *GyroZ);
int interface_Accelerometre_Rotation();

#endif