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

    void fileManagerNotFound(void);
    String dispIntDotted(size_t i);
    String dispFileString(size_t fs);
	String CheckFileNameLengthLimit(String fn);
	
	// the webpage
    void fileManagerIndexpage(void);
	void fileManagerJS(void);
    void fileManagerCSS(void);
	
	// javascript xmlhttp includes
	String colorline(int i);
    void fileManagerFileListInsert(void);
	void fileManagerFileEditorInsert(void);
	boolean allowAccessToThisFile(const String filename);
    void fileManagerCommandExecutor(void);
	void fileManagerReceiverOK(void);
	void fileManagerReceiver(void);

  public:
    ESP8266WebFlMgr(word port);
    virtual ~ESP8266WebFlMgr();
	
	void begin();
	void end();
    virtual void handleClient();
	
	void setViewSysFiles(bool vsf);
	bool getViewSysFiles(void);
	
	void setSysFileStartPattern(String sfsp);
	String getSysFileStartPattern(void);
};


#endif