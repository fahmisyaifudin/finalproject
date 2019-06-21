#include "OneWire.h"
#include "DallasTemperature.h"
#include <WiFi.h>
#include "coap_client.h"

coapClient coap;

const char* ssid = "Andromax-M2Y-DFFC";
const char* password = "katingcaper";
char temp[50];

IPAddress ip(192,168,43,132);//take ETH Zurich or coap.me server to run and check client 
int port =5683;

OneWire oneWire(22);
DallasTemperature tempSensor(&oneWire);

// coap client response callback
void callback_response(coapPacket &packet, IPAddress ip, int port);

// coap client response callback
void callback_response(coapPacket &packet, IPAddress ip, int port) {
    char p[packet.payloadlen + 1];
    memcpy(p, packet.payload, packet.payloadlen);
    p[packet.payloadlen] = NULL;

    //response from coap server
 if(packet.type==3 && packet.code==0){
      Serial.println("ping ok");
    }

    Serial.println(p);
}



void setup() {
  Serial.begin(115200);
  tempSensor.begin();
  WiFi.begin(ssid, password);
    Serial.println(" ");

    // Connection info to WiFi network
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
    //delay(500);
    yield();
    Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    // Print the IP address of client
    Serial.println(WiFi.localIP());
    coap.response(callback_response);
    coap.start();

}

void loop() {
    float suhu = ambilsuhuair();
    snprintf (temp, 50, "%.2f", suhu);
    Serial.print("Suhu air: ");
    Serial.print(temp);
    Serial.print("\n");
    bool state;
    //put request 
    //arguments server ip address,default port,resource name, payload,payloadlength
    int msgid =coap.put(ip,port,"sensor",temp,5);  
    Serial.println(msgid);
    delay(60000);
}

float ambilsuhuair()
{
  tempSensor.requestTemperaturesByIndex(0);  
  return tempSensor.getTempCByIndex(0);
}
