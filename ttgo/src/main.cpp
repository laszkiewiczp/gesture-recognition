#include <Arduino.h>
#include <LilyGoWatch.h>
#include "config.h"
#include "accelerometer.h"
#include "findGesture.h"
#include <EEPROM.h>
#include <BluetoothSerial.h>
#include <FS.h>
#include <SPIFFS.h>
#include <stdio.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define EEPROM_SIZE 7

BluetoothSerial SerialBT;

void doubleClickCallback(void);
boolean averageAccBelowThresh(Accel*, int);

int acc_counter=-1;
unsigned long t0;
TTGOClass *ttgo;

#define MIN_MEASUREMENTS 50
#define MAX_MEASUREMENTS 125
#define ACC_SAMPLING_TIME 20
#define ACC_THRESHOLD_UP 1040
#define ACC_THRESHOLD_DOWN 1010

unsigned long oldT;
boolean stop_record = 0;

unsigned long timestamps[MAX_MEASUREMENTS];
Accel accelerometerData[MAX_MEASUREMENTS];

void setup() {
  Serial.begin(115200);
  SPIFFS.begin();
  SerialBT.begin("TTGo Watch");
  ttgo = TTGOClass::getWatch();
  ttgo->begin();
  ttgo->openBL();
  ttgo->motor_begin();
  EEPROM.begin(EEPROM_SIZE);
  setup_Accelerometer(ttgo->bma);
  setDoubleClickCallback(doubleClickCallback);
}

void loop() {
  Accel acc=getCalibratedAccel();
  /*#ifdef ACC_DEBUG
    Serial.print(acc.x); Serial.print("\t");
    Serial.print(acc.y); Serial.print("\t");
    Serial.print(acc.z); Serial.println();
  #endif*/
  process_Accelerometer_IRQ();
  if ((acc_counter>=0)&&(acc_counter<MAX_MEASUREMENTS)&&(!(stop_record)))
  {
    unsigned long T=millis();
    if ((T-oldT)>=ACC_SAMPLING_TIME)
    {
      timestamps[acc_counter]=T-t0;
      accelerometerData[acc_counter].x=acc.x;
      accelerometerData[acc_counter].y=acc.y;
      accelerometerData[acc_counter].z=acc.z;
      acc_counter++;
      oldT=T;
    }
    if (acc_counter >= MIN_MEASUREMENTS)
    {
      stop_record = averageAccBelowThresh(accelerometerData, acc_counter);
    }
  }
  else if ((acc_counter>=MAX_MEASUREMENTS) || (stop_record))
  {
    ttgo->motor->onec();
    delay(200);
    //SerialBT.println(acc_counter);
    //Transmit all data now

    double acceleration[acc_counter][3];
    int result;
    
    for (int i=0;i<acc_counter;i++)
    {
      //SerialBT.print(timestamps[i]); SerialBT.print("\t");
      //SerialBT.print(accData[i].x); SerialBT.print("\t");
      //SerialBT.print(accData[i].y); SerialBT.print("\t");
      //SerialBT.print(accData[i].z); SerialBT.println();

      acceleration[i][0] = accelerometerData[i].x;
      acceleration[i][1] = accelerometerData[i].y;
      acceleration[i][2] = accelerometerData[i].z;
    }

    result = findGesture(acceleration, acc_counter);

    SerialBT.print(result);
    
    acc_counter=-1;
    stop_record = 0;
  }
}

void doubleClickCallback(void)
{
  #ifdef ACC_DEBUG
  Serial.println("doubleClick");
  #endif
  if (acc_counter==-1)
  {
    ttgo->motor->onec();
    delay(200);
    //SerialBT.println("----------------");
    acc_counter=0;
    t0=millis();
    oldT=t0;
  }
}


boolean averageAccBelowThresh(Accel accData[MAX_MEASUREMENTS], int acc_counter)
{
  int number_samples = 30;
  double average_acc = 0;

  for (int i=0;i<number_samples;i++)
  {
    average_acc += sqrt(sq((double)accData[acc_counter - i].x) + sq((double)accData[acc_counter - i].y) + sq((double)accData[acc_counter - i].z));
  }

  average_acc /= number_samples;

  return ((average_acc < ACC_THRESHOLD_UP) && (average_acc > ACC_THRESHOLD_DOWN));
} 