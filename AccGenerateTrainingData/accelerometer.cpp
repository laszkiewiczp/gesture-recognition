#include "config.h"
#include "accelerometer.h"
#include <EEPROM.h>

bool acc_irq = false;
BMA* acc_sensor;

#ifdef ACC_USE_STEPCOUNTER
uint32_t stepCount = 0;
stepcount_callback_function stepCounterFunc;
#endif
#ifdef ACC_USE_TILT
uint32_t tiltCount = 0;
tilt_callback_function tiltCallbackFunc;
#endif
#ifdef ACC_USE_DOUBLECLICK
uint32_t doubleClickCount = 0;
doubleclick_callback_function doubleClickCallbackFunc;
#endif

Accel acc_baseline;

void setup_Accelerometer(BMA *sensor)
{
  acc_sensor=sensor;
  Acfg cfg;
    /*!
        Output data rate in Hz, Optional parameters:
            - BMA4_OUTPUT_DATA_RATE_0_78HZ
            - BMA4_OUTPUT_DATA_RATE_1_56HZ
            - BMA4_OUTPUT_DATA_RATE_3_12HZ
            - BMA4_OUTPUT_DATA_RATE_6_25HZ
            - BMA4_OUTPUT_DATA_RATE_12_5HZ
            - BMA4_OUTPUT_DATA_RATE_25HZ
            - BMA4_OUTPUT_DATA_RATE_50HZ
            - BMA4_OUTPUT_DATA_RATE_100HZ
            - BMA4_OUTPUT_DATA_RATE_200HZ
            - BMA4_OUTPUT_DATA_RATE_400HZ
            - BMA4_OUTPUT_DATA_RATE_800HZ
            - BMA4_OUTPUT_DATA_RATE_1600HZ
    */
    cfg.odr = BMA4_OUTPUT_DATA_RATE_100HZ;
    /*!
        G-range, Optional parameters:
            - BMA4_ACCEL_RANGE_2G
            - BMA4_ACCEL_RANGE_4G
            - BMA4_ACCEL_RANGE_8G
            - BMA4_ACCEL_RANGE_16G
    */
    cfg.range = BMA4_ACCEL_RANGE_2G;
    /*!
        Bandwidth parameter, determines filter configuration, Optional parameters:
            - BMA4_ACCEL_OSR4_AVG1
            - BMA4_ACCEL_OSR2_AVG2
            - BMA4_ACCEL_NORMAL_AVG4
            - BMA4_ACCEL_CIC_AVG8
            - BMA4_ACCEL_RES_AVG16
            - BMA4_ACCEL_RES_AVG32
            - BMA4_ACCEL_RES_AVG64
            - BMA4_ACCEL_RES_AVG128
    */
    cfg.bandwidth = BMA4_ACCEL_NORMAL_AVG4;

    /*! Filter performance mode , Optional parameters:
        - BMA4_CIC_AVG_MODE
        - BMA4_CONTINUOUS_MODE
    */
    cfg.perf_mode = BMA4_CONTINUOUS_MODE;

    // Configure the BMA423 accelerometer
    sensor->accelConfig(cfg);

    // Enable BMA423 accelerometer
    // Warning : Need to use feature, you must first enable the accelerometer
    // Warning : Need to use feature, you must first enable the accelerometer
    // Warning : Need to use feature, you must first enable the accelerometer
    sensor->enableAccel();

    pinMode(BMA423_INT1, INPUT);
    attachInterrupt(BMA423_INT1, [] {
        // Set interrupt to set irq value to 1
        acc_irq = true;
    }, RISING); //It must be a rising edge

    // Enable BMA423 isStepCounter feature
	#ifdef ACC_USE_STEPCOUNTER
    sensor->enableFeature(BMA423_STEP_CNTR, true);
	#endif
    // Enable BMA423 isTilt feature
	#ifdef ACC_USE_TILT
    sensor->enableFeature(BMA423_TILT, true);
	#endif
    // Enable BMA423 isDoubleClick feature
	#ifdef ACC_USE_DOUBLECLICK
    sensor->enableFeature(BMA423_WAKEUP, true);
	#endif

    // Reset steps
    #ifdef ACC_USE_STEPCOUNTER
		sensor->resetStepCounter();
    // Turn on feature interrupt
		sensor->enableStepCountInterrupt();
	#endif
	#ifdef ACC_USE_TILT
		sensor->enableTiltInterrupt();
	#endif
    // It corresponds to isDoubleClick interrupt
	#ifdef ACC_USE_DOUBLECLICK
		sensor->enableWakeupInterrupt();
	#endif

  if (EEPROM.read(EEPROM_ACC_BASE)==0)
  {
    //Sensor not calibrated. We use here some factory values
    #ifdef ACC_DEBUG
      Serial.println("Acceleration sensor not calibrated. Using factory values");
    #endif
    acc_baseline.x=-66;
    acc_baseline.y=10;
    acc_baseline.z=-1017;
  }
  else
  {
    acc_baseline.x=((int16_t)EEPROM.read(EEPROM_ACC_X)<<8)|((int16_t)EEPROM.read(EEPROM_ACC_X+1));
    acc_baseline.y=((int16_t)EEPROM.read(EEPROM_ACC_Y)<<8)|((int16_t)EEPROM.read(EEPROM_ACC_Y+1));
    acc_baseline.z=((int16_t)EEPROM.read(EEPROM_ACC_Z)<<8)|((int16_t)EEPROM.read(EEPROM_ACC_Z+1));
  }
}

#ifdef ACC_USE_STEPCOUNTER
void resetStepCounter()
{
  stepCount = 0;
}
#endif
#ifdef ACC_USE_TILT
void resetTiltCounter()
{
  tiltCount = 0;
}
#endif
#ifdef ACC_USE_DOUBLECLICK
void resetDoubleClickCounter()
{
  doubleClickCount = 0;
}
#endif

void process_Accelerometer_IRQ()
{
  if (acc_irq)
    {
      acc_irq=false;
      bool  rlst;
      do {
          // Read the BMA423 interrupt status,
          // need to wait for it to return to true before continuing
          rlst =  acc_sensor->readInterrupt();
      } while (!rlst);
      #ifdef ACC_USE_STEPCOUNTER
      if (acc_sensor->isStepCounter()) {
        stepCount = acc_sensor->getCounter();
        stepCounterCallbackFunc(stepCount);
        #ifdef ACC_DEBUG
          Serial.print("Step count: ");
          Serial.println(stepCount);
        #endif
      }
      #endif
      #ifdef ACC_USE_TILT
      if (acc_sensor->isTilt()) {
            ++tiltCount;
            tiltCallbackFunc();
            #ifdef ACC_DEBUG
              Serial.print("Tilt count: ");
              Serial.println(tiltCount);
            #endif
        }
      #endif
      #ifdef ACC_USE_DOUBLECLICK 
        // Double-click interrupt
        if (acc_sensor->isDoubleClick()) {
            ++doubleClickCount;
              doubleClickCallbackFunc();
            #ifdef ACC_DEBUG
              Serial.print("DoubleClick count: ");
              Serial.println(doubleClickCount);
            #endif
        }
      #endif
    }
    
}

#ifdef ACC_USE_STEPCOUNTER
void setStepCounterCallback(stepcount_callback_function callback)
{
  stepCounterCallbackFunc=callback;
}
#endif

#ifdef ACC_USE_TILT
void setTiltCallback(tilt_callback_function callback)
{
  tiltCallbackFunc=callback;
}
#endif

#ifdef ACC_USE_DOUBLECLICK
void setDoubleClickCallback(doubleclick_callback_function callback)
{
  doubleClickCallbackFunc=callback;
}
#endif

Accel getAccel()
{
  Accel acc;
  acc_sensor->getAccel(acc);
  return acc;
}

Accel getCalibratedAccel()
{
  Accel acc;
  acc_sensor->getAccel(acc);
  acc.x-=acc_baseline.x;
  acc.y-=acc_baseline.y;
  acc.z-=acc_baseline.z;
  return acc;
}

void calibrateAccel()
{
  #ifdef ACC_DEBUG
  Serial.println("Calibrating...");
  #endif
  double acc_x=0.0,acc_y=0.0,acc_z=0.0;

  for (int i=0;i<ACC_MAX_MEASUREMENTS;i++)
  {
    Accel acc=getAccel();
    acc_x+=(((double)acc.x)/ACC_MAX_MEASUREMENTS);
    acc_y+=(((double)acc.y)/ACC_MAX_MEASUREMENTS);
    acc_z+=(((double)acc.z)/ACC_MAX_MEASUREMENTS);
    delay(10); //This value has to be consistent with the sampling rate of the acc in its configuration
  }
  acc_baseline.x=(int16_t)acc_x;
  acc_baseline.y=(int16_t)acc_y;
  acc_baseline.z=(int16_t)acc_z; 
  EEPROM.write(EEPROM_ACC_BASE,1); //This means that has been calibrated
  EEPROM.write(EEPROM_ACC_X,highByte(acc_baseline.x));
  EEPROM.write(EEPROM_ACC_X+1,lowByte(acc_baseline.x));
  EEPROM.write(EEPROM_ACC_Y,highByte(acc_baseline.y));
  EEPROM.write(EEPROM_ACC_Y+1,lowByte(acc_baseline.y));
  EEPROM.write(EEPROM_ACC_Z,highByte(acc_baseline.z));
  EEPROM.write(EEPROM_ACC_Z+1,lowByte(acc_baseline.z));
  EEPROM.commit();
  #ifdef ACC_DEBUG
  Serial.println("Calibration done!");
  Serial.print(acc_baseline.x); Serial.print("\t");
  Serial.print(acc_baseline.y); Serial.print("\t");
  Serial.print(acc_baseline.z); Serial.println();
  #endif
}

/*bool readCalibratedAccelBaseline(Accel *baseline)
{
  #ifdef ACC_DEBUG
    Serial.println("Reading accelerometer calibrated data");
  #endif
  if (EEPROM.read(EEPROM_ACC_BASE)==0)
  {
    #ifdef ACC_DEBUG
      Serial.println("Accelerometer not calibrated. Please calibrate the accelorometer first");
    #endif
    return false;
  }
  baseline->x=((int16_t)EEPROM.read(EEPROM_ACC_X)<<8)|((int16_t)EEPROM.read(EEPROM_ACC_X+1));
  baseline->y=((int16_t)EEPROM.read(EEPROM_ACC_Y)<<8)|((int16_t)EEPROM.read(EEPROM_ACC_Y+1));
  baseline->z=((int16_t)EEPROM.read(EEPROM_ACC_Z)<<8)|((int16_t)EEPROM.read(EEPROM_ACC_Z+1));
  #ifdef ACC_DEBUG
  Serial.println("Calibration done!");
  Serial.print(baseline->x); Serial.print("\t");
  Serial.print(baseline->y); Serial.print("\t");
  Serial.print(baseline->z); Serial.println();
  #endif
  return true;
}*/
