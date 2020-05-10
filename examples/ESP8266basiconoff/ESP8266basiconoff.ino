#include <ESP8266WiFi.h>
#include <ESPxWebFlMgr.h>
#include <FS.h>

const word filemanagerport = 8080;

const String hlssid ="..";
const String hlpwd = "..";

ESPxWebFlMgr filemgr(filemanagerport); // we want a different port than the webserver

void setup() {
  // the usual Serial stuff....
  Serial.begin(115200);
  while (! Serial) {
    delay(1);
  }
  Serial.println("\n\nESP8266WebFlMgr Demo basiconoff");

  SPIFFS.begin();

  // login into WiFi
  WiFi.begin(hlssid, hlpwd);
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


  static unsigned long ticker = 0;
  static int seconds = 3 * 60;
  if ( (seconds > 0) && (millis() - ticker > 1000) ) {
    ticker = millis();
    seconds--;
    if (seconds == 0) {
      Serial.println(F("Filemanager turned off."));
      filemgr.end();
    }
  }
}