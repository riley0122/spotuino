#include <LiquidCrystal.h>

#include <WiFiNINA.h>
#include "wifi_settings.h"

// The pins it is connected to on the arduino
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int status = WL_IDLE_STATUS;

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

  String fv = WiFi.firmwareVersion();
  bool secondLineOccupied = false;
  if (fv < WIFI_FIRMWARE_LATEST_VERSION)
  {
    Serial.println("Please update your firmware!");
    lcd.setCursor(0,1);
    lcd.print("fw update avail");
    secondLineOccupied = true;
  }

  while (status != WL_CONNECTED)
  {
    Serial.print("Connecting to ");
    Serial.println(SSID);

    status = WiFi.begin(SSID, PASS);
    if(secondLineOccupied)
    {
      lcd.setCursor(0,0);
    } else
    {
      lcd.setCursor(0,1);
    }

    int dots = 8;
    for (int i = 0; i < dots; ++i) 
    {
      if(secondLineOccupied)
      {
        lcd.setCursor(0,0);
      } else
      {
        lcd.setCursor(0,1);
      }
      lcd.print("Connecting");
      for(int j = 0; j < i; ++j){
        lcd.print(".");
        delay(10000/dots);
      }
    }
  }

  lcd.setCursor(0,1);
  lcd.print("Connected!");
}

void loop() {

}
