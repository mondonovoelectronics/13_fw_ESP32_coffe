/*
  Clock example example (Extended class example)
  Display a clock on the display. For this demo you can add a speed multiplier to make the clock run faster. For a real clock you want to use a delay of 1 min or even use a Real Time Clock module (RTC)
  The circuit:
  * connect TM1637 pin CLK to Arduino pin 13
  * connect TM1637 pin DIO to Arduino pin 12
  * connect TM1637 pin Vcc to Arduino pin 5V
  * connect TM1637 pin GND to Arduino pin GND
  Created 25 September 2015
  By Bram Harmsen
  https://github.com/bremme/arduino-tm1637
*/
// include the SevenSegmentTM1637 library
#include "SevenSegmentTM1637.h"
#include "SevenSegmentExtended.h"
#include "moka_vapo.h"

/* initialize global TM1637 Display object
*  The constructor takes two arguments, the number of the clock pin and the digital output pin:
* SevenSegmentTM1637(byte pinCLK, byte pinDIO);
*/
const byte PIN_CLK = 13;   // define CLK pin (any digital pin)
const byte PIN_DIO = 12;   // define DIO pin (any digital pin)
SevenSegmentExtended      display(PIN_CLK, PIN_DIO);

const unsigned int clockSpeed = 10000;    // speed up clock for demo

volatile int interruptCounter;
byte seconds, minutes, hours;

hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  interruptCounter++;
  portEXIT_CRITICAL_ISR(&timerMux);
}


// run setup code
void moka_display_setup_1() {
  hours=7;
  minutes=59;
  //seconds=45;  //credo si possa omettere perchè non è visualizzato a display

  display.begin();            // initializes the display
  display.setBacklight(100);  // set the brightness to 100 %
  Serial.print("setup...");
  display.printTime(hours, minutes, true);
  delay(10000); //aspetto 10 sec prima di far scattare le 08:00
}
void moka_display_setup_2() {   //ho diviso il setup in 2 parti per eseguire la seconda parte dopo il setup
                                // SD perchè questo comportava un piccolo malfunzionamento nei timer. 
  hours=8;
  minutes=0;
  seconds=0;
  display.printTime(hours, minutes, true);
    
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1000000, true);
  timerAlarmEnable(timer);
};

// run loop (forever)
void moka_display_loop() {
  if (interruptCounter > 0) {
 
    portENTER_CRITICAL(&timerMux);
    interruptCounter--;
    portEXIT_CRITICAL(&timerMux);

    if (vapo_button){    //timer che tiene premuto il pulsante vapo per accenderlo o spegnerlo (1 sec credo vada bene).
      Serial.println(vapo_button);
      vapo_button--;
      Serial.println(vapo_button);
    }
    seconds++;
    if (seconds>=60){
      minutes++;
      seconds=0;
      if (minutes>=60){
        hours++;
        minutes=0;
        if (hours>=24){
          hours=0;
        }
      }
      display.printTime(hours, minutes, true);
    }
    Serial.print("H: ");
    Serial.print(hours);
    Serial.print("        m: ");
    Serial.print(minutes);
    Serial.print("        s: ");
    Serial.println(seconds);
  }
};
