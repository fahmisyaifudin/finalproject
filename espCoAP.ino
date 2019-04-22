/*
ESP-COAP Client
*/
#include <WiFi.h>
#include "coap_client.h"
#include <DHT.h>

#define DHTPIN 26
#define DHTTYPE DHT22

//instance for coapclient
coapClient coap;

//WiFi connection info
const char* ssid = "Andromax-M2Y-DFFC";
const char* password = "katingcaper";
char humidity[50];

//ip address and default port of coap server in which your interested in
IPAddress ip(192,168,1,100);//take ETH Zurich or coap.me server to run and check client 
int port =5683;
DHT dht(DHTPIN, DHTTYPE);

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
//int i=0;

void loop() {
    float hum = dht.readHumidity();
    snprintf (humidity, 50, "%.2f", hum);
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print("\n");
    bool state;
    //put request 
    //arguments server ip address,default port,resource name, payload,payloadlength
    int msgid =coap.put(ip,port,"sensor",humidity,5);  
    Serial.println(msgid);
    delay(10000);
}
