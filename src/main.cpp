#include "main.h"

Button Btn1(BTN_1, 80);
Button Btn2(BTN_2, 80);

void espRestart(void) {
	ESP.restart();
}

void setup() {
	console.header(DOUBLE_DASHED, LOG_BLUE, 80, "START INITIALIZATION");
	Btn1.onPress(espRestart);
	Btn2.onPress(espRestart);
	console.header(DOUBLE_DASHED, LOG_BLUE, 80, "END INITIALIZATION");
}

void loop() {
	Btn1.loop();
	Btn2.loop();
}