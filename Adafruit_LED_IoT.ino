#include<ESP8266WiFi.h>
#include<Adafruit_MQTT.h>
#include<Adafruit_MQTT_Client.h>
#define ssid "Pramod"
#define pass "9437131795"
#define server "io.adafruit.com"
#define port 1883
#define user "Pratyush14"
#define key "aio_Javk45OqPdkjPG38PDDhJSp8uFS5"
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client,server,port,user,key);
Adafruit_MQTT_Subscribe tog = Adafruit_MQTT_Subscribe(&mqtt,user"/feeds/toggle");

void MQTT_Connect(){
   int a,retries=3;
   if (mqtt.connected()){
      return;
    }
   Serial.println("Connecting to Adafruit MQTT");
   while((a = mqtt.connect())!=0){
      Serial.println(mqtt.connectErrorString(a));
      Serial.println("Retrying after 5 Secs");
      mqtt.disconnect();
      delay(5000);
      retries--;
      if(retries == 0){
          while(1);    // reset the nodemcu and try everything again
        }
      }
    Serial.println("MQTT Connected");
  }

void setup() {
  Serial.begin(9600);
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid,pass);
  while(WiFi.status()!=WL_CONNECTED){
    Serial.print(".");
    delay(500);
    }
  Serial.println("WiFi Connected");
  pinMode(D2,OUTPUT);
  mqtt.subscribe(&tog);
  mqtt.subscribe(&slider);
}
void loop() {
    MQTT_Connect();
    Adafruit_MQTT_Subscribe *button_data;
    while((button_data = mqtt.readSubscription(5000))){
          if(button_data == &tog){
            char* data = (char*)tog.lastread;
            Serial.println(data);
            if(strcmp(data,"ON") == 0){
                digitalWrite(D2,HIGH);
                Serial.println("LED ON");
              }
            if(strcmp(data,"OFF") == 0){
                digitalWrite(D2,LOW);
                Serial.println("LED OFF");
              }
            }
           if(button_data == &slider){
            char* data = (char*)slider.lastread;
            int brightness = atoi(data);
            analogWrite(D2,brightness);
            Serial.println(brightness); 
            }
      }
}
