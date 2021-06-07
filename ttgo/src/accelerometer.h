#ifndef ACC_H
#define ACC_H

#include "config.h"

//#define ACC_DEBUG
//#define ACC_USE_STEPCOUNTER
//#define ACC_USE_TILT
#define ACC_USE_DOUBLECLICK

#define ACC_MAX_MEASUREMENTS 1000

#define EEPROM_ACC_BASE 0
#define EEPROM_ACC_X  1
#define EEPROM_ACC_Y  3
#define EEPROM_ACC_Z  5

typedef void (*tilt_callback_function)(void); // type for conciseness
typedef void (*stepcount_callback_function)(int); // type for conciseness
typedef void (*doubleclick_callback_function)(void); // type for conciseness

void setup_Accelerometer(BMA *sensor);
#if defined(ACC_USE_STEPCOUNTER)||defined(ACC_USE_TILT)||defined(ACC_USE_DOUBLECLICK)
void process_Accelerometer_IRQ();
#endif
#ifdef ACC_USE_STEPCOUNTER
void setStepCounterCallback(stepcount_callback_function callback);
#endif

#ifdef ACC_USE_TILT
void setTiltCallback(tilt_callback_function callback);
#endif

#ifdef ACC_USE_DOUBLECLICK
void setDoubleClickCallback(doubleclick_callback_function callback);
#endif
Accel getAccel();
Accel getCalibratedAccel();
void calibrateAccel();
//bool readCalibratedAccelBaseline(Accel *baseline);

#endif
