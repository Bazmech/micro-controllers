#include <Adafruit_BMP280.h>
#include <Adafruit_AHTX0.h>
#include "Wire.h"

Adafruit_AHTX0 aht;
Adafruit_BMP280 bmp;

float pressureAtSeaLevel = 1010.2;

void setup() {
  byte error, address;
  int nDevices = 0;
  Serial.begin(115200);
  Wire.begin(5, 6);
  Serial.println("v3");

  if (! aht.begin()) {
    Serial.println("Could not find AHT? Check wiring");
    while (1) delay(10);
  }
  
  if  (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor,  check wiring!"));
    while (1);
  }

  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500);  /* Standby time. */

  Serial.println("AHT10 or AHT20 found");

  
  Serial.println("Scanning for I2C devices ...");
  for (address = 0x01; address < 0x7f; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      Serial.printf("I2C device found at address 0x%02X\n", address);
      nDevices++;
    } else if (error != 2) {
      Serial.printf("Error %d at address 0x%02X\n", error, address);
    }
  }
}

void loop() {
  int nDevices = 0;

  delay(5000);

  if (nDevices == 0) {
    Serial.println("No I2C devices found");
  }
  
  // listen for commands
  if (Serial.available() > 0) {

    // read command
    String command = Serial.readStringUntil('\n');

    // run command
    if (command == "ping") {

      // send response
      Serial.print("pong");
      Serial.print("\n");
    } else {
      pressureAtSeaLevel = command.toFloat();
    }
  }
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
  Serial.print("Temperature: "); Serial.print(temp.temperature); Serial.println(" degrees C");
  Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); Serial.println("% rH");

  Serial.println();

  Serial.print(F("Temperature  = "));
  Serial.print(bmp.readTemperature());
  Serial.println(" *C");

  Serial.print(F("Pressure = "));
  Serial.print(bmp.readPressure()/100);  //displaying the Pressure in hPa, you can change the unit
  Serial.println("  hPa");

  Serial.print(F("Approx altitude = "));
  Serial.print(bmp.readAltitude(pressureAtSeaLevel));  //The "1019.66" is the pressure(hPa) at sea level in day in your region
  Serial.println("  m");                    //If you don't know it, modify it until you get your current  altitude

  Serial.println();
  Serial.println("----------------------------------------------------");
  Serial.println();

}
