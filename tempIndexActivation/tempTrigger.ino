#include "DHT.h"

#define DHTPIN A0     // what pin we're connected to for data
#define DHTTYPE DHT22   // DHT 22  (AM2302)
//this is the pin that turns on the relay if it is cold enough, adjust if using different pin
#define outputPin 2
int maxHum = 60;
int maxTemp = 40;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(outputPin, OUTPUT);
  Serial.begin(9600); 
  dht.begin();
}

void loop() {

  // Wait a few seconds between measurements.
  delay(2000);
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
 
  if(h > maxHum || t > maxTemp) {
      digitalWrite(outputPin, HIGH);
  } else {
     digitalWrite(outputPin, LOW); 
  }
  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.println(" *C ");
}
