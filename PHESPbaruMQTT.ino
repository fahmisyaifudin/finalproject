#include <WiFi.h>
#include <PubSubClient.h>

#define SensorPin 35            //pH meter Analog output to Arduino Analog Input 0
#define Offset 0.00            //deviation compensate
#define samplingInterval 20
#define printInterval 800
#define pHWater 7
#define ArrayLenth  40    //times of collection
#define CLIENT_ID "ESPfahmi"

int pHArray[ArrayLenth];   //Store the average value of the sensor feedback
int pHArrayIndex=0;
int adc;
const char* ssid       = "Andromax-M2Y-DFFC";
const char* password   = "katingcaper";
const char* mqtt_server = "192.168.43.132";
char pH[50];
WiFiClient espClient;
PubSubClient client(espClient);

void setup(void)
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println(" CONNECTED");
  client.setServer(mqtt_server, 1883);
  client.connect(CLIENT_ID, "fahmi", "123456");
  Serial.println("pH meter experiment!");    //Test the serial monitor
}

void loop(void)
{
  static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();
  static float pHValue,voltage;
  if(millis()-samplingTime > samplingInterval)
  {
      pHArray[pHArrayIndex++]=analogRead(SensorPin);
      analogReadResolution(10);
      adc = analogRead(SensorPin);
      if(pHArrayIndex==ArrayLenth)pHArrayIndex=0;
      voltage = avergearray(pHArray, ArrayLenth)*3.3/1024; //diubah rumusnya atau menggunkan level logic controller.
      pHValue = 3.5*voltage+Offset;
      pHValue = pHWater - (pHValue - pHWater);
      samplingTime=millis();
  }
  if(millis() - printTime > printInterval)   //Every 800 milliseconds, print a numerical, convert the state of the LED indicator
  {
        Serial.print("Voltage:");
        Serial.print(voltage,2);
        Serial.print("    pH value: ");
        Serial.println(pHValue,2);
        Serial.print("ADC: ");
        Serial.println(adc);
        snprintf (pH, 50, "%.2f", pHValue);
        Serial.print("pH: ");
        Serial.println(pH);
        client.publish("Suhu", pH);
        printTime=millis();
        delay(20000);
  }
}
double avergearray(int* arr, int number){
  int i;
  int max,min;
  double avg;
  long amount=0;
  if(number<=0){
    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if(number<5){   //less than 5, calculated directly statistics
    for(i=0;i<number;i++){
      amount+=arr[i];
    }
    avg = amount/number;
    return avg;
  }else{
    if(arr[0]<arr[1]){
      min = arr[0];max=arr[1];
    }
    else{
      min=arr[1];max=arr[0];
    }
    for(i=2;i<number;i++){
      if(arr[i]<min){
        amount+=min;        //arr<min
        min=arr[i];
      }else {
        if(arr[i]>max){
          amount+=max;    //arr>max
          max=arr[i];
        }else{
          amount+=arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount/(number-2);
  }//if
  return avg;
}
