#define TurbidityPin A0// 
#define PHPin A1// 
#define Supplywaterpin 11//
#define Drainwaterpin 12//

float Turbidityval;//
float PHval;//
void setup()
{
  pinMode(Supplywaterpin, OUTPUT);//
  pinMode(Drainwaterpin, OUTPUT);//
  Serial.begin(9600); // 
}
void loop()
{
   getPH();//
   delay(1000);
} 

void getTurbidity()//
{
   Turbidityval=analogRead(A0)/1024.0*5.0;
   Serial.print("    Trubidity value: ");
   Serial.println( Turbidityval);//
  }
  
 void getPH()//
 {
  PHval=analogRead(A1)/1024.0*5.0*1.45;
  Serial.print("    PH value: ");     
  Serial.println(PHval);;
 }
