#include <LiquidCrystal.h>
#include <SR501.h>

#define PIR_PIN 2
#define LED_PIN 7
#define BUZZER_PIN 3

bool state = false;
LiquidCrystal lcd (12, 11, 5, 4, 3, 2);

void setup(){
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  lcd.begin(16,2);
}

void loop(){
  if(digitalRead(PIR_PIN) == HIGH){
    if(!state){
      state = true;
    }
    lcd.setCursor(0,0);
    lcd.print("È scattato l'allarme");
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, millis()%1000+200);
  }
  else{
if(state){
      lcd.setCursor (0,0);
      lcd.print ("È tutto apposto");
      digitalWrite(LED_PIN, LOW);
      noTone(BUZZER_PIN);
      state = false;
    }
  }
  delay(10);
}