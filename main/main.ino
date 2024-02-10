#include <LiquidCrystal.h>

#include <WiFiNINA.h>
#include "wifi_settings.h"

// The pins it is connected to on the arduino
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);

  Serial.println("Started");

  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("                ");
  lcd.setCursor(0,0);
  lcd.print("Welcome!");

  if(WiFi.status() == WL_NO_MODULE) 
  {
    Serial.println("Communication with WiFi module failed!");
    lcd.setCursor(0,0);
    lcd.print("Couldnt talk to ");
    lcd.setCursor(0,1);
    lcd.print("WiFi module!");
    while(true);
  }
}

void loop() {

}