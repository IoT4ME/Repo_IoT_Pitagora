#include <dht_nonblocking.h>    
#include <LiquidCrystal.h>

#define DHT_SENSOR_TYPE DHT_TYPE_11
#define PIN_RED 12
#define PIN_GREEN 13

static const int DHT_SENSOR_PIN = 7;

DHT_nonblocking dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() 
{
  pinMode(PIN_GREEN,OUTPUT);
  pinMode(PIN_RED,OUTPUT);
  lcd.begin(16, 2);
  
Serial.begin(115200);
}

static bool measure_environment( float *temperature, float *humidity)
{
    static unsigned long measurement_timestamp = millis( );

  if( millis( ) - measurement_timestamp > 3000ul )
  {
    if( dht_sensor.measure( temperature, humidity ) == true )
    {
      measurement_timestamp = millis( );
      return( true );
    }
  }

return(false);
}

void loop() 
{
 float temperature;
 float humidity;
 if(measure_environment( &temperature, &humidity ) == true)
  {
    Serial.print("Temperatura: " );
    Serial.print(temperature, 1 );
    Serial.print("C");
    lcd.setCursor(0,0);
    lcd.print("Temp: ");
    lcd.print(temperature, 1);
    lcd.print("C");
    Serial.println("Umidità: ");
    Serial.print(humidity, 1 );
    Serial.println("%");
    lcd.setCursor(0,1);
    lcd.print("Umid: " );
    lcd.print(humidity, 1 );
    lcd.print("%");
   
  }
 
  if (temperature >= 30.0 && humidity == 8.0)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("La temperaratura è troppo alta");
    lcd.setCursor(0,1);
    lcd.print("L'umidità è giusta");
    digitalWrite (PIN_RED,HIGH);
  }
  
  else if (temperarature <= 25 || humidity >= 10.0 )
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("La temperaratura è giusta");
    lcd.setCursor(0,1);
    lcd.print("L'umidità è alta");
    digitalWrite (PIN_GREEN,HIGH);
  } 
}