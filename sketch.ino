#define BLYNK_TEMPLATE_ID "TMPL3c46Pvih3"
#define BLYNK_TEMPLATE_NAME "Skin Analyser"
#define BLYNK_AUTH_TOKEN "OPMdUPvXhjOL3d1BL7uL6DlVCoZ_jnXb"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"

char ssid[] = "Wokwi-GUEST";  
char pass[] = "";  

#define DHTPIN 15
#define LDRPIN 32
#define LEDPIN 2
#define BUZZERPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensorData() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int ldrValue = analogRead(LDRPIN);

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("❌ Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temp: "); Serial.print(temperature);
  Serial.print(" °C  | Humidity: "); Serial.print(humidity);
  Serial.print(" %  | LDR: "); Serial.println(ldrValue);

  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, humidity);
  Blynk.virtualWrite(V2, ldrValue);

  if (temperature > 37.0 || humidity < 30 || ldrValue > 3000) {
    digitalWrite(LEDPIN, HIGH);
    digitalWrite(BUZZERPIN, HIGH);
  } else {
    digitalWrite(LEDPIN, LOW);
    digitalWrite(BUZZERPIN, LOW);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LEDPIN, OUTPUT);
  pinMode(BUZZERPIN, OUTPUT);
  dht.begin();

  WiFi.begin(ssid, pass);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ WiFi Connected!");

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Serial.println("✅ Connected to Blynk Cloud!");
  timer.setInterval(2000L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();
}
