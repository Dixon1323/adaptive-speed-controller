#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

SoftwareSerial mySerial(D5, D6); 

SoftwareSerial gpsSerial(D1, D3); // RX, TX pins for GPS module
//SoftwareSerial mySerial(4, 3);
TinyGPSPlus gps; // create a TinyGPS++ object
float lat,lon;

void setup() {
  Serial.begin(9600); // initialize serial communication for debugging
  gpsSerial.begin(9600); // initialize GPS serial communication
  //mySerial.begin(9600);
}

void loop() {
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
        String url = "https://www.google.com/maps/search/?api=1&query=" + String(lat, 6) + "," + String(lon, 6);
        Serial.println(url);
       // mySerial.println(url);
       // Serial.print(gps.location.lng(), 6); // print longitude with 6 decimal places
        //Serial.print(", Altitude: ");
        //Serial.print(gps.altitude.meters()); // print altitude in meters
        //Serial.println(" meters");
      }
    }
  }

}
