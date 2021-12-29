/***************************************************
Demo per moka.
Questo sketch inizializza l'orario del display ad una prefissata impostabile da setup().
Dopo un tot di secondi prefissati da un delay fa scattare l'orario un minuto avanti e fa partire il vaporizzatore insieme 
allo speaker che suona il rumore della moka.
Per attivare il pulsante vapo utilizzare un MOS canale N
 ****************************************************/
#include"moka_SD.h"
#include"moka_display.h"
//#include"moka_vapo.h"
#include"moka_LED.h"

#define ON 1
#define OFF 0

extern byte hours;
void setup()
{
  Serial.begin(9600);
  moka_LED_setup();  
  moka_display_setup_1();
  moka_SD_setup();
  moka_vapo_setup();
  moka_display_setup_2();
  Serial.println("Setup ended"); 
  delay(1000);
}

void loop()
{
  moka_display_loop();
  tank_check();
  if(tank_status){
    if (hours==8){
      moka_SD_loop();
      //button_moka_vapo(delay_vapo);   //fa partire il vapo dopo delay_vapo secondi dall'inizio della riproduzione
      if ((minutes==0)&&(seconds<10)){
          button_moka_vapo(ON);
          LED_fading();
      }
      else{
        button_moka_vapo(OFF);
        LED_off();
      }
    }
  }
  else{
    LED_blinking();
    button_moka_vapo(OFF);
  }
  moka_vapo_loop();
}
