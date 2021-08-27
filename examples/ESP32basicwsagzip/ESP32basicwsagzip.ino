#include <WiFi.h>
#include <FS.h>
#include <LittleFS.h>
#include <WebServer.h>
// getting access to the nice mime-type-table and getContentType()
#include <detail/RequestHandlersImpl.h>

#include <ESPxWebFlMgr.h>

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
  Serial.println("\n\nESP32WebFlMgr Demo basicwsagzip"); // BASIC and WebServer And GZIPper

  if (!LittleFS.begin(true)) { // Format if failed.
    Serial.println("LittleFS Mount Failed");
    return;
  }

  // login into WiFi
  WiFi.begin(hlssid.c_str(), hlpwd.c_str());
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
