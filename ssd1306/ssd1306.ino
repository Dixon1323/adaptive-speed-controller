#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


Adafruit_SSD1306 myDisplay(128, 64, &Wire);


void setup() {
//internel charge pump cct enable. or DC-to-DC converter
  myDisplay.begin(SSD1306_SWITCHCAPVCC, 0x3C);

}

void loop() {
  myDisplay.clearDisplay();

    myDisplay.setTextSize(2);
    myDisplay.setCursor(0,0);
    myDisplay.setTextColor(WHITE);
    myDisplay.println("vaave");

    myDisplay.display();
  
  //LEFT to RIGHT and RIGHT to LEFT Scroll
    myDisplay.startscrolldiagright(0, 7);
    delay(2000);
    myDisplay.stopscroll();
     
    myDisplay.startscrolldiagleft(0, 7);
    delay(2000);
    myDisplay.stopscroll();
    
}
