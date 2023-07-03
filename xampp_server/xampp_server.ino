//////////////////////////////////////////
////new code
//////////////////////////////////////////

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

String URL = "http://172.20.10.2/speed/post.php";
//String URL = "http://192.168.1.10/speed/post.php";
String link="https://www.google.com/maps/search/?query=9.916844,76.621284";


const char* ssid = "Iphone 12"; 
const char* password = "tubelight"; 

int temperature = 50; 
int humidity = 50;

void setup() {
  Serial.begin(115200); 
  connectWiFi();
}

void loop()
 {
  if(WiFi.status() != WL_CONNECTED) { 
    connectWiFi();
  }

  String postData = "Location=" + link + "&speed=" + humidity; 
    Serial.println(postData);
    WiFiClient client;
    HTTPClient http;
  http.begin(client, URL);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  int httpCode = http.POST(postData); 
  String payload = http.getString(); 
  
  Serial.print("URL : "); Serial.println(URL); 
  Serial.print("Data: "); Serial.println(postData); 
  Serial.print("httpCode: "); Serial.println(httpCode); 
  Serial.print("payload : "); Serial.println(payload); 
  Serial.println("--------------------------------------------------");
}



void connectWiFi() {
  WiFi.mode(WIFI_OFF);
  delay(1000);
  //This line hides the viewing of ESP as wifi hotspot
  WiFi.mode(WIFI_STA);
  
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
    
  Serial.print("connected to : "); Serial.println(ssid);
  Serial.print("IP address: "); Serial.println(WiFi.localIP());
}