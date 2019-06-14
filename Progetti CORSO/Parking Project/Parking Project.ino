#include <LiquidCrystal.h>
#include <SR04.h>

#define TRIG_PIN 9
#define ECHO_PIN 8
#define LED_RED 6
#define LED_GREEN 7

SR04 sensultr = SR04(ECHO_PIN,TRIG_PIN); 
LiquidCrystal lcd (12, 11, 5, 4, 3, 2);
long distanza;

void setup() {
pinMode(LED_RED, OUTPUT);
pinMode (LED_GREEN, OUTPUT);
lcd.begin(16,2);
Serial.begin (9600);
}

void loop() {

distanza = sensultr.Distance();
int pos;

for (pos=0; pos<29; pos++)
{
lcd.setCursor(0,0);
lcd.print("Parking: ");
lcd.setCursor(0,1);
lcd.print("Distanza: ");
lcd.setCursor(10,1);
lcd.print(distanza);
lcd.print(" cm");
Serial.print("Distanza: ");
Serial.print(distanza);
Serial.println(" cm");



if (distanza >= 20)
{
digitalWrite (LED_GREEN, HIGH);
digitalWrite (LED_RED,LOW);
lcd.setCursor(10,0);
lcd.print ("Free");
}
else 
{
digitalWrite (LED_RED, HIGH);
digitalWrite (LED_GREEN,LOW);
lcd.setCursor(10,0);
lcd.print ("Busy");
}
}
}