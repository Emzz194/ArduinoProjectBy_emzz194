#include "DHT.h"
#define DHTPIN 14
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);





void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  dht.begin();



}

void loop() {
  // put your main code here, to run repeatedly:
  float h =dht.readHumidity();
  float t = dht.readTemperature();
  if(isnan(h)|| isnan(t) ){
    Serial.println("error");
    delay(1500);
    return;

  }
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println("%\t");

  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println("°C");
  delay(1500);

}
