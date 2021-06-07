#include "config.h"
#include "accelerometer.h"
#include <EEPROM.h>
#include <BluetoothSerial.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define EEPROM_SIZE 7

BluetoothSerial SerialBT;

void doubleClickCallback(void);

int acc_counter=-1;
unsigned long t0;
TTGOClass *ttgo;

#define MIN_MEASUREMENTS 50 /* minimum number of samples that have to be recorded */
#define MAX_MEASUREMENTS 125 /* maximum number of saples that may be recorded */
#define ACC_SAMPLING_TIME 20 /* sampling time interval */
#define ACC_THRESHOLD_UP 1040 /* upper value of average acceleration corresponding to not making a gesture */
#define ACC_THRESHOLD_DOWN 1010 /* lower value of average acceleration corresponding to not making a gesture */

unsigned long oldT;
boolean stop_record = 0; /* variable that stops recording acceleration when the subject is not performing gestures */

unsigned long timestamps[MAX_MEASUREMENTS];
Accel accData[MAX_MEASUREMENTS];

void setup() {
  Serial.begin(115200);
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
    if ((T-oldT)>=ACC_SAMPLING_TIME) /* start recording acceleration data every sampling time interval */
    {
      timestamps[acc_counter]=T-t0;
      accData[acc_counter].x=acc.x;
      accData[acc_counter].y=acc.y;
      accData[acc_counter].z=acc.z;
      acc_counter++;
      oldT=T;
    }
    if (acc_counter >= MIN_MEASUREMENTS) /* after the gesture recording time exceeds the minimum time, we start analysing if the subject is still performing the gesture */
    {
      stop_record = averageAccBelowThresh(accData, acc_counter);
    }
  }
  else if ((acc_counter>=MAX_MEASUREMENTS) || (stop_record)) /* stop recroding acceleration and send data if the time exceeded the upper limit or the gesture is finished */
  {
    ttgo->motor->onec(); /* run motor after the acceleration recording is finished */
    SerialBT.println(acc_counter); /* send data about the number of acceleration samples recorded, used by MATLAB script */
    //Transmit all data now
    for (int i=0;i<acc_counter;i++)
    {
      //SerialBT.print(timestamps[i]); SerialBT.print("\t");
      SerialBT.print(accData[i].x); SerialBT.print("\t");
      SerialBT.print(accData[i].y); SerialBT.print("\t");   /* transmitting acceleration data */
      SerialBT.print(accData[i].z); SerialBT.println();
    }
    acc_counter=-1;
    stop_record = 0;
  }
}

void doubleClickCallback(void) /* action for double click - run motor for 200 ms and start acc recording */
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


boolean averageAccBelowThresh(Accel accData[MAX_MEASUREMENTS], int acc_counter) /* function used to verify if the subject is still performing a gesture - returns true if the gesture is not being performed*/
{
  int number_samples = 30; /* number of samples from which the average acceleration is calculated */
  double average_acc = 0; /* variable to store average acceleration */

  for (int i=0;i<number_samples;i++)
  {
    average_acc += sqrt(sq((double)accData[acc_counter - i].x) + sq((double)accData[acc_counter - i].y) + sq((double)accData[acc_counter - i].z));
  }

  average_acc /= number_samples;

  return ((average_acc < ACC_THRESHOLD_UP) && (average_acc > ACC_THRESHOLD_DOWN)); /* returns TRUE if average acceleration is inside the range (ACC_THRESHOLD_UP; ACC_THRESHOLD_DOWN)*/
} 
