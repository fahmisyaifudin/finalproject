#include <WiFi.h>
#include <PubSubClient.h>

#define CLIENT_ID "ESPfahmi"

const char* ssid       = "Andromax-M2Y";
const char* password   = "katinggoblok";
const char* mqtt_server = "192.168.1.102";
float pH;
char suhu[50];

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
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
  if (Serial.available()) {
   pH = Serial.parseFloat();
   snprintf (suhu, 50, "%.2f", pH);
   client.publish("Suhu", suhu);
   Serial.println(suhu);
    
    /*
    snprintf (suhu, 50, "%s", pH);
    Serial.print(suhu);
    client.publish("Suhu", suhu);
    */
  }
}
