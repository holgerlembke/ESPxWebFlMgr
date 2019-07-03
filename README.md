# ESP8266WebFlMgr
Manage your SPIFFS/LittleFS files with a simple web based interface

![this is it](https://raw.githubusercontent.com/holgerlembke/ESP8266WebFlMgr/master/img/screenshot1.png)

## Usage
* Click on the filename to download the file.
* D is delete, R is rename, E is in-place-edit.
* Drop one or multiple file onto the drop zone to upload.

## System files

Because the SPIFFS file system is feature limited there is no real concept for separating "internal files" from "web server allowed files".

My solution of choice is that all internal files start with "/." (slash dot). Your idea might differ.

Use __.setSysFileStartPattern(String)__ to define a pattern that identifies internal files.

Use __.setViewSysFiles(bool)__ to choose whether the file manager shows these files or not.

## The Editor

It is very basic. It will fail in a lot of cases. Use it as fast file viewer or if in distress. Instead I would recommend editing with Notepad++ or Visual Studio Code and upload the files.

# Examples

## Example __basic__

It shows the use at its simplest. 

Intended use: putting configuration files on your ESP8266 and fetching data files without any ado.

## Example __basiconoff__

Some sort of real life demand: Turn off the file manager after 180 seconds.

## Example __basicwsagzip__

More real life:
* implements a file based web server (cut and paste ready on its own sketch tab)
* allows serving gzipped files
* has an "on the fly" gzipper-tool inside the file manager

![this is it](https://raw.githubusercontent.com/holgerlembke/ESP8266WebFlMgr/master/img/screenshot2.png)

WARNING: The webserver has no access control. It servers everything from your ESP8266 file system.

To use the "on the fly" gzipper-tool you need to put the file "gzipper.js" from "gzip files" folder on the webserver. Click the "C"-button to compress a file. If the compression factor meets your expectations delete the source file.


