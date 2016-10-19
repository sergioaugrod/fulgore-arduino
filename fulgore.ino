#include <math.h>
#include <DHT.h>
#include <ArduinoJson.h>

#define LDR_PIN A0
#define DHT_PIN A1
#define PRESENCE_PIN 8

#define DHT_TYPE DHT11
DHT dht(DHT_PIN, DHT_TYPE);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  sensors();
}

void sensors() {
  sendMessage("temperature", dht.readTemperature());
  sendMessage("humidity", dht.readHumidity());
  sendMessage("luminosity", readLuminosity());
  sendMessage("presence", readPresence());

  delay(1500);
}

double readLuminosity() {
  double luminosity = analogRead(LDR_PIN);
  return 100 - ((luminosity / 1024) * 100);
}

int readPresence() {
  return digitalRead(PRESENCE_PIN);
}

void sendMessage(String topic, double value) {
  StaticJsonBuffer<200> jsonBuffer;

  JsonObject& message = jsonBuffer.createObject();
  message["topic"] = topic;
  message["value"] = value;

  message.printTo(Serial);
  Serial.println();
}

void sendMessage(String topic, int value) {
  StaticJsonBuffer<200> jsonBuffer;

  JsonObject& message = jsonBuffer.createObject();
  message["topic"] = topic;
  message["value"] = value;

  message.printTo(Serial);
  Serial.println();
}

void sendMessage(String topic, String value) {
  StaticJsonBuffer<200> jsonBuffer;

  JsonObject& message = jsonBuffer.createObject();
  message["topic"] = topic;
  message["value"] = value;

  message.printTo(Serial);
  Serial.println();
}
