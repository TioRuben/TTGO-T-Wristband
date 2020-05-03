#include "mpu.hpp"
#include "quaternionFilters.hpp"

MPU9250 IMU;

void initMPU()
{
  byte c = IMU.readByte(MPU9250_ADDRESS, WHO_AM_I_MPU9250);
  if (c == 0x71)
  {
    IMU.initMPU9250();
    IMU.initAK8963(IMU.magCalibration);
    getMagBiasEEPROM(IMU.magbias);
  }
}

void mpuSleep()
{
  IMU.writeBit(MPU9250_ADDRESS, PWR_MGMT_1, 5, false);
  IMU.writeBit(MPU9250_ADDRESS, PWR_MGMT_1, 6, false);
  IMU.writeBit(MPU9250_ADDRESS, PWR_MGMT_1, 4, false);
  IMU.writeByte(MPU9250_ADDRESS, PWR_MGMT_2, 0x07);
  IMU.writeByte(MPU9250_ADDRESS, ACCEL_CONFIG2, 0x09);
  IMU.writeByte(MPU9250_ADDRESS, INT_ENABLE, 0x40);
  IMU.writeBit(MPU9250_ADDRESS, MOT_DETECT_CTRL, 7, true);
  IMU.writeBit(MPU9250_ADDRESS, MOT_DETECT_CTRL, 6, true);
  IMU.writeByte(MPU9250_ADDRESS, WOM_THR, 220);
  IMU.writeBit(MPU9250_ADDRESS, INT_PIN_CFG, 5, 0);
  IMU.writeByte(MPU9250_ADDRESS, INT_STATUS, 0);
  IMU.writeByte(MPU9250_ADDRESS, LP_ACCEL_ODR, 0x01);
  IMU.writeBit(MPU9250_ADDRESS, PWR_MGMT_1, 5, true);
}

int16_t getBearing()
{
  IMU.readMagData(IMU.magCount); // Read the x/y/z adc values
  IMU.getMres();
  IMU.mx = (float)IMU.magCount[0] * IMU.mRes * IMU.magCalibration[0] -
           IMU.magbias[0];
  IMU.my = (float)IMU.magCount[1] * IMU.mRes * IMU.magCalibration[1] -
           IMU.magbias[1];
  IMU.mz = (float)IMU.magCount[2] * IMU.mRes * IMU.magCalibration[2] -
           IMU.magbias[2];
  float bearing = atan2(IMU.my, IMU.mx);
  return (bearing > 0 ? bearing : (2 * PI + bearing)) * 360 / (2 * PI);
}

int calibrateBearing()
{
  uint16_t ii = 0, sample_count = 1500;
  int32_t mag_bias[3] = {0, 0, 0};
  int16_t mag_max[3] = {-32767, -32767, -32767}, mag_min[3] = {32767, 32767, 32767}, mag_temp[3] = {0, 0, 0};
  sleep(4);
  for (ii = 0; ii < sample_count; ii++)
  {
    IMU.readMagData(mag_temp); // Read the mag data
    for (int jj = 0; jj < 3; jj++)
    {
      if (mag_temp[jj] > mag_max[jj])
        mag_max[jj] = mag_temp[jj];
      if (mag_temp[jj] < mag_min[jj])
        mag_min[jj] = mag_temp[jj];
    }
    delay(12);                                                              // at 100 Hz ODR, new mag data is available every 10 ms
    mag_bias[0] = (mag_max[0] + mag_min[0]) / 2;                            // get average x mag bias in counts
    mag_bias[1] = (mag_max[1] + mag_min[1]) / 2;                            // get average y mag bias in counts
    mag_bias[2] = (mag_max[2] + mag_min[2]) / 2;                            // get average z mag bias in counts
    IMU.magbias[0] = (float)mag_bias[0] * IMU.mRes * IMU.magCalibration[0]; // save mag biases in G for main program
    IMU.magbias[1] = (float)mag_bias[1] * IMU.mRes * IMU.magCalibration[1];
    IMU.magbias[2] = (float)mag_bias[2] * IMU.mRes * IMU.magCalibration[2];
  }
  storeMagBiasEEPROM(IMU.magbias);
  return 1;
}

float getTemperature()
{
  int tempCount = IMU.readTempData();
  float temperature = ((float)tempCount) / 333.87 + 21.0;
  return temperature;
}

// Based on example code by Kris Winer at https://github.com/kriswiner/MPU9250/issues/162#issuecomment-336604802
void mpuDeepSleep()
{
  IMU.writeByte(MPU9250_ADDRESS, PWR_MGMT_1, IMU.readByte(MPU9250_ADDRESS, PWR_MGMT_1) | 0x40); // set sleep mode bit(6), disable all sensors
  delay(100); // wait for all registers to reset
  IMU.writeByte(AK8963_ADDRESS, AK8963_CNTL, IMU.readByte(AK8963_ADDRESS, AK8963_CNTL) & ~(0x0F) ); // clear bits 0 to 3 to power down magnetometer
  IMU.writeByte(MPU9250_ADDRESS, PWR_MGMT_1, IMU.readByte(MPU9250_ADDRESS, PWR_MGMT_1) | 0x10); // write bit 4 to enable gyro standby
  delay(10); // wait for all registers to reset
}
