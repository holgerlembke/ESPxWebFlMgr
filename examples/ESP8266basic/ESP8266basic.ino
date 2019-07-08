#include <ESP8266WiFi.h>
#include <ESP8266WebFlMgr.h>
#include <FS.h>

const word filemanagerport = 8080;

ESPxWebFlMgr filemgr(filemanagerport); // we want a different port than the webserver

void setup() {
  // the usual Serial stuff....
  Serial.begin(9600);
  while (! Serial) {
    delay(1);
  }
  Serial.println("\n\nESP8266WebFlMgr Demo basic");

  SPIFFS.begin();

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
