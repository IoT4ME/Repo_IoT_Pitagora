#include <dht_nonblocking.h>

#define DHT_SENSOR_TYPE DHT_TYPE_11
#define PIN_RED 12
#define PIN_GREEN 13

static const int DHT_SENSOR_PIN = 2;

DHT_nonblocking dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

void setup() {
  pinMode(PIN_GREEN,OUTPUT);
  pinMode(PIN_RED,OUTPUT);
  
Serial.begin(115200);
}

static bool measure_environment( loat *temperature, float *humidity)
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
    Serial.print( "Temperatura = " );
    Serial.print( temperature, 1 );
    Serial.print( " C, Umidità = " );
    Serial.print( humidity, 1 );
    Serial.println( "%" );
  }
  if ( temperature >= 30.0 )
  {
    digitalWrite (PIN_RED,HIGH);
  }
  else if ( humidity >= 7.0 )
  {
    digitalWrite (PIN_GREEN,HIGH);
  } 
}