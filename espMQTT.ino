#include <DHT.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define DHTPIN 26
#define DHTTYPE DHT22
#define CLIENT_ID "ESPfahmi"

float hum = 0;
float temp = 0;
const char* ssid       = "Andromax-M2Y-DFFC";
const char* password   = "katingcaper";
const char* mqtt_server = "192.168.1.100";
char suhu[50];
char humidity[50];

WiFiClient espClient;
PubSubClient client(espClient);

DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(115200);
  dht.begin();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println(" CONNECTED");
  client.setServer(mqtt_server, 1883);
  client.connect(CLIENT_ID, "fahmi", "123456");

}

void loop() {
  float temp = dht.readTemperature();
  snprintf (suhu, 50, "%.2f", temp);
  client.publish("Suhu", suhu);
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.println(" Celsius");
  delay(10000);
}
