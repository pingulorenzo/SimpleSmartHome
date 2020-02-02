#include "gui.h"

volatile int count = 0;
volatile int countControl = 0;
volatile int countTemp = 0;
volatile int countUmid = 0;
volatile int countLuci = 0;
volatile int color = 0;
volatile int countColor = 0;
int controlFlag = 0;
int controlFlagLuci = 0;
int stopTaskOut = 0;
int rooms[] = { 0, 0, 0, 0, 0 };
int controls[] = { 0, 0, 0 };
int stopTaskControl = 2;

int stopTaskTemp = 2;
int stopTaskUmid = 2;
int stopTaskLuci = 2;
int countStopTemp = 0;
int countStop = 0;
int countStopOut = 0;
int countStopUmid = 0;
int countStopLuci = 0;
int countTaskPress = 0;

void selectSoggiorno() {
	if (color) {
		LCD_SetBackColor(Red);
		stopTaskOut = 1;
		stopTaskControl = 0;
		countStop = 0;
		rooms[0] = 1;

	} else {
		LCD_SetBackColor(Green);
	}
	LCD_DisplayStringLine(LINE(1), "SOGGIORNO");
	LCD_DrawRect(RECT1_X, RECT1_Y, HEIGHT_RECT1, WIDTH_RECT1);
	LCD_SetBackColor(White);
	LCD_DisplayStringLine(LINE(3), "INGRESSO");
	LCD_DrawRect(RECT2_X, RECT2_Y, HEIGHT_RECT2, WIDTH_RECT2);
	LCD_DisplayStringLine(LINE(5), "CAMERA DA LETTO");
	LCD_DrawRect(RECT3_X, RECT3_Y, HEIGHT_RECT3, WIDTH_RECT3);
	LCD_DisplayStringLine(LINE(7), "SALA DA PRANZO");
	LCD_DrawRect(RECT4_X, RECT4_Y, HEIGHT_RECT4, WIDTH_RECT4);
	LCD_DisplayStringLine(LINE(9), "CUCINA");
	LCD_DrawRect(RECT5_X, RECT5_Y, HEIGHT_RECT5, WIDTH_RECT5);
}

void selectCam1() {
	LCD_SetBackColor(White);
	LCD_DisplayStringLine(LINE(1), "SOGGIORNO");
	LCD_DrawRect(RECT1_X, RECT1_Y, HEIGHT_RECT1, WIDTH_RECT1);
	if (color) {
		LCD_SetBackColor(Red);
		stopTaskOut = 1;
		stopTaskControl = 0;
		countStop = 0;
		rooms[1] = 1;

	} else {
		LCD_SetBackColor(Green);
	}
	LCD_DisplayStringLine(LINE(3), "INGRESSO");
	LCD_DrawRect(RECT2_X, RECT2_Y, HEIGHT_RECT2, WIDTH_RECT2);
	LCD_SetBackColor(White);
	LCD_DisplayStringLine(LINE(5), "CAMERA DA LETTO");
	LCD_DrawRect(RECT3_X, RECT3_Y, HEIGHT_RECT3, WIDTH_RECT3);
	LCD_DisplayStringLine(LINE(7), "SALA DA PRANZO");
	LCD_DrawRect(RECT4_X, RECT4_Y, HEIGHT_RECT4, WIDTH_RECT4);
	LCD_DisplayStringLine(LINE(9), "CUCINA");
	LCD_DrawRect(RECT5_X, RECT5_Y, HEIGHT_RECT5, WIDTH_RECT5);
}

void selectCam2() {
	LCD_SetBackColor(White);
	LCD_DisplayStringLine(LINE(1), "SOGGIORNO");
	LCD_DrawRect(RECT1_X, RECT1_Y, HEIGHT_RECT1, WIDTH_RECT1);
	LCD_DisplayStringLine(LINE(3), "INGRESSO");
	LCD_DrawRect(RECT2_X, RECT2_Y, HEIGHT_RECT2, WIDTH_RECT2);
	if (color) {
		LCD_SetBackColor(Red);
		stopTaskOut = 1;
		stopTaskControl = 0;
		countStop = 0;
		rooms[2] = 1;

	} else {
		LCD_SetBackColor(Green);
	}
	LCD_DisplayStringLine(LINE(5), "CAMERA DA LETTO");
	LCD_DrawRect(RECT3_X, RECT3_Y, HEIGHT_RECT3, WIDTH_RECT3);
	LCD_SetBackColor(White);
	LCD_DisplayStringLine(LINE(7), "SALA DA PRANZO");
	LCD_DrawRect(RECT4_X, RECT4_Y, HEIGHT_RECT4, WIDTH_RECT4);
	LCD_DisplayStringLine(LINE(9), "CUCINA");
	LCD_DrawRect(RECT5_X, RECT5_Y, HEIGHT_RECT5, WIDTH_RECT5);
}

void selectSalaPranzo() {
	LCD_SetBackColor(White);
	LCD_DisplayStringLine(LINE(1), "SOGGIORNO");
	LCD_DrawRect(RECT1_X, RECT1_Y, HEIGHT_RECT1, WIDTH_RECT1);
	LCD_DisplayStringLine(LINE(3), "INGRESSO");
	LCD_DrawRect(RECT2_X, RECT2_Y, HEIGHT_RECT2, WIDTH_RECT2);
	LCD_DisplayStringLine(LINE(5), "CAMERA DA LETTO");
	LCD_DrawRect(RECT3_X, RECT3_Y, HEIGHT_RECT3, WIDTH_RECT3);
	if (color) {
		LCD_SetBackColor(Red);
		stopTaskOut = 1;
		stopTaskControl = 0;
		countStop = 0;
		rooms[3] = 1;

	} else {
		LCD_SetBackColor(Green);
	}
	LCD_DisplayStringLine(LINE(7), "SALA DA PRANZO");
	LCD_DrawRect(RECT4_X, RECT4_Y, HEIGHT_RECT4, WIDTH_RECT4);
	LCD_SetBackColor(White);
	LCD_DisplayStringLine(LINE(9), "CUCINA");
	LCD_DrawRect(RECT5_X, RECT5_Y, HEIGHT_RECT5, WIDTH_RECT5);
}

void selectCucina() {
	LCD_SetBackColor(White);
	LCD_DisplayStringLine(LINE(1), "SOGGIORNO");
	LCD_DrawRect(RECT1_X, RECT1_Y, HEIGHT_RECT1, WIDTH_RECT1);
	LCD_DisplayStringLine(LINE(3), "INGRESSO");
	LCD_DrawRect(RECT2_X, RECT2_Y, HEIGHT_RECT2, WIDTH_RECT2);
	LCD_DisplayStringLine(LINE(5), "CAMERA DA LETTO");
	LCD_DrawRect(RECT3_X, RECT3_Y, HEIGHT_RECT3, WIDTH_RECT3);
	LCD_DisplayStringLine(LINE(7), "SALA DA PRANZO");
	LCD_DrawRect(RECT4_X, RECT4_Y, HEIGHT_RECT4, WIDTH_RECT4);
	if (color) {
		LCD_SetBackColor(Red);
		stopTaskOut = 1;
		stopTaskControl = 0;
		countStop = 0;
		rooms[4] = 1;

	} else {
		LCD_SetBackColor(Green);
	}
	LCD_DisplayStringLine(LINE(9), "CUCINA");
	LCD_DrawRect(RECT5_X, RECT5_Y, HEIGHT_RECT5, WIDTH_RECT5);
}

void displayHeadingControl() {
	LCD_Clear(White);
	LCD_SetBackColor(Red);
	LCD_SetTextColor(Black);
	if (rooms[0]) {
		LCD_DisplayStringLine(LINE(1), "SOGGIORNO");
	} else if (rooms[1]) {
		LCD_DisplayStringLine(LINE(1), "INGRESSO");
	} else if (rooms[2]) {
		LCD_DisplayStringLine(LINE(1), "CAMERA DA LETTO");
	} else if (rooms[3]) {
		LCD_DisplayStringLine(LINE(1), "SALA DA PRANZO");
	} else if (rooms[4]) {
		LCD_DisplayStringLine(LINE(1), "CUCINA");
	}
}

void selectTempControl() {
	if (color) {
		LCD_SetBackColor(Blue);
		controls[0] = 1;
		stopTaskControl = 1;
		stopTaskTemp = 0;
		countStopTemp = 0;
	} else {
		LCD_SetBackColor(Green);
	}
	LCD_DisplayStringLine(LINE(3), "TEMPERATURA");
	LCD_SetBackColor(White);
	LCD_DisplayStringLine(LINE(7), "UMIDITA");
	LCD_DisplayStringLine(LINE(5), "LUCI");
	LCD_DisplayChar(LINE(9), 250, 66);
	LCD_DisplayChar(LINE(9), 265, 65);
	LCD_DisplayChar(LINE(9), 280, 67);
	LCD_DisplayChar(LINE(9), 295, 75);
}

void selectUmidControl() {
	LCD_SetBackColor(White);
	LCD_DisplayStringLine(LINE(3), "TEMPERATURA");
	if (color) {
		LCD_SetBackColor(Blue);
		controls[1] = 1;
		stopTaskControl = 1;
		stopTaskUmid = 0;
		countStopUmid = 0;
	} else {
		LCD_SetBackColor(Green);
	}
	LCD_DisplayStringLine(LINE(7), "UMIDITA");
	LCD_SetBackColor(White);
	LCD_DisplayStringLine(LINE(5), "LUCI");
	LCD_DisplayChar(LINE(9), 250, 66);
	LCD_DisplayChar(LINE(9), 265, 65);
	LCD_DisplayChar(LINE(9), 280, 67);
	LCD_DisplayChar(LINE(9), 295, 75);
}

void selectLuciControl() {
	LCD_SetBackColor(White);
	LCD_DisplayStringLine(LINE(3), "TEMPERATURA");
	LCD_DisplayStringLine(LINE(7), "UMIDITA");
	if (color) {
		LCD_SetBackColor(Blue);
		controls[1] = 1;
		stopTaskControl = 1;
		stopTaskLuci = 0;
		countStopLuci = 0;
	} else {
		LCD_SetBackColor(Green);
	}
	LCD_DisplayStringLine(LINE(5), "LUCI");
	LCD_SetBackColor(White);
	LCD_DisplayChar(LINE(9), 250, 66);
	LCD_DisplayChar(LINE(9), 265, 65);
	LCD_DisplayChar(LINE(9), 280, 67);
	LCD_DisplayChar(LINE(9), 295, 75);
}

int selectBackButtonControl() {
	LCD_SetBackColor(White);
	LCD_DisplayStringLine(LINE(3), "TEMPERATURA");
	LCD_DisplayStringLine(LINE(7), "UMIDITA");
	LCD_DisplayStringLine(LINE(5), "LUCI");
	if (color) {
		LCD_SetBackColor(Blue);
		stopTaskControl = 1;
		stopTaskOut = 0;
		countStopOut = 0;
		return 1;
	} else {
		LCD_SetBackColor(Green);
	}
	LCD_DisplayChar(LINE(9), 250, 66);
	LCD_DisplayChar(LINE(9), 265, 65);
	LCD_DisplayChar(LINE(9), 280, 67);
	LCD_DisplayChar(LINE(9), 295, 75);
	return 0;
}

int selectBackButtonTemp() {
	if (countTemp == 2) {
		LCD_SetBackColor(Green);
	} else {
		LCD_SetBackColor(White);
	}
	LCD_DisplayChar(LINE(9), 250, 66);
	LCD_DisplayChar(LINE(9), 265, 65);
	LCD_DisplayChar(LINE(9), 280, 67);
	LCD_DisplayChar(LINE(9), 295, 75);
	if ((countTemp == 2) && (color)) {
		stopTaskTemp = 1;
		stopTaskControl = 0;
		countStop = 0;
		return 1;
	}
	return 0;
}

int selectBackButtonUmid() {
	if (countUmid == 2) {
		LCD_SetBackColor(Green);
	} else {
		LCD_SetBackColor(White);
	}
	LCD_DisplayChar(LINE(9), 250, 66);
	LCD_DisplayChar(LINE(9), 265, 65);
	LCD_DisplayChar(LINE(9), 280, 67);
	LCD_DisplayChar(LINE(9), 295, 75);
	if ((countUmid == 2) && (color)) {
		stopTaskUmid = 1;
		stopTaskControl = 0;
		countStop = 0;
		return 1;
	}
	return 0;
}

void initialTempDisplay() {
	LCD_Clear(White);
	LCD_SetBackColor(Blue);
	LCD_SetTextColor(Black);
	LCD_DisplayStringLine(LINE(1), "TEMPERATURA");
	LCD_SetBackColor(White);
	LCD_DisplayStringLine(LINE(3), "DESIDERATA");
	LCD_DisplayStringLine(LINE(5), "ATTUALE");
}

void initialUmidDisplay() {
	LCD_Clear(White);
	LCD_SetBackColor(Blue);
	LCD_SetTextColor(Black);
	LCD_DisplayStringLine(LINE(1), "UMIDITA");
	LCD_SetBackColor(White);
	LCD_DisplayStringLine(LINE(3), "DESIDERATA");
	LCD_DisplayStringLine(LINE(5), "ATTUALE");
}

void displayDesiredTemp(char ascii1, char ascii2) {
	LCD_DisplayChar(LINE(3), 215, ascii1);
	LCD_DisplayChar(LINE(3), 230, ascii2);
}

void displayDesiredUmid(char ascii1, char ascii2) {
	LCD_DisplayChar(LINE(3), 215, ascii1);
	LCD_DisplayChar(LINE(3), 230, ascii2);
}

void displayCurrentTemp(char ascii1, char ascii2) {
	LCD_DisplayChar(LINE(5), 215, ascii1);
	LCD_DisplayChar(LINE(5), 230, ascii2);
}

void displayCurrentUmid(char ascii1, char ascii2) {
	LCD_DisplayChar(LINE(5), 215, ascii1);
	LCD_DisplayChar(LINE(5), 230, ascii2);
}

void selectMinusTemp() {
	if (countTemp == 0) {
		LCD_SetBackColor(Green);

	}
	LCD_DisplayChar(LINE(3), 200, 45);
	LCD_SetBackColor(White);
}

void selectPlusTemp() {
	if (countTemp == 1) {
		LCD_SetBackColor(Green);
	} else {
		LCD_SetBackColor(White);
	}
	LCD_DisplayChar(LINE(3), 245, 43);
	LCD_SetBackColor(White);
}

void selectMinusUmid() {
	if (countUmid == 0) {
		LCD_SetBackColor(Green);

	}
	LCD_DisplayChar(LINE(3), 200, 45);
	LCD_SetBackColor(White);
}

void selectPlusUmid() {
	if (countUmid == 1) {
		LCD_SetBackColor(Green);
	} else {
		LCD_SetBackColor(White);
	}
	LCD_DisplayChar(LINE(3), 245, 43);
	LCD_SetBackColor(White);
}

void selectAccendi(int *on, int *off, int *aut) {
	if (color) {
		LCD_SetBackColor(Blue);
		LCD_DisplayStringLine(LINE(3), "ACCENDI");
		*on = 1;
		*off = 0;
		*aut = 0;
	} else {
		LCD_SetBackColor(Green);
		LCD_DisplayStringLine(LINE(3), "ACCENDI");
	}
	LCD_SetBackColor(White);
	LCD_DisplayStringLine(LINE(5), "SPEGNI");
	LCD_DisplayStringLine(LINE(7), "AUTO");
	LCD_DisplayChar(LINE(9), 250, 66);
	LCD_DisplayChar(LINE(9), 265, 65);
	LCD_DisplayChar(LINE(9), 280, 67);
	LCD_DisplayChar(LINE(9), 295, 75);
}

void selectSpegni(int *on, int *off, int *aut) {
	LCD_SetBackColor(White);
	LCD_DisplayStringLine(LINE(3), "ACCENDI");
	if (color) {
		LCD_SetBackColor(Blue);
		LCD_DisplayStringLine(LINE(5), "SPEGNI");
		*on = 0;
		*off = 1;
		*aut = 0;
	} else {
		LCD_SetBackColor(Green);
		LCD_DisplayStringLine(LINE(5), "SPEGNI");
	}
	LCD_SetBackColor(White);
	LCD_DisplayStringLine(LINE(7), "AUTO");

	LCD_DisplayChar(LINE(9), 250, 66);
	LCD_DisplayChar(LINE(9), 265, 65);
	LCD_DisplayChar(LINE(9), 280, 67);
	LCD_DisplayChar(LINE(9), 295, 75);
}

void selectAuto(int *on, int *off, int *aut) {
	LCD_SetBackColor(White);
	LCD_DisplayStringLine(LINE(3), "ACCENDI");
	LCD_DisplayStringLine(LINE(5), "SPEGNI");
	if (color) {
		LCD_SetBackColor(Blue);
		LCD_DisplayStringLine(LINE(7), "AUTO");
		*on = 0;
		*off = 0;
		*aut = 1;
	} else {
		LCD_SetBackColor(Green);
		LCD_DisplayStringLine(LINE(7), "AUTO");
	}
	LCD_SetBackColor(White);
	LCD_DisplayChar(LINE(9), 250, 66);
	LCD_DisplayChar(LINE(9), 265, 65);
	LCD_DisplayChar(LINE(9), 280, 67);
	LCD_DisplayChar(LINE(9), 295, 75);
}

int selectBackButtonLuci() {
	LCD_SetBackColor(White);
	LCD_DisplayStringLine(LINE(3), "ACCENDI");
	LCD_DisplayStringLine(LINE(5), "SPEGNI");
	LCD_DisplayStringLine(LINE(7), "AUTO");
	if (color) {
		LCD_SetBackColor(Blue);
		stopTaskLuci = 1;
		stopTaskControl = 0;
		countStop = 0;
		return 1;
	} else {
		LCD_SetBackColor(Green);
	}
	LCD_DisplayChar(LINE(9), 250, 66);
	LCD_DisplayChar(LINE(9), 265, 65);
	LCD_DisplayChar(LINE(9), 280, 67);
	LCD_DisplayChar(LINE(9), 295, 75);
	return 0;
}

void displayOnOff(int on, int off, int aut) {
	LCD_SetBackColor(White);
	if ((off == 1) && (!on) && (!aut)) {
		LCD_DisplayChar(LINE(5), 230, 79);
		LCD_DisplayChar(LINE(5), 245, 70);
		LCD_DisplayChar(LINE(5), 260, 70);
	}
	if ((on == 1) && (!off) && (!aut)) {
		LCD_DisplayChar(LINE(3), 230, 79);
		LCD_DisplayChar(LINE(3), 245, 78);
	}
	if ((aut == 1) && (!off) && (!on)) {
		LCD_DisplayChar(LINE(7), 230, 79);
		LCD_DisplayChar(LINE(7), 245, 75);
	}
}

void initialSettingsLuci() {
	LCD_Clear(White);
	LCD_SetBackColor(Blue);
	LCD_SetTextColor(Black);
	LCD_DisplayStringLine(LINE(1), "LUCE");
}
