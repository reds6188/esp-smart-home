#include "main.h"

Button Btn1(BTN_1, 80);
Button Btn2(BTN_2, 80);
Led LedR(RED_LED);
Led LedY(YLW_LED);
Led LedG(GRN_LED);
WiFiHandler wifi_handler("esp-smart-home");

Timer TimerRefresh;
bool apEnabled;

void fToggleWifi(void) {
	apEnabled = !apEnabled;
	if(apEnabled) {
		console.info(MAIN_T, "Starting AP...");
		wifi_handler.setApSsid("ESP_Smart_Home_AP");
		wifi_handler.switchMode(WIFI_AP_STA);
		wifi_handler.startMDNS("esp-smart-home");
	}
	else {
		console.info(MAIN_T, "Stopping AP...");
		wifi_handler.stopMDNS();
		wifi_handler.switchMode(WIFI_STA);
	}
}

void setup() {
	console.header(DOUBLE_DASHED, LOG_BLUE, 80, "START INITIALIZATION");
	LedR.set();
	LedY.set();
	LedG.set();
	printDeviceInfo();
	printResetReason();
	Btn1.onPress(softwareReset);
	//Btn2.onPress(printChipTemp);
	Btn2.onPress(fToggleWifi);
	wifi_handler.begin(WIFI_STA);
	startWebServer();
	addFileToServe("/", "text/html", INDEX_HTML, sizeof(INDEX_HTML));
	addFileToServe("/favicon.svg", "image/svg+xml", FAVICON_SVG, sizeof(FAVICON_SVG));
	addFileToServe("/style.css", "text/css", STYLE_CSS, sizeof(STYLE_CSS));
	addFileToServe("/colors.css", "text/css", COLORS_CSS, sizeof(COLORS_CSS));
	addFileToServe("/main.js", "text/javascript", MAIN_JS, sizeof(MAIN_JS));
	LedR.reset();
	LedY.reset();
	LedG.startBlink(200,200);
	console.header(DOUBLE_DASHED, LOG_BLUE, 80, "END INITIALIZATION");
}

void loop() {
	Btn1.loop();
	Btn2.loop();
	LedG.loop();
	if(TimerRefresh.elapsedX1ms(100)) {
		TimerRefresh.trigger();
		LedY.toggle();
	}
}