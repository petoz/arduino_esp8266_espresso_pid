//espresso pid esp8266,arduino uno

#include "DHT.h"

#define DHTPIN            2         // Pin which is connected to the DHT sensor.
#define DHTTYPE   DHT11     // DHT 11 

DHT DHTPID(DHTPIN, DHTTYPE);

float temp;

void setup() {
  Serial.begin(9600);
  DHTPID.begin();
}

void loop() {
  delay(2000);
  temp = DHTPID.readTemperature();
  if (isnan(temp)) {
    Serial.println("Error reading temperature!");
  }
  else {
    Serial.print("Temperature: ");
    Serial.print(DHTPID.readTemperature());
    Serial.println(" *C");
  }
}
