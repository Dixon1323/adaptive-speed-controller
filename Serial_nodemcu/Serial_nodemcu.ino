#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <TinyGPS++.h>

SoftwareSerial mySerial(D5, D6); // RX, TX
SoftwareSerial gpsSerial(D1, D3);
String URL = "http://192.168.62.123/speed/post.php";
//String URL = "http://192.168.1.10/speed/post.php";
String dataPacket,gpsData,datas;
TinyGPSPlus gps; // create a TinyGPS++ object
float lat,lon;
const char* ssid = "Odikko"; 
const char* password = "qwertyuiop"; 

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  gpsSerial.begin(9600);
  pinMode(LED_BUILTIN,OUTPUT);
  connectWiFi();
}

void serial_read() 
{
  if(WiFi.status() != WL_CONNECTED)
     { 
    connectWiFi();
     }

  // Check if there is data available on mySerial
  if (mySerial.available()) 
  {
    // Read the data packet from mySerial
    dataPacket = mySerial.readStringUntil('\n');

    // Extract the GPS data and the integer variable from the data packet
    //int spaceIndex = dataPacket.indexOf(' ');
    int spaceIndex1 = dataPacket.indexOf(' ');
    int spaceIndex2 = dataPacket.indexOf(' ', spaceIndex1 + 1);
    gpsData = dataPacket.substring(0, spaceIndex1);
    //int intData = dataPacket.substring(spaceIndex + 1).toInt();
    int intData1 = dataPacket.substring(spaceIndex1 + 1, spaceIndex2).toInt();
    int intData2 = dataPacket.substring(spaceIndex2 + 1).toInt();

    // Print the data to the serial monitor for debugging
    Serial.print("GPS data: ");
    Serial.print(gpsData);
    Serial.print(" , integer variable 1: ");
    Serial.println(intData1);
    Serial.print(" , integer variable 2: ");
    Serial.println(intData2);

  String postData = "Location=" + datas + "&speed=" + intData1 + "&limit=" + intData2;  
  // String postData ="&speed=" + intData1 + "&limit=" + intData2; 
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
}

void connectWiFi()
 {
  WiFi.mode(WIFI_OFF);
  delay(1000);
  //This line hides the viewing of ESP as wifi hotspot
  WiFi.mode(WIFI_STA);
  
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  
  while (WiFi.status() != WL_CONNECTED) 
  {
    digitalWrite(LED_BUILTIN,HIGH);
    delay(500);
    Serial.print(".");
  }
  digitalWrite(LED_BUILTIN,LOW);
  Serial.print("connected to : "); Serial.println(ssid);
  Serial.print("IP address: "); Serial.println(WiFi.localIP());
}

 void loop() 
 {
  serial_read();
  while (gpsSerial.available() > 0) 
  {
    if (gps.encode(gpsSerial.read()))
     {
      if (gps.location.isValid()) 
      { 
        lat = gps.location.lat();
        lon = gps.location.lng();
        //Serial.print("Latitude: ");
        //Serial.print(gps.location.lat(), 6); // print latitude with 6 decimal places
        //Serial.print(", Longitude: ");
        datas = "https://www.google.com/maps/search/?api=1&query=" + String(lat, 6) + "," + String(lon, 6);
        Serial.print("received from gps module : ");
        Serial.println(datas);
       // mySerial.println(url);
       // Serial.print(gps.location.lng(), 6); // print longitude with 6 decimal places
        //Serial.print(", Altitude: ");
        //Serial.print(gps.altitude.meters()); // print altitude in meters
        //Serial.println(" meters");
      }
    }
  }

}
