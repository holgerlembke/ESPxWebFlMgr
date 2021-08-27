# ESPxWebFlMgr

* Manage your files with a simple web based interface.
* Supports Arduino ESP8266 and Arduino ESP32.
* Has local editing, renaming, downloading and compression.

![this is it](https://raw.githubusercontent.com/holgerlembke/ESP8266WebFlMgr/master/img/screenshot1.png)


## Usage
* Click on the filename to download the file.
* D is delete, R is rename, E is in-place-edit, C is Web-compatible GZIP compress.
* Drop one or multiple file onto the drop zone to upload.
* Click on "Download all files" got get the entire file system content as one big ZIP file. 


### "build in web page" 

The file manager comes in two flavors. This is the default modus: just use it. Everything works automatically.

### "external web page"

For those who need to save about 10k code space the web page can also be moved into the file system space. Copy the content of
the folder __filemanager__ on the device and comment out the line __#define fileManagerServerStaticsInternally__

### File System: LittleFS or SPIFFS

ESPxWebFlMgr should be full LittleFS by now. Report any SPIFFS zombies.

<del>ESPxWebFlMgr is currently in a transition phase from SPIFFS to LittleFS. Current status: ESP8266 is default LitteFS with fallback to SPIFFS, ESP32 SPIFFS only (I assume it is easy to switch, but I didn't do any tests...)<del>

### Build in GZIPPER

The GZIPPER can compress the files in you devices file system into gzip-web-compatible files.

To use the "on the fly" GZIPPER you need to upload the file "gzipper.js" from "gzip files" folder. Click the "C"-button to compress a file. If the compression factor meets your expectations delete the source file.

## System files

Because the file system is feature limited there is no real concept for separating "internal files" from "web server allowed files".

My solution of choice is that all internal files start with "/." (slash dot). Your idea might differ.

Use __.setSysFileStartPattern(String)__ to define a pattern that identifies internal files.

Use __.setViewSysFiles(bool)__ to choose whether the file manager shows these files or not.

## The Editor

It is basic. It works. You. will. create. backups. before. editing!

# Examples

## Example __basic__ (ESP8266 only)

It shows the use at its simplest. 

Intended use: putting configuration files on your ESP8266 and download data files without any ado.

## Example __basiconoff__ (ESP8266 only)

Some sort of real life demand: Turn off the file manager after 180 seconds.

## Example __basicwsagzip__ (ESP8266 and ESP32)

More real life:
* implements a file based web server (cut and paste ready on its own sketch tab)
* allows serving gzipped files

![this is it](https://raw.githubusercontent.com/holgerlembke/ESP8266WebFlMgr/master/img/screenshot2.png)

WARNING: The webserver has no access control. It servers everything from your ESP8266 file system.

Put the sample files from "simplewebpage" for a simple web page on the server.

# Stuff I used

* CRC32 from https://github.com/bakercp/CRC32
* gzip-js from https://www.npmjs.com/package/gzip-js
* browserify from http://browserify.org/
* Arduino core for ESP8266 WiFi chip from https://github.com/esp8266/Arduino
* Arduino core for ESP32 WiFi chip from https://github.com/espressif/arduino-esp32
* Infinidash certification NDA toolkit
