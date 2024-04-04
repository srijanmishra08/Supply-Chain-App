//First install the following from Tools -> Manage Libraries
#include <DHT.h> 
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27,16,2); 
  
#define DHTPIN 7     
#define DHTTYPE DHT11   

DHT dht(DHTPIN, DHTTYPE); 

void setup()
{
    Serial.begin(9600);
    Serial.println("Temperature and Humidity Sensor Test");
    dht.begin();
    lcd.init(); 
    lcd.backlight();
}

void loop()
{
    // Wait a few seconds between measurements.
    delay(2000);
    
    float t = dht.readTemperature();
 
    float f = dht.readTemperature(true);

    float h = dht.readHumidity()-10;

    // Check if any reads failed and exit early (to try again)
    if (isnan(h) || isnan(t) || isnan(f)) 
    {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }
    
    // Compute heat index in Fahrenheit (the default)
    float hif = dht.computeHeatIndex(f, h);
    // Compute heat index in Celsius (isFahreheit = false)
    float hic = dht.computeHeatIndex(t, h, false);
  
    Serial.print(F(" Humidity: "));
    Serial.print(h);
    Serial.print(F("%  Temperature: "));
    Serial.print(t);
    Serial.print(F("C "));
    Serial.print(f);
    Serial.print(F("F  Heat index: "));
    Serial.print(hic);
    Serial.print(F("C "));
    Serial.print(hif);
    Serial.println(F("F"));
   
    lcd.setCursor(0, 0);
    lcd.println("SUPPLY CHAIN APP");
    
    lcd.setCursor(0, 1);
    lcd.print("T:");
    lcd.print(t);
    lcd.print("C");

    lcd.setCursor(6, 1);
    lcd.println("2023 ");
     
    lcd.setCursor(11, 1);
    lcd.print("H:");
    lcd.print(h);
    lcd.print("%");

    delay(1000); 
}