/*
  The define ESPxWebFlMgr_FileSystem holds the selected filesystem in (surprise!) ESPxWebFlMgr.

  You can
    -- ignore it. Then LittleFS will be selected and you need to use LittleFS.whatever().
    -- use it. Like in this example.
    -- change it. Set a new value *BEFORE* #including <ESPxWebFlMgr.h>
       Only "#define ESPxWebFlMgr_FileSystem SPIFFS" makes any sense.
*/ 

// Board settings
// Board: "Generic ESP8266 Module"
// Builtin Led: "2"
// Upload Speed: "115200"
// CPU Frequency: "160 MHz"
// Crystal Frequency: "26 MHz"
// Flash Size: "4MB (FS:2MB OTA:~1019KB)"
// Flash Mode: "DOUT (compatible)"
// Flash Frequency: "40MHz"
// Reset Method: "dtr (aka nodemcu)"
// Debug port: "Disabled"
// Debug Level: "Keine"
// lwIP Variant: "v2 Lower Memory"
// VTables: "Flash"
// Exceptions: "Legacy (new can return nullptr)"
// Erase Flash: "Only Sketch"
// Espressif FW: "nonos-sdk 2.2.1+100 (190703)"
// SSL Support: "All SSL ciphers (most compatible)"

#include <ESP8266WiFi.h>
#include <ESPxWebFlMgr.h>

const word filemanagerport = 8080;

ESPxWebFlMgr filemgr(filemanagerport); // we want a different port than the webserver

void setup() {
  // the usual Serial stuff....
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n\nESP8266WebFlMgr Demo basic");

  ESPxWebFlMgr_FileSystem.begin();

  // login into WiFi
  WiFi.begin("ssid", "pwd");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1);
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("Open Filemanager with http://");
    Serial.print(WiFi.localIP());
    Serial.print(":");
    Serial.print(filemanagerport);
    Serial.print("/");
    Serial.println();
  }

  filemgr.begin();
}

void loop() {
  filemgr.handleClient();
}