#include <LiquidCrystal.h>

#include <WiFiNINA.h>
#include "wifi_settings.h"

// The pins it is connected to on the arduino
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int status = WL_IDLE_STATUS;

WiFiServer server(80);

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

  lcd.setCursor(0,0);
  lcd.print("ip:");
  IPAddress ip = WiFi.localIP();
  lcd.print(ip);
  lcd.setCursor(0,1);
  lcd.print("Connected!      ");
  server.begin();
}

void loop() {
  // Accept connections on web server
  WiFiClient client = server.available();
  if (client)
  {
    boolean blank = true;
    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();
        Serial.write(c);
        if (c == '\n' && blank)
        {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();
          client.println("<!docktype html>");
          client.println("<html>");
          client.println("<head><title>Spotuino</title></head>");
          client.println("<body><h1>Hello, World!</h1></body>");
          client.println("</html>");
          break;
        }

        if (c == '\n')
        {
          blank = true;
        } else if (c != '\r')
        {
          blank = false;
        }
      }
    }
    
    delay(1);

    client.stop();
  }
}
