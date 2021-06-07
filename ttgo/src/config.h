#ifndef CONFIG_H
#define CONFIG_H

// => Hardware select
// #define LILYGO_WATCH_2019_WITH_TOUCH     // To use T-Watch2019 with touchscreen, please uncomment this line
// #define LILYGO_WATCH_2019_NO_TOUCH          // To use T-Watch2019 Not touchscreen , please uncomment this line
//#define LILYGO_WATCH_2020_V1             //To use T-Watch2020, please uncomment this line

#define LILYGO_WATCH_HAS_MOTOR       //Use Motor module 

// NOT SUPPORT ...
//// #define LILYGO_WATCH_BLOCK
// NOT SUPPORT ...

// => Function select
#define LILYGO_WATCH_LVGL                   //To use LVGL, you need to enable the macro LVGL

#include <LilyGoWatch.h>

#endif
