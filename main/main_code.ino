#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <RH_ASK.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
SoftwareSerial gpsSerial(10, 13); // RX, TX pins for GPS module
SoftwareSerial mySerial(4, 3);
TinyGPSPlus gps; // create a TinyGPS++ object
Adafruit_SSD1306 myDisplay(128, 64, &Wire);
RH_ASK rf_driver;
int a,b,speed,gps_speed,i;
float lat=0.000000,lon=00.000000;
int style=0,limit=0;;
String url,url1;

void setup() {
  Serial.begin(115200);
  gpsSerial.begin(9600);
  mySerial.begin(9600);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(A9,INPUT);
  digitalWrite(6,LOW);
  digitalWrite(5,HIGH);
  myDisplay.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  myDisplay.clearDisplay();
  myDisplay.setTextSize(2);
  myDisplay.setCursor(0,0);
  myDisplay.setTextColor(WHITE);
  myDisplay.println("ASC System");
  myDisplay.display();
  rf_driver.init();
  pinMode(A8,INPUT);
  pinMode(2,OUTPUT);
  digitalWrite(2,LOW);
  delay(3000); 
}

void loop()
{
  //mySerial.println(url);
  receiverdata();
  style=1;
  b=analogRead(A9);
  //Serial.println(b);
  a=analogRead(A8);
  a=map(a,0,1023,0,255);
  Serial.println(a);
  speed=map(a,60,255,0,100);
  gps_speed=speed;;
  analogWrite(8,a);
  if(speed<0)
  {
    gps_speed=0;
  myDisplay.clearDisplay();
  myDisplay.setTextSize(4);
  myDisplay.setCursor(25,2);
  myDisplay.setTextColor(WHITE);
  myDisplay.println("0");
  myDisplay.setTextSize(3);
  myDisplay.setCursor(25,40);
  myDisplay.setTextColor(WHITE);
  myDisplay.println("Km/h");
  myDisplay.display();
  }
  else
  {
  myDisplay.clearDisplay();
  myDisplay.setTextSize(4);
  myDisplay.setCursor(25,2);
  myDisplay.setTextColor(WHITE);
  myDisplay.println(speed);
  myDisplay.setTextSize(3);
  myDisplay.setCursor(25,40);
  myDisplay.setTextColor(WHITE);
  myDisplay.println("Km/h");
  myDisplay.display();
}
}

void getloc() {
  while (gpsSerial.available() > 0) 
  {
   // Serial.println("jjhgfdfgghgtyrtdfcv");
    if (gps.encode(gpsSerial.read()))
     {
      if (gps.location.isValid()) 
      { 
        lat = gps.location.lat();
        lon = gps.location.lng();
        //Serial.print("Latitude: ");
        //Serial.print(gps.location.lat(), 6); // print latitude with 6 decimal places
        //Serial.print(", Longitude: ");
        url = "https://www.google.com/maps/search/?api=1&query=" + String(lat, 6) + "," + String(lon, 6)+ " " + String(gps_speed)+ " " + String(limit);
        Serial.println(url);
       // mySerial.println(url);
        style=1;
       // Serial.print(gps.location.lng(), 6); // print longitude with 6 decimal places
        //Serial.print(", Altitude: ");
        //Serial.print(gps.altitude.meters()); // print altitude in meters
        //Serial.println(" meters");
      }
     }
  }
}



void receiverdata()
{
uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);
  if (rf_driver.recv(buf, &buflen))
   {
    int message = *(int*)buf;
   Serial.print("Received message: ");
   Serial.println(message);
    if (message == 60 && speed>=60&&a>=177) 
    {
      //Serial.println(speed);
      rdce60();
    }
    else
    if(message == 40&&speed>=40&&a>=138)
    {
      //Serial.print(speed);
      rdce40();
    }
  }
}

void rdce60()
{
 
    limit=60;
    url = "https://www.google.com/maps/search/?api=1&query=" + String(lat, 6) + "," + String(lon, 6)+ " " + String(gps_speed)+ " " + String(limit);
    Serial.println(url);
    mySerial.println(url);
    mySerial.println(url);
    analogWrite(8,140);
    myDisplay.clearDisplay();
    myDisplay.setTextSize(2);
    myDisplay.setCursor(0,0);
    myDisplay.setTextColor(WHITE);
    myDisplay.println("limiting Speed");
    myDisplay.display();
    for(i=0;i<7;i++)
    {
      digitalWrite(2,HIGH);
      delay(200);
      digitalWrite(2,LOW);
      delay(200);
    }
    delay(2000);
    myDisplay.clearDisplay();
    myDisplay.clearDisplay();
    myDisplay.setTextSize(4);
    myDisplay.setCursor(25,2);
    myDisplay.setTextColor(WHITE);
    myDisplay.println("60");
    myDisplay.setTextSize(3);
    myDisplay.setCursor(25,40);
    myDisplay.setTextColor(WHITE);
    myDisplay.println("Km/h");
    myDisplay.display();
    delay(5000);
}

void rdce40()
{
 

    limit=40;
    url = "https://www.google.com/maps/search/?api=1&query=" + String(lat, 6) + "," + String(lon, 6)+ " " + String(gps_speed)+ " " + String(limit);
    Serial.println(url);
    mySerial.println(url);
    analogWrite(8,100);
    myDisplay.clearDisplay();
    myDisplay.setTextSize(2);
    myDisplay.setCursor(0,0);
    myDisplay.setTextColor(WHITE);
    myDisplay.println("limiting   Speed");
    myDisplay.display();
    for(i=0;i<7;i++)
    {
      digitalWrite(2,HIGH);
      delay(200);
      digitalWrite(2,LOW);
      delay(200);
    }
    delay(2000);
    myDisplay.clearDisplay();
    myDisplay.clearDisplay();
    myDisplay.setTextSize(4);
    myDisplay.setCursor(25,2);
    myDisplay.setTextColor(WHITE);
    myDisplay.println("40");
    myDisplay.setTextSize(3);
    myDisplay.setCursor(25,40);
    myDisplay.setTextColor(WHITE);
    myDisplay.println("Km/h");
    myDisplay.display();
    delay(5000);
}

