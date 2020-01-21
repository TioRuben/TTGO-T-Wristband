#include "mpu.hpp"
#include "quaternionFilters.hpp"

MPU9250 IMU;

bool mpuReady = false;

void initMPU()
{
  byte c = IMU.readByte(MPU9250_ADDRESS, WHO_AM_I_MPU9250);
  if (c == 0x71)
  {
    IMU.initMPU9250();
    IMU.initAK8963(IMU.magCalibration);
    mpuReady = true;
  }
}

void taskInitMPU(void *parameter)
{
  IMU.initMPU9250();
  mpuReady = true;
  vTaskDelete(NULL);
}

void mpuSleep()
{
  IMU.setSleepEnabled(true);
}

int16_t getBearing()
{
  if (mpuReady && IMU.readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01)
  {
    IMU.readAccelData(IMU.accelCount); // Read the x/y/z adc values
    IMU.getAres();
    IMU.ax = (float)IMU.accelCount[0] * IMU.aRes; // - accelBias[0];
    IMU.ay = (float)IMU.accelCount[1] * IMU.aRes; // - accelBias[1];
    IMU.az = (float)IMU.accelCount[2] * IMU.aRes; // - accelBias[2];
    IMU.readGyroData(IMU.gyroCount);              // Read the x/y/z adc values
    IMU.getGres();
    IMU.gx = (float)IMU.gyroCount[0] * IMU.gRes;
    IMU.gy = (float)IMU.gyroCount[1] * IMU.gRes;
    IMU.gz = (float)IMU.gyroCount[2] * IMU.gRes;
    IMU.readMagData(IMU.magCount); // Read the x/y/z adc values
    IMU.getMres();
    IMU.magbias[0] = +470.;
    IMU.magbias[1] = +120.;
    IMU.magbias[2] = +125.;
    IMU.mx = (float)IMU.magCount[0] * IMU.mRes * IMU.magCalibration[0] -
             IMU.magbias[0];
    IMU.my = (float)IMU.magCount[1] * IMU.mRes * IMU.magCalibration[1] -
             IMU.magbias[1];
    IMU.mz = (float)IMU.magCount[2] * IMU.mRes * IMU.magCalibration[2] -
             IMU.magbias[2];
    IMU.updateTime();
    MahonyQuaternionUpdate(IMU.ax, IMU.ay, IMU.az, IMU.gx * DEG_TO_RAD,
                           IMU.gy * DEG_TO_RAD, IMU.gz * DEG_TO_RAD, IMU.my,
                           IMU.mx, IMU.mz, IMU.deltat);
    IMU.delt_t = millis() - IMU.count;
    if (IMU.delt_t > 20)
    {
      IMU.yaw = atan2(2.0f * (*(getQ() + 1) * *(getQ() + 2) + *getQ() *
                                                                  *(getQ() + 3)),
                      *getQ() * *getQ() + *(getQ() + 1) * *(getQ() + 1) - *(getQ() + 2) * *(getQ() + 2) - *(getQ() + 3) * *(getQ() + 3));
      IMU.pitch = -asin(2.0f * (*(getQ() + 1) * *(getQ() + 3) - *getQ() *
                                                                    *(getQ() + 2)));
      IMU.roll = atan2(2.0f * (*getQ() * *(getQ() + 1) + *(getQ() + 2) *
                                                             *(getQ() + 3)),
                       *getQ() * *getQ() - *(getQ() + 1) * *(getQ() + 1) - *(getQ() + 2) * *(getQ() + 2) + *(getQ() + 3) * *(getQ() + 3));
      IMU.pitch *= RAD_TO_DEG;
      IMU.yaw *= RAD_TO_DEG;
      IMU.roll *= RAD_TO_DEG;
      IMU.count = millis();
      IMU.sumCount = 0;
      IMU.sum = 0;
      return IMU.roll;
    }
    else
    {
      return -1;
    }
  }
  else
  {
    return -1;
  }
}

int calibrateBearing()
{
  return 1;
}
