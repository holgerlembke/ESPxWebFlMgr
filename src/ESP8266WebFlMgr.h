// inline guard. Did I mention that c/c++ is broken by design?
#ifndef ESP8266WebFlMgr_h
#define ESP8266WebFlMgr_h

#include <Arduino.h>
#include <inttypes.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>

/* undefine this to save about 10k code space. 
   it requires to put the files from "<library>/filemanager" into the FS. No free lunch.
*/
#define fileManagerServerStaticsInternally  

// will show the Edit-Button for every file type, even binary and such.
//#define fileManagerEditEverything

class ESP8266WebFlMgr {
  private:
    word _Port ;
    ESP8266WebServer * fileManager = NULL;
	bool _ViewSysFiles = false;
	String _SysFileStartPattern = "/.";
    File fsUploadFile;
	String _backgroundColor = "black";

    void fileManagerNotFound(void);
    String dispIntDotted(size_t i);
    String dispFileString(size_t fs);
	String CheckFileNameLengthLimit(String fn);
	
	// the webpage
    void fileManagerIndexpage(void);
	void fileManagerJS(void);
    void fileManagerCSS(void);
	void fileManagerGetBackGround(void);
	
	// javascript xmlhttp includes
	String colorline(int i);
	String escapeHTMLcontent(String html);
    void fileManagerFileListInsert(void);
	void fileManagerFileEditorInsert(void);
	boolean allowAccessToThisFile(const String filename);
    void fileManagerCommandExecutor(void);
	void fileManagerReceiverOK(void);
	void fileManagerReceiver(void);
	
	// Zip-File uncompressed/stored
	void getAllFilesInOneZIP(void);
    int WriteChunk(const char* b, size_t l);

  public:
    ESP8266WebFlMgr(word port);
    virtual ~ESP8266WebFlMgr();
	
	void begin();
	void end();
    virtual void handleClient();

    // This must be called before the webpage is loaded in the browser...
	// must be a valid css color name, see https://en.wikipedia.org/wiki/Web_colors
    void setBackGroundColor(const String backgroundColor);
	
	void setViewSysFiles(bool vsf);
	bool getViewSysFiles(void);
	
	void setSysFileStartPattern(String sfsp);
	String getSysFileStartPattern(void);
};

#endif

/*
      History
	  
	    -- 2019-07-06
	       + "Download all files" creates a zip file from all files and lets it download
		   + option to set background color
		   - html5 fixes
		   
	    -- 2019-07-03
	       + Public Release on https://github.com/holgerlembke/ESP8266WebFlMgr
	  
	  
	  Things to do
	  
	    ?? unify file system access for SPIFFS, LittleFS and SDFS
		?? Port to ESP32
    



*/



