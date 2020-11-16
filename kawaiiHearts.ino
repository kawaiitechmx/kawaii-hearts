
// ATtiny85 sleep mode, wake on pin change interrupt or watchdog timer
// Author: Nick Gammon
// Date: 12 October 2013

// ATMEL ATTINY 25/45/85 / ARDUINO
//
//                  +-\/-+
// Ain0 (D 5) PB5  1|    |8  Vcc
// Ain3 (D 3) PB3  2|    |7  PB2 (D 2) Ain1
// Ain2 (D 4) PB4  3|    |6  PB1 (D 1) pwm1
//            GND  4|    |5  PB0 (D 0) pwm0
//                  +----+

#include <avr/sleep.h>    // Sleep Modes
#include <avr/power.h>    // Power management
#include <avr/wdt.h>      // Watchdog timer
#define CHARLIE_A 0
#define CHARLIE_B 1
#define CHARLIE_C 2
const byte LED = 1;  // pin 2
byte watchdog_counter = 0;
byte lastLED = 0;
byte randomLed = 0;
// watchdog interrupt
ISR (WDT_vect)
{
  watchdog_counter++;
  wdt_disable();  // disable watchdog
}  // end of WDT_vect

void resetWatchdog ()
 {
 // clear various "reset" flags
 MCUSR = 0;    
 // allow changes, disable reset, clear existing interrupt
 WDTCR = bit (WDCE) | bit (WDE) | bit (WDIF);
 // set interrupt mode and an interval (WDE must be changed from 1 to 0 here)
 //WDTCR = bit (WDIE) | bit (WDP2) | bit (WDP1) | bit (WDP0);    // set WDIE, and 2 seconds delay
 WDTCR = bit (WDIE); 
 //WDTCR |= (0<<WDP3) | (1<<WDP2) | (0<<WDP1) | (1<<WDP0);  //0.5 ms delay
 // pat the dog
 wdt_reset();  
 }  // end of resetWatchdog
 
void setup ()
 {
 resetWatchdog ();  // do this first in case WDT fires
 pinMode (LED, OUTPUT);
 pinMode(3, INPUT_PULLUP);
 pinMode(4, INPUT_PULLUP);
 pinMode(5, INPUT_PULLUP);
 pinMode(CHARLIE_A, OUTPUT);
 pinMode(CHARLIE_B, OUTPUT);
 pinMode(CHARLIE_C, OUTPUT);
 ADCSRA |= (1<<ADEN); //Enable ADC
 randomSeed (analogRead (0));    // randomize
 ADCSRA &= ~(1<<ADEN); //Disable ADC, saves ~230uA
 }  // end of setup

void loop ()
 {
 //digitalWrite (LED, HIGH);
 //delay (1);

 //goToSleep ();
 
 //digitalWrite (LED, LOW);

 randomLed = random (1,7);  
 randomLEDs(randomLed);
 goToSleep();  

 }  // end of loop
 
void goToSleep ()
 {
 set_sleep_mode (SLEEP_MODE_PWR_DOWN);
 ADCSRA = 0;            // turn off ADC
 power_all_disable ();  // power off ADC, Timer 0 and 1, serial interface
 noInterrupts ();       // timed sequence coming up
 resetWatchdog ();      // get watchdog ready
 sleep_enable ();       // ready to sleep
 interrupts ();         // interrupts are required now
 sleep_cpu ();          // sleep                
 sleep_disable ();      // precaution
 //power_all_enable ();   // power everything back on
 }  // end of goToSleep



 void randomLEDs(int n)
{
//    pinMode(CHARLIE_A, OUTPUT); 
//    digitalWrite(CHARLIE_A, LOW);
//    pinMode(CHARLIE_B, OUTPUT); 
//    digitalWrite(CHARLIE_B, LOW);
//    pinMode(CHARLIE_C, OUTPUT); 
//    digitalWrite(CHARLIE_C, LOW);
//    
//
//    if(n==lastLED)
//    {
//      n = random(0, lastLED-1);
//    }
  switch(n)
   {
    case 1 :
       
       // LIGHT 1 
      //turn on LED L1
      pinMode(CHARLIE_A, OUTPUT);     //row 1
      digitalWrite(CHARLIE_A, LOW);
      pinMode(CHARLIE_B, OUTPUT);     //row 2
      digitalWrite(CHARLIE_B, HIGH);  
      pinMode(CHARLIE_C, INPUT);      //row 3
      digitalWrite(CHARLIE_C, LOW);
      
    break;
    case 2 :
    // LIGHT 2 
    //turn on LED L2
    pinMode(CHARLIE_A, OUTPUT);     //row 1
    digitalWrite(CHARLIE_A, HIGH);
    pinMode(CHARLIE_B, OUTPUT);     //row 2
    digitalWrite(CHARLIE_B, LOW);   
    pinMode(CHARLIE_C, INPUT);      //row 3
    digitalWrite(CHARLIE_C, LOW);
    
    break;
    case 3:
    // LIGHT 3
    pinMode(CHARLIE_A, INPUT);      //row 1
    digitalWrite(CHARLIE_A, LOW);
    pinMode(CHARLIE_B, OUTPUT);     //row 2
    digitalWrite(CHARLIE_B, LOW);  
    pinMode(CHARLIE_C, OUTPUT);     //row 3
    digitalWrite(CHARLIE_C, HIGH);
    
    break;
    case 4:
    // LIGHT 4 
    pinMode(CHARLIE_A, INPUT);     //row 1
    digitalWrite(CHARLIE_A, LOW);
    pinMode(CHARLIE_B, OUTPUT);    //row 2
    digitalWrite(CHARLIE_B, HIGH);  
    pinMode(CHARLIE_C, OUTPUT);    //row 3
    digitalWrite(CHARLIE_C, LOW);

    break;
    case 5:
    // LIGHT 5 
    pinMode(CHARLIE_A, OUTPUT);    //row 1
    digitalWrite(CHARLIE_A, LOW);
    pinMode(CHARLIE_B, INPUT);     //row 2
    digitalWrite(CHARLIE_B, LOW);
    pinMode(CHARLIE_C, OUTPUT);    //row3
    digitalWrite(CHARLIE_C, HIGH);
    
    break;
    case 6:
    // LIGHT 6 
    pinMode(CHARLIE_A, OUTPUT);
    digitalWrite(CHARLIE_A, HIGH);
    pinMode(CHARLIE_B, INPUT);
    digitalWrite(CHARLIE_B, LOW);
    pinMode(CHARLIE_C, OUTPUT);
    digitalWrite(CHARLIE_C, LOW);
    
    break;
//    default:
//     pinMode(CHARLIE_A, INPUT); 
//     pinMode(CHARLIE_B, INPUT); 
//     pinMode(CHARLIE_C, INPUT); 
   }

   //lastLED = n;
}
