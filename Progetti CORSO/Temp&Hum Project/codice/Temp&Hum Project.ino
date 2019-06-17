#include <dht_nonblocking.h>    
#include <LiquidCrystal.h>

#define DHT_SENSOR_TYPE DHT_TYPE_11
#define ventola 6

static const int DHT_SENSOR_PIN = 7;

DHT_nonblocking dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() 
{
  pinMode(ventola,OUTPUT);
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
 
  lcd.setCursor(0,0);
  lcd.print("Temp. ");
  lcd.setCursor(0,1);
  lcd.print("Umid. ");
  
 if(measure_environment( &temperature, &humidity ) == true)
  {
   lcd.setCursor(6,0);
   lcd.print(temperature,1);
   lcd.print("C");
   lcd.setCursor(6,1); 
   lcd.print(humidity,1);
   lcd.print("%");
  }

  if (temperature > 35.00)
  {
    digitalWrite(ventola,HIGH);
    lcd.setCursor(12,0);
    lcd.print ("HOT");
    if (humidity > 70.00)
    {
    lcd.setCursor(12,1);
    lcd.print ("+++");  
    }
  }

  if (temperature < 35.00)
  { 
    digitalWrite (ventola,LOW);
    lcd.setCursor(12,0);
    lcd.print("COOL");
    if (humidity < 10.00)
    {
    lcd.setCursor(12,1);
    lcd.print ("---");
    }