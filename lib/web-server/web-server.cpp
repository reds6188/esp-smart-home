#include "web-server.h"

AsyncWebServer server(80);

void startWebServer(void)
{
    if(!SPIFFS.begin(false, "/spiffs", 10, "spiffs"))
    {
        console.error(HTTP_T, "An Error has occurred while mounting SPIFFS partition");
        return;
    }
    else {
        console.success(HTTP_T, "SPIFFS partition has mounted");
    }

	#ifdef ASYNCWEBSERVER_REGEX
    server.on("^(\\/.+\\/)*(.+)\\.(.+)$", HTTP_GET, [](AsyncWebServerRequest *request){
        String dir = request->pathArg(0);
        String name = request->pathArg(1);
        String ext = request->pathArg(2);
        String MIMEtype = "text/plain";
        String path = dir + name + "." + ext;
        if(!ext.compareTo("svg")) {
            console.log(HTTP_T, "Serving SVG file: " + dir + name);
            MIMEtype = "image/svg+xml";
        }
        else if(!ext.compareTo("css")) {
            console.log(HTTP_T, "Serving CSS file: " + dir + name);
            MIMEtype = "text/css";
        }
        else if(!ext.compareTo("js")) {
            console.log(HTTP_T, "Serving JS file: " + dir + name);
            MIMEtype = "text/javascript";
        }
        else if(!ext.compareTo("ico")) {
            console.log(HTTP_T, "Serving ICO file: " + dir + name);
            MIMEtype = "image/x-icon";
        }
        else
            console.log(HTTP_T, "ERROR: path not recognized");
        request->send(SPIFFS, path, MIMEtype);
    });
	#endif
    
    server.onNotFound([](AsyncWebServerRequest *request){
        console.log(HTTP_T, "ERROR 404 - The content you are looking for was not found.");
		console.log(HTTP_T, "URL: " + request->url());
        request->send(404, "text/plain", "ERROR 404 - The content you are looking for was not found.");
    });

    // Start server
    delay(100);
    server.begin();

    console.success(HTTP_T, "Web server was set successfully!");
}

void stopWebServer(void) {
    server.reset();
    server.end();
    SPIFFS.end();
}

void addGetCallback(const char * uri, String (*func)(uint8_t*)) {
    server.on(uri, HTTP_GET, [func](AsyncWebServerRequest *request) {
        console.info(HTTP_T, "Received GET request: \"" + String(request->url()) + "\"");
        String payload = func(NULL);
        if(payload.length() > 24) {
            console.info(HTTP_T, payload.substring(0,24) + " ...");
        }
        else
            console.info(HTTP_T, payload);
        request->send(200, "text/json", payload);
    });
}

void addPostCallback(const char * uri, String (*func)(uint8_t*)) {
    server.on(uri, HTTP_POST, [](AsyncWebServerRequest *request) {
    }, [](AsyncWebServerRequest *request, const String& filename, size_t index, uint8_t *data, size_t len, bool final) {
    }, [func](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
        //String payload = func(request->url(), data);
        console.info(HTTP_T, "Received POST request: \"" + String(request->url()) + "\"");
        String payload = func(data);
        console.log(HTTP_T, payload);
        request->send(200, "text/json", payload);
    });
}

void addFileToServe(const char * uri, const char * mime_type, const uint8_t * data, int size) {
	server.on(uri, [mime_type, data, size](AsyncWebServerRequest *request) {
		console.log(HTTP_T, "Serving \"" + String(request->url()) + "\" (size : " + String(size) + ")");
		request->send(200, mime_type, data, size);
	});
}