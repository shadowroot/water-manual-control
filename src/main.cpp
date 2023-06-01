#include <Arduino.h>
#include <simpleRPC.h>
#include "config.h"
#include <LiquidCrystal.h>
#include <simpleRPC.h>

LiquidCrystal lcd(LCD_RS_PIN, LCD_EN_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);

enum ButtonPressed{ RIGHT, UP, DOWN, LEFT, SELECT, NONE };
bool running = false;

void callCommand(const char* command){
    Serial.println(command);
    int i = 0;
    char buf[3];
    while (Serial.available() > 0) {
      if(Serial.available() > 0){
        int incomingByte = 0;
        // read the incoming byte:
        incomingByte = Serial.read();
        buf[i%3] = incomingByte;
        i++;
        Serial.print((char)incomingByte);
      }
      if(buf[0] == 'O' && buf[1] == 'N'){
          running = true;
          break;
      }
      else if(buf[0] == 'O' && buf[1] == 'F'  && buf[2] == 'F'){
          running = false;
          break;
      }
      //Serial.print("buf: ");
      //Serial.println(buf);
    }
}

ButtonPressed read_LCD_buttons()
{
  int adc_key_in = analogRead(A0);      // read the value from the sensor 
  // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
  // we add approx 50 to those values and check to see if we are close
  ButtonPressed selectedKey = ButtonPressed::NONE;
  const char * selectedText = "N";
  if (adc_key_in < 50){
    selectedKey = ButtonPressed::RIGHT; 
    selectedText = "R";
  }
  else if (adc_key_in < 250) {
    selectedKey = ButtonPressed::UP;
    selectedText = "U";
  }
  else if (adc_key_in < 450){
    selectedKey = ButtonPressed::DOWN;
    selectedText = "D";
  }
  else if (adc_key_in < 650){
    selectedKey = ButtonPressed::LEFT;
    selectedText = "L";
  }
  else if (adc_key_in < 850){
    selectedKey = ButtonPressed::SELECT;
    selectedText = "S";
  }
  // Serial.print("adc_key_in: ");
  // Serial.println(adc_key_in);
  // Serial.print("selectedKey: ");
  // Serial.println(selectedKey);
  lcd.setCursor(15, 1);
  lcd.print(selectedText);
  // Serial.print("selectedText: ");
  // Serial.println(selectedText);

  return selectedKey;
}

ButtonPressed readClickButton(){
  ButtonPressed key = read_LCD_buttons();
  if(key != ButtonPressed::NONE){
    //HOld clicked
    while(key == read_LCD_buttons()){
      delay(100);
    }
  }
  return key;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.println(WATER_BOOT_TEXT);
  lcd.begin(LCD_ROWS, LCD_COLS); 
  lcd.setCursor(0, 0);
  lcd.print(WATER_BOOT_TEXT);
  lcd.setCursor(0, 1);
  lcd.print(ACTION_WATERRING_ON_TEXT);
}

void loop() {
  // put your main code here, to run repeatedly:
  callCommand("STATE");
  ButtonPressed key = readClickButton();
  if(running){
    lcd.setCursor(0, 0);
    lcd.print(WATER_BOOT_TEXT);
    lcd.setCursor(0, 1);
    lcd.print(ACTION_WATERRING_OFF_TEXT);
    if(key == ButtonPressed::SELECT){
      lcd.clear();
      callCommand("OFF");
      running = false;
    }
  }
  else{
    lcd.setCursor(0, 0);
    lcd.print(WATER_BOOT_TEXT);
    lcd.setCursor(0, 1);
    lcd.print(ACTION_WATERRING_ON_TEXT);
    if(key == ButtonPressed::SELECT){
      lcd.clear();
      callCommand("ON");
      running = true;
    }
  }
}