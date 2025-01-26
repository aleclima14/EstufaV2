/**
 * @file timer.cpp
 * @author aleclima14@gmail.com
 * @brief 
 * @version 0.1
 * @date 2024-06-15
 * 
 * @copyright Copyright (c) 2024
 * 
 */

/* INCLUDES */
#include <Arduino.h>
#include "timer.h"

/**
 * @brief Start the timer
 * 
 * @param timerPointer 
 */
void StartTimerMillis(ulong *timerPointer)
{
   *timerPointer = millis();
}

/**
 * @brief Start the timer
 * 
 * @param timerPointer 
 */
void StartTimerMicros(ulong *timerPointer)
{
   *timerPointer = micros();
}

/**
 * @brief Wait Millisecond
 * 
 * @param timerPointer <- pointer to the timer
 * @param delay <- waiting timer
 * @return true if the timer is over
 */
boolean ElapsedTimerMillis(ulong *timerPointer, ulong delay)
{
   boolean returnValue = false;

   if((millis() - *timerPointer) >= delay)
   {
      *timerPointer = millis();
      returnValue = true;
   }
   return returnValue;
}

/**
 * @brief Wait Microsecond
 * 
 * @param timerPointer <- pointer to the timer
 * @param delay <- waiting timer
 * @return true if the timer is over
 */
boolean ElapsedTimerMicros(ulong *timerPointer, ulong delay)
{
   boolean returnValue = false;

   if((micros() - *timerPointer) >= delay)
   {
      *timerPointer = micros();
      returnValue = true;
   }
   return returnValue;
}