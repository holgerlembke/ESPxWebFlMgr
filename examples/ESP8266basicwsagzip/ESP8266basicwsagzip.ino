#include <ESP8266WiFi.h>
#include <ESPxWebFlMgr.h>
// getting access to the nice mime-type-table and getContentType()
#include "detail/RequestHandlersImpl.h"
#include <FS.h>

/*

 This example has an additional web server on port 80.
 It serves files from SPIFFS. Upload the files from "simplewebpage" for a quick start.

 Usage: copy the sketch tab, call setup+loop as we all know.
 
*/

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
  Serial.println("\n\nESP8266WebFlMgr Demo basicwsagzip"); // BASIC and WebServer And GZIPper

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
    Serial.print("Webserver is at http://");
    Serial.print(WiFi.localIP());
    Serial.print("/");
    Serial.println();
  }

  setupWebserver();

  filemgr.begin();
}

void loop() {
  filemgr.handleClient();
  loopWebServer();
}
