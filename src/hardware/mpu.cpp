#include "mpu.hpp"

MPU9250 MPU(Wire, MPU_ADDR);

bool mpuReady = false;

void initMPU()
{
  xTaskCreate(taskInitMPU, "taskInitIMU", 1500, NULL, tskIDLE_PRIORITY, NULL);
}

void taskInitMPU(void *parameter)
{
  MPU.begin();
  MPU.enableDataReadyInterrupt();
  mpuReady = true;
  vTaskDelete(NULL);
}

void mpuSleep()
{
  pinMode(IMU_INT_PIN, INPUT_PULLUP);
  MPU.enableWakeOnMotion(400, MPU9250::LP_ACCEL_ODR_31_25HZ);
}

int16_t getBearing()
{
  if (mpuReady)
  {
    const float R2D = 180.0f / PI;
    MPU.readSensor();
    float ax = MPU.getAccelY_mss(); //MPU.getAccelX_mss();
    float ay = MPU.getAccelZ_mss(); //MPU.getAccelY_mss();
    float az = MPU.getAccelX_mss(); //MPU.getAccelZ_mss();
    float hx = MPU.getMagY_uT();    //MPU.getMagX_uT();
    float hy = MPU.getMagZ_uT();    //MPU.getMagY_uT();
    float hz = MPU.getMagX_uT();    //MPU.getMagZ_uT();
    float a = sqrtf(ax * ax + ay * ay + az * az);
    ax /= a;
    ay /= a;
    az /= a;
    float h = sqrtf(hx * hx + hy * hy + hz * hz);
    hx /= h;
    hy /= h;
    hz /= h;
    float pitch_rad = asinf(ax);
    float roll_rad = asinf(-ay / cosf(pitch_rad));
    float yaw_rad = atan2f(hz * sinf(roll_rad) - hy * cosf(roll_rad), hx * cosf(pitch_rad) + hy * sinf(pitch_rad) * sinf(roll_rad) + hz * sinf(pitch_rad) * cosf(roll_rad));
    float heading_rad = constrainAngle360(yaw_rad);
    return round(heading_rad * R2D);
  }
  else
  {
    return -1;
  }
}

float constrainAngle360(float dta)
{
  dta = fmod(dta, 2.0 * PI);
  if (dta < 0.0)
    dta += 2.0 * PI;
  return dta;
}

int calibrateBearing()
{
  return MPU.calibrateMag();
}

void calibrateAccel()
{
  MPU.calibrateAccel();
}

void calibrateGyro()
{
  MPU.calibrateGyro();
}