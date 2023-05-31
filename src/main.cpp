#include <Arduino.h>
#include <simpleRPC.h>
#include "config.h"
#include "menu.h"
#include "keypadlcd.h"


KeypadLCDControl keypadLCDControl(LCD_RS_PIN, LCD_EN_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN, BUTTON_PIN);
Menu menu(&keypadLCDControl);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.println(WATER_BOOT_TEXT);
  keypadLCDControl.setup_hook();
  menu.setup_hook();
}

void loop() {
  // put your main code here, to run repeatedly:
  keypadLCDControl.loop_hook();
  menu.loop_hook();
}