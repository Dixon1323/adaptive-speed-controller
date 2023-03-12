#include <RH_ASK.h>
#include <SPI.h>

RH_ASK rf_driver;

void setup() {
  Serial.begin(9600);
  if (!rf_driver.init())
   {
    Serial.println("RF driver initialization failed.");
  }
}

void loop() {
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);
  if (rf_driver.recv(buf, &buflen))
   {
    int message = *(int*)buf;
    Serial.print("Received message: ");
    Serial.println(message);
    if (message == 40) {
      Serial.println("Received message 20: Success!");
    }
  }
}
