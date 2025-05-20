#include "main.h"

Button Btn1(BTN_1, 80);
Button Btn2(BTN_2, 80);
Led LedR(RED_LED);
Led LedY(YLW_LED);
Led LedG(GRN_LED);
WiFiHandler wifi_handler("esp-smart-home");

Timer TimerRefresh;

void setup() {
	console.header(DOUBLE_DASHED, LOG_BLUE, 80, "START INITIALIZATION");
	LedR.set();
	LedY.set();
	LedG.set();
	printDeviceInfo();
	printResetReason();
	Btn1.onPress(softwareReset);
	Btn2.onPress(printChipTemp);
	wifi_handler.begin(WIFI_STA);
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