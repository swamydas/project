  #define ldr 14
#define smoke 15
#define flame 16
#define led 6
#define buzzer 8
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(ldr,INPUT);
pinMode(smoke,INPUT);
pinMode(flame,INPUT);
pinMode(led,OUTPUT);
pinMode(buzzer,OUTPUT);
pinMode(12,OUTPUT);
}
void loop() {
  // put your main code here, to run repeatedly:
Serial.print("ldr:");
Serial.println(analogRead(ldr));
Serial.print("smoke:");
Serial.println(analogRead(smoke));
Serial.print("flame:");
Serial.println(analogRead(flame));
delay(1000);

int l,s,f,flame_alert;
l=analogRead(ldr);
s=analogRead(smoke);
f=analogRead(flame);
//ldr code
if(l>=1000)
   digitalWrite(led,HIGH);
else
   digitalWrite(led,LOW);
//smoke code
if(s>=600)
   digitalWrite(buzzer,HIGH);
else
   digitalWrite(buzzer,LOW);
//flame  
if(f<=50)
{
   flame_alert=1;
   digitalWrite(12,HIGH);
}
else
{
   flame_alert=0;
   digitalWrite(12,HIGH);
}
if(flame_alert==1)
   Serial.println("Fire Alert!!!");
}
