#include <ESP8266WiFi.h>
#include <PubSubClient.h>

void callback(char* topic, byte* payload, unsigned int payloadLength);
const char* ssid = "MLRITM-PLACEMENT";
const char* password = "Mlritm@123";

#define ORG           "zoe3jx"
#define DEVICE_TYPE   "Smart_Building"
#define DEVICE_ID     "12345"
#define TOKEN         "187Y1A1252"

#define flame D1

String data;
char server[] = ORG ".messaging.internetofthings.ibmcloud.com";
char subtopic[] = "iot-2/cmd/home/fmt/String";
char pubtopic[] = "iot-2/evt/dht11/fmt/json";
char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;

WiFiClient wifiClient;
PubSubClient client(server, 1883, callback, wifiClient);

void setup() {
  Serial.begin(9600);
  wifiConnect();
  mqttConnect();

pinMode(flame,INPUT);
Serial.print("Connecting to ");
 Serial.print(ssid);
 WiFi.begin(ssid, password);
 while (WiFi.status()!= WL_CONNECTED) 
 {
      delay(500);
      Serial.print(".");
 } 
 Serial.println("");
 
 Serial.print("WiFi connected, IP address : ");
 Serial.println(WiFi.localIP());
}


void loop() {
  // put your main code here, to run repeatedly:
if (!client.loop()) 
  {
    mqttConnect();
  }
  delay(100);
  float f=digitalRead(flame);
  PublishData(f);
  delay(1000);
}
void wifiConnect() 
{
  Serial.print("Connecting to "); Serial.print(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.print("nWiFi connected, IP address: "); Serial.println(WiFi.localIP());
}

void mqttConnect() 
{
  if (!client.connected())
  {
    Serial.print("Reconnecting MQTT client to ");
    Serial.println(server);
    while (!client.connect(clientId, authMethod, token))
    {
      Serial.print(".");
      delay(500);
    }
    initManagedDevice();
    Serial.println();
  }
}
void initManagedDevice() 
{
  if (client.subscribe(subtopic)) 
  {
    Serial.println("subscribe to cmd OK");
  }
  else 
  {
    Serial.println("subscribe to cmd FAILED");
  }
}

/*void callback(char* topic, byte* payload, unsigned int payloadLength)
{
  Serial.print("callback invoked for topic: "); 
  Serial.println(subtopic);

  for (int i = 0; i < payloadLength; i++) 
  {
    data += (char)payload[i];
  }
    Serial.println(data);
    if(data == "light_ON")
    {
      digitalWrite(D1,HIGH);
      Serial.println("Light is Switched ON");
    }
    else if(data == "light_OFF")
    {
       digitalWrite(D1,LOW);
        Serial.println("Light is Switched OFF");
    }
    data ="";
}*/
void PublishData(int f)
{
  if (!client.connected()) 
  {
    Serial.print("Reconnecting client to ");
    Serial.println(server);
    while (!client.connect(clientId, authMethod, token)) 
    {
      Serial.print(".");
      delay(500);
    }
     Serial.println();
  }
  String payload="Fire";
  payload+=f;
  payload+=" . ";
 Serial.print("Sending payload: ");
 Serial.println(payload);
  
 if (client.publish(pubtopic, (char*) payload.c_str()))
 {
    Serial.println("Publish ok");
 }
 else 
 {
 Serial.println("Publish failed");
 }
}
