#include <Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <RH_ASK.h>
#include <SPI.h>

Adafruit_SSD1306 myDisplay(128, 64, &Wire);
Servo esc_signal;
RH_ASK rf_driver;
int a,speed;

void setup()
{
  Serial.begin(9600);
  myDisplay.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  myDisplay.clearDisplay();
    myDisplay.setTextSize(2);
    myDisplay.setCursor(0,0);
    myDisplay.setTextColor(WHITE);
    myDisplay.println("ASC System");
    myDisplay.display();
    if (!rf_driver.init())
   {
    Serial.println("RF driver initialization failed.");
  }
  pinMode(A0,INPUT);
  esc_signal.attach(9);  //Specify here the pin number on which the signal pin of ESC is connected.
  esc_signal.write(30);   //ESC arm command. ESCs won't start unless input speed is less during initialization.
  delay(3000);            //ESC initialization delay.
}

void loop()
{
  receiverdata();
a=analogRead(A0);
//Serial.println(a);
a=map(a,0,1023,40,130);
//Serial.println(a);
esc_signal.write(a);
speed=map(a,40,130,0,100);
//Serial.println(speed);
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
delay(15);
}

void rdce()
{
  myDisplay.clearDisplay();
    myDisplay.setTextSize(2);
    myDisplay.setCursor(0,0);
    myDisplay.setTextColor(WHITE);
    myDisplay.println("Speed limiting");
    myDisplay.display();
    delay(2000);
    myDisplay.clearDisplay();
    esc_signal.write(76);
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

void receiverdata()
{
uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);
  if (rf_driver.recv(buf, &buflen))
   {
    int message = *(int*)buf;
    Serial.print("Received message: ");
    Serial.println(message);
    if (message == 60) 
    {
      rdce();
    }
  }
}