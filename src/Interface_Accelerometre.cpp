
#include <Arduino.h>
#include "main.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include "Interface_Accelerometre.h"



#define ADDRESSE 0x68

TwoWire I2C = TwoWire(0);
Adafruit_MPU6050 mpu;


int interface_Accelerometre_initialise(void)
{
  
  I2C.begin(I2C_SDA, I2C_SCL, 400000);

  if (!mpu.begin(ADDRESSE, &I2C, 0)) 
  {
    Serial.println("Failed to find MPU6050 chip");
    return -1;
  }

    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);


  return 0;

}


int Get_Sensor_Event(sensors_event_t *a, sensors_event_t *g, sensors_event_t *temp)
{
    if(mpu.getEvent(a, g, temp))
    {
        return 0;
    }
    else
    {
        return -1;
    }
}
