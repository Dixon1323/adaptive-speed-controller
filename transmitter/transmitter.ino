#include <RH_ASK.h>
#include <SPI.h>

RH_ASK rf_driver;

void setup() {
  Serial.begin(9600);
  if (!rf_driver.init()) {
    Serial.println("RF driver initialization failed.");
  }
}

void loop() {
  int message = 40;
  rf_driver.send((uint8_t*)&message, sizeof(message));
  rf_driver.waitPacketSent();
  Serial.println("Sent message: ");
  Serial.println(message);
  delay(1000);
}
