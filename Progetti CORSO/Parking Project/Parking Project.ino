#include <LiquidCrystal.h>
#include <SR04.h>

#define TRIG_PIN 8
#define ECHO_PIN 13
#define LED_RED 6
#define LED_GREEN 7

SR04 sensultr = SR04(ECHO_PIN,TRIG_PIN); 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
long distanza;

void setup() {
pinMode(LED_RED, OUTPUT);
pinMode (LED_GREEN, OUTPUT);
lcd.begin(16,2);
Serial.begin(115200);
}

void loop() {

distanza = sensultr.Distance();
Serial.print ("La distanza è: ");
Serial.print (distanza);
Serial.print (" cm ");

if (distanza >= 20)
{
digitalWrite (LED_GREEN, HIGH);
digitalWrite (LED_RED,LOW);
Serial.print ("Parking Free");
Serial.println ("Distance: ");
Serial.print (distanza);
Serial.print (" cm");
lcd.setCursor(0,0);
lcd.print ("Parking Free");
lcd.setCursor(0,1);
lcd.print("Distance: ");
lcd.print(distanza);
lcd.print (" cm");
}

else if (distanza <= 10)
{
digitalWrite (LED_RED, HIGH);
digitalWrite (LED_GREEN,LOW);
Serial.print ("Parking Busy");
Serial.println ("Distance: ");
Serial.print (distanza);
Serial.print (" cm");
lcd.setCursor(0,0);
lcd.print ("Parking Busy");
lcd.setCursor(0,1);
lcd.print("Distance: ");
lcd.print(distanza);
lcd.print (" cm");
}
delay (2000); 
}