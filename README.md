# ESP8266WebFlMgr
Manage your SPIFFS/LittleFS files with a simple web based interface

![this is it](https://raw.githubusercontent.com/holgerlembke/ESP8266WebFlMgr/master/img/screenshot.png)

## Usage
* Click on the filename to download the file.
* D is delete, R is rename. 
* Drop one or multiple file onto the drop zone to upload.

## System files

Because the SPIFFS file system is feature limited there is no real concept for separating "internal files" from "web server allowed files".

My solution of choice is that all internal files start with "/." (slash dot). Your idea might differ.

Use __.setSysFileStartPattern(String)__ to define a pattern that identifies internal files.

Use __.setViewSysFiles(bool)__ to choose whether the file manager shows these files or not.




