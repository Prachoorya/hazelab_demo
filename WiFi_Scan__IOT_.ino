#include<ESP8266WiFi.h>
void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("Scanning Wifi....");
  int n = WiFi.scanNetworks();
  Serial.println("Scanning Completed");
  if(n==0){
    Serial.println("No Network");
    }
  else{
     for(int i=0; i<n; i++){
      Serial.print(WiFi.SSID(i));   // Service Set Identifier
      Serial.print("(");
      Serial.print(WiFi.RSSI(i));   // Received Signal Strength Indicator
      Serial.println(")");
      }
    }
  delay(5000);
}
