
#include <Arduino.h>
#include "main.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include "Interface_Accelerometre.h"





int Get_Sensor_Acc(float *AccX, float *AccY, float *AccZ);
int Get_Sensor_Gyro(float *GyroX, float *GyroY, float *GyroZ);
void calculate_IMU_error();

float AccX1 = 0;
float AccY1 = 0;
float AccZ1 = 0;

float accAngleX1 = 0;
float accAngleY1 = 0;

float GyroX1 = 0;
float GyroY1 = 0;
float GyroZ1 = 0;

float yaw1 = 0;

float gyroAngleX1 = 0;
float gyroAngleY1 = 0;
float gyroAngleZ1 = 0;


float roll1 = 0;
float pitch1 = 0;



typedef struct 
{
  float AccErrorX;
  float AccErrorY;
  float GyroErrorX;
  float GyroErrorY;
  float GyroErrorZ;

}Interface_Accelerometre;

Interface_Accelerometre interface_Accelerometre_Struct;

TwoWire I2C = TwoWire(0);
Adafruit_MPU6050 mpu;


int interface_Accelerometre_initialise(void)
{
  // interface_Accelerometre_Struct.AccErrorX = 0;
  // interface_Accelerometre_Struct.AccErrorY = 0;
  // interface_Accelerometre_Struct.GyroErrorX = 0;
  // interface_Accelerometre_Struct.GyroErrorY = 0;
  // interface_Accelerometre_Struct.GyroErrorZ = 0;
   I2C.begin(I2C_SDA, I2C_SCL, 400000);

  // I2C.begin();                      // Initialize comunication
  // I2C.beginTransmission(ADDRESSE);       // Start communication with MPU6050 // MPU=0x68
  // I2C.write(0x6B);                  // Talk to the register 6B
  // I2C.write(0x00);                  // Make reset - place a 0 into the 6B register
  // I2C.endTransmission(true);        //end the transmission
  if (!mpu.begin(ADDRESSE, &I2C, 0)) 
  {
    Serial.println("Failed to find MPU6050 chip");
    return -1;
  }

    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

    //calculate_IMU_error();

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





int interface_Accelerometre_Accelerometre(float *accAngleX, float *accAngleY)
{
  I2C.beginTransmission(ADDRESSE);
  I2C.write(0x3B);
  I2C.endTransmission(false);
  I2C.requestFrom(ADDRESSE, 6, true);
  float AccX = (I2C.read() << 8 | I2C.read()) / 16384.0;
  float AccY = (I2C.read() << 8 | I2C.read()) / 16384.0;
  float AccZ = (I2C.read() << 8 | I2C.read()) / 16384.0;

  *accAngleX = (atan(AccY / sqrt(pow(AccX, 2) + pow(AccZ, 2))) * 180 / PI) - 0.58; // AccErrorX ~(0.58) See the calculate_IMU_error()custom function for more details
  *accAngleY = (atan(-1 * AccX / sqrt(pow(AccY, 2) + pow(AccZ, 2))) * 180 / PI) + 1.58; // AccErrorY ~(-1.58)
  return 0;
}


int interface_Accelerometre__Gyroscope(float *GyroX, float *GyroY, float *GyroZ)
{
  I2C.beginTransmission(ADDRESSE);
  I2C.write(0x43);
  I2C.endTransmission(false);
  I2C.requestFrom(ADDRESSE, 6, true);
  *GyroX = (I2C.read() << 8 | I2C.read()) / 131.0;
  *GyroY = (I2C.read() << 8 | I2C.read()) / 131.0;
  *GyroZ = (I2C.read() << 8 | I2C.read()) / 131.0;


  *GyroX = (*GyroX) + 0.56;  // GyroErrorX ~(-0.56)
  *GyroY = (*GyroY) - 2;  // GyroErrorY ~(2)
  *GyroZ = (*GyroZ) + 0.8;  // GyroErrorZ ~ (-0.8)
  return 0;
}


int interface_Accelerometre_Rotation()
{
  // I2C.beginTransmission(ADDRESSE);
  // I2C.write(0x3B);
  // I2C.endTransmission(false);
  // I2C.requestFrom(ADDRESSE, 6, true);
  // AccX1 = (I2C.read() << 8 | I2C.read()) / 16384.0;
  // AccY1 = (I2C.read() << 8 | I2C.read()) / 16384.0;
  // AccZ1 = (I2C.read() << 8 | I2C.read()) / 16384.0;

  
  


  // accAngleX1 = (atan(AccY1 / sqrt(pow(AccX1, 2) + pow(AccZ1, 2))) * 180 / PI) - 0.58; // AccErrorX ~(0.58) See the calculate_IMU_error()custom function for more details
  // accAngleY1 = (atan(-1 * AccX1 / sqrt(pow(AccY1, 2) + pow(AccZ1, 2))) * 180 / PI) + 1.58; // AccErrorY ~(-1.58)


  // // previousTime = currentTime;        // Previous time is stored before the actual time read
  // // currentTime = millis();            // Current time actual time read
  // // elapsedTime = (currentTime - previousTime) / 1000; // Divide by 1000 to get seconds


  // I2C.beginTransmission(ADDRESSE);
  // I2C.write(0x43);
  // I2C.endTransmission(false);
  // I2C.requestFrom(ADDRESSE, 6, true);
  // GyroX1 = (I2C.read() << 8 | I2C.read()) / 131.0;
  // GyroY1 = (I2C.read() << 8 | I2C.read()) / 131.0;
  // GyroZ1 = (I2C.read() << 8 | I2C.read()) / 131.0;


  // GyroX1 = (GyroX1) + 0.56;  // GyroErrorX ~(-0.56)
  // GyroY1 = (GyroY1) - 2;  // GyroErrorY ~(2)
  // GyroZ1 = (GyroZ1) + 0.8;  // GyroErrorZ ~ (-0.8)



  // Serial.print(GyroX1);
  // Serial.print("/");
  // Serial.print(GyroY1);
  // Serial.print("/");
  // Serial.println(GyroZ1);


  // gyroAngleX1 = gyroAngleX1 + GyroX1 * elapsedTime; // deg/s * s = deg
  // gyroAngleY1 = gyroAngleY1 + GyroY1 * elapsedTime;
  // yaw1 =  yaw1 + gyroAngleZ1 * elapsedTime;


  // roll1 = 0.96 * gyroAngleX1 + 0.04 * accAngleX1;
  // pitch1 = 0.96 * gyroAngleY1 + 0.04 * accAngleY1;
  
  // Print the values on the serial monitor
  // Serial.print(roll1);
  // Serial.print("/");
  // Serial.print(pitch1);
  // Serial.print("/");
  // Serial.println(yaw1);


  return 0;
}















int Get_Sensor_Acc(float *AccX, float *AccY, float *AccZ)
{
    I2C.beginTransmission(ADDRESSE);
    I2C.write(0x3B);
    I2C.endTransmission(false);
    I2C.requestFrom(ADDRESSE, 6, true);
    *AccX = (I2C.read() << 8 | I2C.read()) / 16384.0 ;
    *AccY = (I2C.read() << 8 | I2C.read()) / 16384.0 ;
    *AccZ = (I2C.read() << 8 | I2C.read()) / 16384.0 ;

    return 0;
}



int Get_Sensor_Gyro(float *GyroX, float *GyroY, float *GyroZ)
{
    I2C.beginTransmission(ADDRESSE);
    I2C.write(0x43);
    I2C.endTransmission(false);
    I2C.requestFrom(ADDRESSE, 6, true);
    *GyroX = (I2C.read() << 8 | I2C.read());
    *GyroY = (I2C.read() << 8 | I2C.read());
    *GyroZ = (I2C.read() << 8 | I2C.read());


      

    return 0;
}




void calculate_IMU_error() {
  // We can call this funtion in the setup section to calculate the accelerometer and gyro data error. From here we will get the error values used in the above equations printed on the Serial Monitor.
  // Note that we should place the IMU flat in order to get the proper values, so that we then can the correct values
  // Read accelerometer values 200 times
  int c = 0;
  while (c < 200) {
    float AccX = 0;
    float AccY = 0;
    float AccZ = 0;
    Get_Sensor_Acc(&AccX, &AccY, &AccZ);
    // Sum all readings
    interface_Accelerometre_Struct.AccErrorX = interface_Accelerometre_Struct.AccErrorX + ((atan((AccY) / sqrt(pow((AccX), 2) + pow((AccZ), 2))) * 180 / PI));
    interface_Accelerometre_Struct.AccErrorY = interface_Accelerometre_Struct.AccErrorY + ((atan(-1 * (AccX) / sqrt(pow((AccY), 2) + pow((AccZ), 2))) * 180 / PI));
    c++;
  }
  //Divide the sum by 200 to get the error value
  interface_Accelerometre_Struct.AccErrorX = interface_Accelerometre_Struct.AccErrorX / 200;
  interface_Accelerometre_Struct.AccErrorY = interface_Accelerometre_Struct.AccErrorY / 200;
  c = 0;
  // Read gyro values 200 times
  while (c < 200) {
    float GyroX = 0;
    float GyroY = 0;
    float GyroZ = 0;
    Get_Sensor_Gyro(&GyroX, &GyroY, &GyroZ);
    // Sum all readings
    interface_Accelerometre_Struct.GyroErrorX = interface_Accelerometre_Struct.GyroErrorX + (GyroX / 131.0);
    interface_Accelerometre_Struct.GyroErrorY = interface_Accelerometre_Struct.GyroErrorY + (GyroY / 131.0);
    interface_Accelerometre_Struct.GyroErrorZ = interface_Accelerometre_Struct.GyroErrorZ + (GyroZ / 131.0);
    c++;
  }
  //Divide the sum by 200 to get the error value
  interface_Accelerometre_Struct.GyroErrorX = interface_Accelerometre_Struct.GyroErrorX / 200;
  interface_Accelerometre_Struct.GyroErrorY = interface_Accelerometre_Struct.GyroErrorY / 200;
  interface_Accelerometre_Struct.GyroErrorZ = interface_Accelerometre_Struct.GyroErrorZ / 200;
  // Print the error values on the Serial Monitor
  Serial.print("AccErrorX: ");
  Serial.println(interface_Accelerometre_Struct.AccErrorX);
  Serial.print("AccErrorY: ");
  Serial.println(interface_Accelerometre_Struct.AccErrorY);
  Serial.print("GyroErrorX: ");
  Serial.println(interface_Accelerometre_Struct.GyroErrorX);
  Serial.print("GyroErrorY: ");
  Serial.println(interface_Accelerometre_Struct.GyroErrorY);
  Serial.print("GyroErrorZ: ");
  Serial.println(interface_Accelerometre_Struct.GyroErrorZ);
}