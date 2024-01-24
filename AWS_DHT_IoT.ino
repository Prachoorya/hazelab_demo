#include<ESP8266WiFi.h>
#include<ESP8266HTTPClient.h>
#include<DHT.h>
DHT dht(D2,DHT11);
float h,t;
char* ssid = "Pramod";
char* pass = "9437131795";
HTTPClient client;
void setup() {
  Serial.begin(9600);
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid,pass);
  while(WiFi.status()!=WL_CONNECTED){
    Serial.print(".");
    delay(500);
    }
  Serial.println("WiFi Connected");
  dht.begin();
}

void loop() {
  h = dht.readHumidity();
  t = dht.readTemperature();
  Serial.print(t);
  Serial.print(",");
  Serial.println(h);
  String api = "http://13.233.195.156/sensor.php?a="+String(h)+"&b="+String(t);
  client.begin(api);
  int code = client.GET();
  String response = http.getString();
  Serial.println(code);
  Serial.println(response);             
  delay(1000)
}
