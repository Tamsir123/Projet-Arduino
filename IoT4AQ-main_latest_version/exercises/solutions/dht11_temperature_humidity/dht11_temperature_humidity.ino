/**
 * DHT11 Sensor Reader for Arduino
 * This sketch reads temperature and humidity data from the DHT11 sensor and prints the values to the serial plotter.
 *
 * Author: Dhruba Saha
 * Version: 2.0.0
 * License: MIT
 * Modified for the IoT4AQ workshop at the university Alioune Diop, Bambey, Sénégal by U. Raich 
 */

// Include the DHT11 library for interfacing with the sensor.
#include <DHT11.h>

// Create an instance of the DHT11 class.
// - For ESP32: On my WeMos D1 mini ESP32 board the DHT11 data line is connected to GPIO 16
// - For the workshop we use GPIO 15
#include <Wire.h>

// Set I2C bus to use: Wire, Wire1, etc.
#define WIRE Wire


#define DHT11_DATALINE 15

DHT11 dht11(DHT11_DATALINE); // this is a global variable
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 20 chars and 4 line display


void setup()
{
   lcd.init();  
   lcd.backlight();
   char txt_buf[3]; // 2 hex characters + the ending 0
  byte error,address;
  WIRE.begin();
    // Initialize serial communication to allow debugging and data readout.
    // Using a baud rate of 115200 bps.
    Serial.begin(115200);
    if (!Serial)
      delay(10);
     
}

void loop()
{
    // Attempt to read the temperature and humidity values from the DHT11 sensor.
    delay(1000); // wait for 1 s between measurements
    int temperature = dht11.readTemperature();

    // since a new measurement is taken when reading the humidity a 1s delay must be respected
    // (see DHT11 data sheet)
    delay(1000);
    
    int humidity = dht11.readHumidity();

    // Check the results of the readings.
    // If there are errors print its type
    // if no errors are detected, print the temperature and humidity values in CSV format.
    if ((temperature == DHT11::ERROR_CHECKSUM) || (temperature == DHT11::ERROR_TIMEOUT))
      Serial.println(dht11.getErrorString(temperature));
    else if ((humidity == DHT11::ERROR_CHECKSUM) || (humidity == DHT11::ERROR_TIMEOUT))
      Serial.println(dht11.getErrorString(humidity));
    else
    {
        Serial.print("Temperature:");
        Serial.print(temperature);
        Serial.print(",Humidity:");
        Serial.println(humidity);
                            // initialize the lcd
  
  // Print a message to the LCD.
  
  lcd.setCursor(0,0);
  lcd.print("Temperature:");
  lcd.setCursor(2,1);
  lcd.print(temperature);
    lcd.setCursor(0,2);
  lcd.print(",Humidity:");
   lcd.setCursor(2,3);
  lcd.print(humidity);
    }
}

