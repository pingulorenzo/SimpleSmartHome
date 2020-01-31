#include "ee.h"

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "stm32f4_discovery_lcd.h"
#include "lcd_log.h"

#include <stdio.h>

#define RECT1_X           (0)
#define RECT1_Y           (20)

#define HEIGHT_RECT1		(150)
#define WIDTH_RECT1			(30)

#define RECT2_X           RECT1_X
#define RECT2_Y           RECT1_Y + 48

#define HEIGHT_RECT2		HEIGHT_RECT1 + 100
#define WIDTH_RECT2			WIDTH_RECT1

#define RECT3_X           RECT2_X
#define RECT3_Y           RECT2_Y + 48

#define HEIGHT_RECT3		HEIGHT_RECT2
#define WIDTH_RECT3			WIDTH_RECT2

#define RECT4_X           RECT3_X
#define RECT4_Y           RECT3_Y + 48

#define HEIGHT_RECT4		HEIGHT_RECT1 + 80
#define WIDTH_RECT4			WIDTH_RECT3

#define RECT5_X           RECT4_X
#define RECT5_Y           RECT4_Y + 48

#define HEIGHT_RECT5		100
#define WIDTH_RECT5			WIDTH_RECT4

#define ASCI1MIN			49
#define ASCI1MAX			51

#define ASCI2MIN			53
#define ASCI2MAX			48

#define ASCI1DEFAULT		50
#define ASCI2DEFAULT		51

#define NROOMS				5
/*
 * SysTick ISR2
 */
volatile int count = 0;
volatile int countControl = 0;
volatile int countTemp = 0;
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
ISR2( systick_handler) {
	/* count the interrupts, waking up expired alarms */
	CounterTick(myCounter);
}
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
	LCD_DisplayStringLine(LINE(3), "CAMERA DA LETTO 1");
	LCD_DrawRect(RECT2_X, RECT2_Y, HEIGHT_RECT2, WIDTH_RECT2);
	LCD_DisplayStringLine(LINE(5), "CAMERA DA LETTO 2");
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
	LCD_DisplayStringLine(LINE(3), "CAMERA DA LETTO 1");
	LCD_DrawRect(RECT2_X, RECT2_Y, HEIGHT_RECT2, WIDTH_RECT2);
	LCD_SetBackColor(White);
	LCD_DisplayStringLine(LINE(5), "CAMERA DA LETTO 2");
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
	LCD_DisplayStringLine(LINE(3), "CAMERA DA LETTO 1");
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
	LCD_DisplayStringLine(LINE(5), "CAMERA DA LETTO 2");
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
	LCD_DisplayStringLine(LINE(3), "CAMERA DA LETTO 1");
	LCD_DrawRect(RECT2_X, RECT2_Y, HEIGHT_RECT2, WIDTH_RECT2);
	LCD_DisplayStringLine(LINE(5), "CAMERA DA LETTO 2");
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
	LCD_DisplayStringLine(LINE(3), "CAMERA DA LETTO 1");
	LCD_DrawRect(RECT2_X, RECT2_Y, HEIGHT_RECT2, WIDTH_RECT2);
	LCD_DisplayStringLine(LINE(5), "CAMERA DA LETTO 2");
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
TASK( TaskOUT) {

	countTaskPress++;
	if (!stopTaskOut) {
		if (stopTaskControl && (!countStopOut)) {
			countStopOut = 1;
			count = 0;
			color = 0;
			for (int i = 0; i < 5; i++) {
				rooms[i] = 0;
			}
			LCD_Clear(White);
		}
		switch (count) {
		case 0: {
			selectSoggiorno();
			break;
		}
		case 1: {
			selectCam1();
			break;
		}
		case 2: {
			selectCam2();
			break;

		}
		case 3: {
			selectSalaPranzo();
			break;

		}
		case 4: {
			selectCucina();
			break;
		}
		}

	}
	if (!stopTaskControl) {
		taskControl(countTaskPress);
	}
	if (!stopTaskLuci) {
		taskLuci(countTaskPress);
	}
	if (!stopTaskTemp) {
		taskTemp();
	}
	if (!stopTaskUmid) {
		taskUmid();
	}
}
TASK( TaskButton) {
	static int oldState = 0;
	static int newState;
	static int flagUp = 0;
	static int flagDown = 0;

	newState = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);

	if (!oldState && newState && !flagDown) {
		flagUp = 1;
	} else if (oldState && !newState && flagUp) {
		flagDown = 1;
	}

	if (flagUp && flagDown && !color) {
		if (!stopTaskOut) {
			count++;
			count = count % 5;
		} else if (!stopTaskControl) {
			countControl++;
			countControl = countControl % 4;
		} else {
			countTemp++;
			countTemp = countTemp % 3;
		}
		flagUp = 0;
		flagDown = 0;
	} else if (color) {
		flagUp = 0;
		flagDown = 0;
	}

	oldState = newState;

}
TASK( TaskPress) {
	static int oldState = 0;
	static int newState;

	newState = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
	if (newState && oldState) {
		color = 1;
	} else {
		color = 0;
	}

	oldState = newState;
}
void displayHeadingControl() {
	LCD_Clear(White);
	LCD_SetBackColor(Red);
	LCD_SetTextColor(Black);
	if (rooms[0]) {
		LCD_DisplayStringLine(LINE(1), "SOGGIORNO");
	} else if (rooms[1]) {
		LCD_DisplayStringLine(LINE(1), "CAMERA DA LETTO 1");
	} else if (rooms[2]) {
		LCD_DisplayStringLine(LINE(1), "CAMERA DA LETTO 2");
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
	LCD_DisplayStringLine(LINE(5), "UMIDITA");
	LCD_DisplayStringLine(LINE(7), "LUCI");
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
	LCD_DisplayStringLine(LINE(5), "UMIDITA");
	LCD_SetBackColor(White);
	LCD_DisplayStringLine(LINE(7), "LUCI");
	LCD_DisplayChar(LINE(9), 250, 66);
	LCD_DisplayChar(LINE(9), 265, 65);
	LCD_DisplayChar(LINE(9), 280, 67);
	LCD_DisplayChar(LINE(9), 295, 75);
}
void selectLuciControl() {
	LCD_SetBackColor(White);
	LCD_DisplayStringLine(LINE(3), "TEMPERATURA");
	LCD_DisplayStringLine(LINE(5), "UMIDITA");
	if (color) {
		LCD_SetBackColor(Blue);
		controls[1] = 1;
		stopTaskControl = 1;
		stopTaskLuci = 0;
		countStopLuci = 0;
	} else {
		LCD_SetBackColor(Green);
	}
	LCD_DisplayStringLine(LINE(7), "LUCI");
	LCD_SetBackColor(White);
	LCD_DisplayChar(LINE(9), 250, 66);
	LCD_DisplayChar(LINE(9), 265, 65);
	LCD_DisplayChar(LINE(9), 280, 67);
	LCD_DisplayChar(LINE(9), 295, 75);
}
int selectBackButtonControl() {
	LCD_SetBackColor(White);
	LCD_DisplayStringLine(LINE(3), "TEMPERATURA");
	LCD_DisplayStringLine(LINE(5), "UMIDITA");
	LCD_DisplayStringLine(LINE(7), "LUCI");
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
void azzeraVariabiliControl() {
	if ((stopTaskTemp || stopTaskOut) && (!countStop)) {
		countTaskPress = 0;
		countStop = 1;
		controlFlag = 0;
		countControl = 0;
		for (int i = 0; i < 3; i++) {
			controls[i] = 0;
		}
		color = 0;
	}
}
void taskControl() {

	if (!stopTaskControl) {

		azzeraVariabiliControl();
		displayHeadingControl();

		if (countTaskPress >= 3) {
			controlFlag = 1;
		}
		if (controlFlag) {
			switch (countControl) {
			case 0: {
				selectTempControl();
				break;
			}
			case 1: {
				selectUmidControl();
				break;
			}
			case 2: {
				selectLuciControl();
				break;
			}
			case 3: {
				if (selectBackButtonControl() == 1) {
					return;
				}
				break; //prima non cera questo break;
			}
			}
		}
	}
	if (!stopTaskLuci) {
		taskLuci();
	}
	if (!stopTaskTemp) {
		taskTemp();
	}
	if (!stopTaskUmid) {
		taskUmid();
	}
}

void regulateTemp(int *stopIncrease, int *stopDecrease, int countAsci,
		int *asci1, int *asci2) {
	if (color && !countTemp && countAsci == 5) {
		if (((*asci1) == ASCI1MIN) && ((*asci2) == ASCI2MIN)) {
			*stopDecrease = 1;
		}
		if (((*asci2) >= 49) && (!(*stopDecrease))) {
			(*asci2)--;
		} else if ((*asci2) == 48) {
			(*asci1)--;
			(*asci2) = 57;
		}
	} else if (color && (countTemp == 1) && (countAsci == 5)) {
		if (((*asci1) == ASCI1MAX) && ((*asci2) == ASCI2MAX)) {
			*stopIncrease = 1;
		}
		if (((*asci2) <= 56) && (!(*stopIncrease))) {
			(*asci2)++;
		} else if ((*asci2) == 57) {
			(*asci1)++;
			(*asci2) = 48;
		}
	}
	return;
}
int backButtonDisplayTemp() {
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

void selectPlusButton() {
	if (countTemp == 1) {
		LCD_SetBackColor(Green);
	} else {
		LCD_SetBackColor(White);
	}
	LCD_DisplayChar(LINE(3), 245, 43);
	LCD_SetBackColor(White);

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
void displayDesiredTemp(int asci1, int asci2) {
	LCD_DisplayChar(LINE(3), 215, asci1);
	LCD_DisplayChar(LINE(3), 230, asci2);
}
void selectMinusButton() {
	if (!countTemp) {
		LCD_SetBackColor(Green);

	}
	LCD_DisplayChar(LINE(3), 200, 45);
	LCD_SetBackColor(White);
}
void initAsci(int asciChars[][5], int *asciFirst, int *asciSecond) {
	if (rooms[0] == 1) {
		*asciFirst = asciChars[0][0];
		*asciSecond = asciChars[1][0];
	} else if (rooms[1] == 1) {
		*asciFirst = asciChars[0][1];
		*asciSecond = asciChars[1][1];
	} else if (rooms[2] == 1) {
		*asciFirst = asciChars[0][2];
		*asciSecond = asciChars[1][2];
	} else if (rooms[3] == 1) {
		*asciFirst = asciChars[0][3];
		*asciSecond = asciChars[1][3];
	} else if (rooms[4] == 1) {
		*asciFirst = asciChars[0][4];
		*asciSecond = asciChars[1][4];
	}
}
void modifyTempRooms(int asciChars[][5], int asciFirst, int asciSecond) {
	if (rooms[0] == 1) {
		asciChars[0][0] = asciFirst;
		asciChars[1][0] = asciSecond;
		displayDesiredTemp(asciChars[0][0], asciChars[1][0]);
	} else if (rooms[1] == 1) {
		asciChars[0][1] = asciFirst;
		asciChars[1][1] = asciSecond;
		displayDesiredTemp(asciChars[0][1], asciChars[1][1]);
	} else if (rooms[2] == 1) {
		asciChars[0][2] = asciFirst;
		asciChars[1][2] = asciSecond;
		displayDesiredTemp(asciChars[0][2], asciChars[1][2]);
	} else if (rooms[3] == 1) {
		asciChars[0][3] = asciFirst;
		asciChars[1][3] = asciSecond;
		displayDesiredTemp(asciChars[0][3], asciChars[1][3]);
	} else if (rooms[4] == 1) {
		asciChars[0][4] = asciFirst;
		asciChars[1][4] = asciSecond;
		displayDesiredTemp(asciChars[0][4], asciChars[1][4]);
	}
}
void taskTemp() {

	int exitFunc = 0;
	int stopIncrease = 0;
	int stopDecrease = 0;
	static int asciFirst;
	static int asciSecond;
	static int asciChars[2][NROOMS] = { { ASCI1DEFAULT, ASCI1DEFAULT, ASCI1DEFAULT, ASCI1DEFAULT, ASCI1DEFAULT },
			{ ASCI2DEFAULT, ASCI2DEFAULT, ASCI2DEFAULT, ASCI2DEFAULT, ASCI2DEFAULT }};

	if (stopTaskControl && (!countStopTemp)) {
		countStopTemp = 1;
		countTemp = 0;
		color = 0;
		initAsci(&asciChars, &asciFirst, &asciSecond);
		countTaskPress = 0;
	}
	if (!stopTaskTemp) {
		initialTempDisplay();
		selectMinusButton();
		regulateTemp(&stopIncrease, &stopDecrease, countTaskPress, &asciFirst,
				&asciSecond);
		modifyTempRooms(&asciChars, asciFirst, asciSecond);
		selectPlusButton();
		if (backButtonDisplayTemp() == 1) {
			return;
		}
		countTaskPress = countTaskPress % 5;
	}
}

void taskUmid() {
	if (!stopTaskUmid) {
		LCD_Clear(White);
		LCD_SetBackColor(Blue);
		LCD_SetTextColor(Black);
		LCD_DisplayStringLine(LINE(1), "UMIDITA");
	}
}

void selectAccendi(int *on, int *off) {
	if (color) {
		LCD_SetBackColor(Blue);
		LCD_DisplayStringLine(LINE(3), "ACCENDI");
		*on = 1;
		*off = 0;
	} else {
		LCD_SetBackColor(Green);
		LCD_DisplayStringLine(LINE(3), "ACCENDI");
	}
	LCD_SetBackColor(White);

	LCD_DisplayStringLine(LINE(5), "SPEGNI");
	LCD_DisplayChar(LINE(9), 250, 66);
	LCD_DisplayChar(LINE(9), 265, 65);
	LCD_DisplayChar(LINE(9), 280, 67);
	LCD_DisplayChar(LINE(9), 295, 75);
}
void selectSpegni(int *on, int *off) {
	LCD_SetBackColor(White);
	LCD_DisplayStringLine(LINE(3), "ACCENDI");
	if (color) {
		LCD_SetBackColor(Blue);
		LCD_DisplayStringLine(LINE(5), "SPEGNI");
		*off = 1;
		*on = 0;
	} else {
		LCD_SetBackColor(Green);
		LCD_DisplayStringLine(LINE(5), "SPEGNI");
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
void displayOnOff(int on, int off) {
	LCD_SetBackColor(White);
	if ((off == 1) && (!on)) {
		LCD_DisplayChar(LINE(5), 230, 79);
		LCD_DisplayChar(LINE(5), 245, 70);
		LCD_DisplayChar(LINE(5), 260, 70);
	} else if ((on == 1) && (!off)) {
		LCD_DisplayChar(LINE(3), 230, 79);
		LCD_DisplayChar(LINE(3), 245, 78);
	}
}
void initialSettingsLuci() {
	LCD_Clear(White);
	LCD_SetBackColor(Blue);
	LCD_SetTextColor(Black);
	LCD_DisplayStringLine(LINE(1), "LUCE");
}
void initializeOnOffLuci(int *on, int *off, int *onRoom, int *offRoom) {
	if (rooms[0] == 1) {
		*on = onRoom[0];
		*off = offRoom[0];
	} else if (rooms[1] == 1) {
		*on = onRoom[1];
		*off = offRoom[1];
	} else if (rooms[2] == 1) {
		*on = onRoom[2];
		*off = offRoom[2];
	} else if (rooms[3] == 1) {
		*on = onRoom[3];
		*off = offRoom[3];
	} else if (rooms[4] == 1) {
		*on = onRoom[4];
		*off = offRoom[4];
	}
}
void OnOffRooms(int on, int off, int *onRoom, int *offRoom) {
	if (rooms[0] == 1) {
		onRoom[0] = on;
		offRoom[0] = off;
		displayOnOff(onRoom[0], offRoom[0]);
	} else if (rooms[1] == 1) {
		onRoom[1] = on;
		offRoom[1] = off;
		displayOnOff(onRoom[1], offRoom[1]);
	} else if (rooms[2] == 1) {
		onRoom[2] = on;
		offRoom[2] = off;
		displayOnOff(onRoom[2], offRoom[2]);
	} else if (rooms[3] == 1) {
		onRoom[3] = on;
		offRoom[3] = off;
		displayOnOff(onRoom[3], offRoom[3]);
	} else if (rooms[4] == 1) {
		onRoom[4] = on;
		offRoom[4] = off;
		displayOnOff(onRoom[4], offRoom[4]);
	}
}
void taskLuci() {
	static int onRoom[5] = { 0, 0, 0, 0, 0 };
	static int offRoom[5] = { 0, 0, 0, 0, 0 };
	static int on = 0;
	static int off = 0;

	initializeOnOffLuci(&on, &off, &onRoom, &offRoom);

	if (stopTaskControl && (!countStopLuci)) {
		countTaskPress = 0;
		controlFlagLuci = 0;
		countStopLuci = 1;
		countTemp = 0;
		color = 0;
	}
	if (!stopTaskLuci) {
		if (countTaskPress >= 3) {
			controlFlagLuci = 1;
		}
		initialSettingsLuci();
		if (controlFlagLuci == 1) {
			switch (countTemp) {
			case 0: {
				selectAccendi(&on, &off);
				break;
			}
			case 1: {
				selectSpegni(&on, &off);
				break;
			}
			case 2: {
				if (selectBackButtonLuci() == 1) {
					return;
				}
			}
			}
			OnOffRooms(on, off, &onRoom, &offRoom);
		}
	}
}

int main(void) {

	/*
	 * Setup the microcontroller system.
	 * Initialize the Embedded Flash Interface, the PLL and update the
	 * SystemFrequency variable.
	 * For default settings look at:
	 * pkg/mcu/st_stm32_stm32f4xx/src/system_stm32f4xx.c
	 */
	GPIO_InitTypeDef GPIO_InitStructure;

	SystemInit();

	/*Initialize Erika related stuffs*/
	EE_system_init();

	/*Initialize systick */
	EE_systick_set_period(MILLISECONDS_TO_TICKS(1, SystemCoreClock));
	EE_systick_enable_int();
	EE_systick_start();

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14
			| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/*Initialize the LCD*/
	STM32f4_Discovery_LCD_Init();

	LCD_Clear(White);
	LCD_SetBackColor(Green);
	LCD_SetTextColor(Black);

	/* Program cyclic alarms which will fire after an initial offset,
	 * and after that periodically
	 * */
	SetRelAlarm(AlarmButton, 10, 20);
	SetRelAlarm(AlarmOUT, 10, 200);
	SetRelAlarm(AlarmPress, 10, 1000);

	/* Forever loop: background activities (if any) should go here */
	for (;;)
		;

}

