#define vapo_pin 27
#define delay_vapo 5000


int vapo_button; //decremento timer gestito in moka_display insieme all'orario.
int vapo_flag;
bool status_precedente;
//void button_moka_vapo(){
//  vapo_button=10;
//}
void button_moka_vapo(bool status_nuovo){
  //static bool status_precedente=0;
  if (status_nuovo!=status_precedente){
    status_precedente = status_nuovo;
    vapo_button = 5; // fa partire il timer che tiene alta l'uscita che pilota il transistor parallelato al pulsante del vapo
                    // in modo da accendere e spegnere il vapo
//    Serial.print("vapo_button:  "); 
//    Serial.println(vapo_button);
    vapo_flag = 1;
  }
}
void moka_vapo_setup(){
  pinMode(vapo_pin, OUTPUT);
}
void moka_vapo_loop(){
//  if (vapo_button){
//    digitalWrite(vapo_pin, HIGH);
//  }
//  else {
//    digitalWrite(vapo_pin, LOW);
//  }
if (vapo_flag){
    digitalWrite(vapo_pin, HIGH);
    delay(300);
    digitalWrite(vapo_pin, LOW);
    vapo_flag=0;
  }
}


//----------
