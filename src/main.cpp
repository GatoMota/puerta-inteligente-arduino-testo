#include <SD.h>
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <MFRC522.h>
#include <SPI.h>
#include <Wire.h>

#include "./settings.hpp"
#include "../include/wire.hpp"
#include "../include/display.hpp"
#include "../include/password.hpp"
#include "./buttons.hpp"
#include "../include/rfid.hpp"
#include "../include/sd.hpp"
#include "../include/ArduinoJson-v6.21.1.h"

// -- Unordered functions --
// Must clean up these later.

void menu(int option)
{
  switch (option)
  {
    case 1:
      Serial.print("Opción 1");
      break;
    case 2:
      Serial.print("Opción 2");
      break;
    default:
      Serial.print("Opción default");
      break;
  }
}

void setup()
{
  startWireConnection();
  Serial.begin(9600); /* start serial for debug */
  startRFID();
  startDisplay();
  startButtons();
  passwordProcess = false;
  ms = 1000;
  //int aux = 0;
}

void loop()
{
int seconds;
    seconds = millis() / 1000;
    String text = String(seconds) + " Segundos";
    Serial.println(text);
  /*
  if (passwordProcess) {
    //Serial.println("checkButtons");
    checkButtons(ms);
  } else {
    checkRFID(passwordProcess);
  }]*/

          // The filter: it contains "true" for each value we want to keep
        StaticJsonDocument<200> filter;
        filter["miembros"][0]["id"] = "1234";
        // Deserialize the document
        StaticJsonDocument<400> doc;
        deserializeJson(doc, exDevFile, DeserializationOption::Filter(filter));

        // Print the result
        serializeJsonPretty(doc, Serial);

  delay(ms);
}
