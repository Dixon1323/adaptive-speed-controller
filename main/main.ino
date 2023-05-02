#include <Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <RH_ASK.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

SoftwareSerial gpsSerial(10, 9); // RX, TX pins for GPS module
TinyGPSPlus gps; // create a TinyGPS++ object
Adafruit_SSD1306 myDisplay(128, 64, &Wire);
Servo esc_signal;
RH_ASK rf_driver;
int a,speed,i;
float lat,lon;

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);
  myDisplay.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  myDisplay.clearDisplay();
  myDisplay.setTextSize(2);
  myDisplay.setCursor(0,0);
  myDisplay.setTextColor(WHITE);
  myDisplay.println("ASC System");
  myDisplay.display();
    //if (!rf_driver.init())
   //{
    //Serial.println("RF driver initialization failed.");
  //}
  pinMode(A8,INPUT);
  pinMode(2,OUTPUT);
  digitalWrite(2,LOW);
  esc_signal.attach(3);  //Specify here the pin number on which the signal pin of ESC is connected.
  esc_signal.write(30);   //ESC arm command. ESCs won't start unless input speed is less during initialization.
  delay(3000); 
}

void loop()
{
  getloc();
  receiverdata();
  a=analogRead(A8);
  a=map(a,0,1023,30,130);
  speed=map(a,30,130,0,100);
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

void getloc() {
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
    if (message == 60 && speed>=60) 
    {
      Serial.println(speed);
      rdce60();
    }
    else
    if(message == 40&&speed>=40)
    {
      Serial.print(speed);
      rdce40();
    }
  }
}

void rdce60()
{
  myDisplay.clearDisplay();
    myDisplay.setTextSize(2);
    myDisplay.setCursor(0,0);
    myDisplay.setTextColor(WHITE);
    myDisplay.println("Speed limiting");
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
    esc_signal.write(78);
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
  myDisplay.clearDisplay();
    myDisplay.setTextSize(2);
    myDisplay.setCursor(0,0);
    myDisplay.setTextColor(WHITE);
    myDisplay.println("Speed limiting");
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
    esc_signal.write(52);
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

