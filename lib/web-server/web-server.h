#ifndef WEB_SERVER_H_
#define WEB_SERVER_H_

#include <Arduino.h>
#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>
#include <console.h>

#define HTTP_T      "HTTP"  // HTTP console tag

void startWebServer(void);
void stopWebServer(void);
void addGetCallback(const char * uri, String (*func)(uint8_t*));
void addGetCallback(const char * uri, String (*func)(void));
void addPostCallback(const char * uri, String (*func)(uint8_t*));
void addFileToServe(const char * uri, const char * mime_type, const uint8_t * data, int size);

#endif  /* WEB_SERVER_H_ */