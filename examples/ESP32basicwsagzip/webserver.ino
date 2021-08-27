// WARNING: This webserver has no access control. It servers everything from your ESP32 file system.
// WARNING: This webserver has no access control. It servers everything from your ESP32 file system.
WebServer * webserver = NULL;
const word webserverServerPort = 80;
const String webserverDefaultname = "/index.html";
// WARNING: This webserver has no access control. It servers everything from your ESP32 file system.
// WARNING: This webserver has no access control. It servers everything from your ESP32 file system.

//*****************************************************************************************************
void setupWebserver(void) {
  webserver = new WebServer(webserverServerPort);

  // ACCEPT-ENCODING  gzip, deflate, br
  const char * headerkeys[] = {"ACCEPT-ENCODING"} ;
  size_t headerkeyssize = sizeof(headerkeys) / sizeof(char*);
  //ask server to track these headers
  webserver->collectHeaders(headerkeys, headerkeyssize );

  // add your .ons here
  // ...
  // example for data requester
  webserver->on("/d", webserverServerDataRequest);

  // Everything else is served by this.
  webserver->onNotFound(webserverServerNotFound);
  webserver->begin();
}

//*****************************************************************************************************
void webserverServerNotFound(void) {
  genericWebserverServerNotFound(webserver);
}

//*****************************************************************************************************
void loopWebServer(void) {
  if (webserver) {
    webserver->handleClient();
  }
}


//*****************************************************************************************************
//*.on-Event Handlers
//*****************************************************************************************************
void webserverServerDataRequest(void) {
  webserver->send(200, F("text/plain"), F("Wonderfull."));
  delay(1);
}


//*****************************************************************************************************
//*internals.
//*****************************************************************************************************
// 404
void genericWebServerHandleNotFound(WebServer * webserver) {
  /** /
    Serial.print(webserver->client().remoteIP().toString());
    Serial.print(F(" 404: "));
    Serial.println(webserver->uri());
    /**/

  String message = "File Not Found\n\n";
  message += "URI: ";
  message += webserver->uri();
  message += "\nhostheader: ";
  message += webserver->hostHeader();
  message += "\nMethod: ";
  message += (webserver->method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += webserver->args();
  message += "\n";
  for (uint8_t i = 0; i < webserver->args(); i++) {
    message += " " + webserver->argName(i) + ": " + webserver->arg(i) + "\n";
  }
  message += "\nHeaders: ";
  message += webserver->headers();
  message += "\n";
  for (uint8_t i = 0; i < webserver->headers(); i++) {
    message += " " + webserver->headerName(i) + ": " + webserver->header(i) + "\n";
  }

  // IE will mindesten 512 Byte, um es anzuzeigen, sonst interne IE-Seite....
  while (message.length() < 512) {
    message += "                         \n";
  }
  webserver->send(404, "text/plain", message);
}

//*****************************************************************************************************
void genericWebserverServerNotFound(WebServer * webserver) {
  String uri = webserver->uri();

  // default name
  if (uri == "/") {
    uri = webserverDefaultname;
  }

  String contentTyp = StaticRequestHandler::getContentType(uri);

  // Are we allowd to send compressed data?
  // (What is more expensive? Checking LittleFS or header first?)
  if (webserver->hasHeader("ACCEPT-ENCODING")) {
    if (webserver->header("ACCEPT-ENCODING").indexOf("gzip") != -1) {
      // gzip version exists?
      if (LittleFS.exists(uri + ".gz"))  {
        uri += ".gz";
      }
    }
  }

  if (LittleFS.exists(uri)) {
    File f = LittleFS.open(uri, "r");
    if (f) {
      if (webserver->streamFile(f, contentTyp) != f.size()) {
        Serial.println(F("Panic: Sent less data than expected!"));
      }
      f.close();
    }
  } else {
    genericWebServerHandleNotFound(webserver);
  }

  delay(1);
}
