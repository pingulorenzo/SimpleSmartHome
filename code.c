#include "gui.h"
#include "code.h"

int asciiFirst;
int asciiSecond;
int asciiChars[2][NROOMS] = { { ASCI1DEFAULT, ASCI1DEFAULT, ASCI1DEFAULT, ASCI1DEFAULT, ASCI1DEFAULT },
			{ ASCI2DEFAULT, ASCI2DEFAULT, ASCI2DEFAULT, ASCI2DEFAULT, ASCI2DEFAULT }};

int onRoom[5] = { 0, 0, 0, 0, 0 };
int offRoom[5] = { 0, 0, 0, 0, 0 };
int on = 0;
int off = 0;

int oldState = 0;
int newState;
int flagUp = 0;
int flagDown = 0;

/*
 * SysTick ISR2
 */
ISR2( systick_handler) {
	/* count the interrupts, waking up expired alarms */
	CounterTick(myCounter);
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

void taskUmid() {
	if (!stopTaskUmid) {
		LCD_Clear(White);
		LCD_SetBackColor(Blue);
		LCD_SetTextColor(Black);
		LCD_DisplayStringLine(LINE(1), "UMIDITÀ");
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

void initAsci(int asciiChars[][5], int *asciiFirst, int *asciiSecond) {
	if (rooms[0] == 1) {
		*asciiFirst = asciiChars[0][0];
		*asciiSecond = asciiChars[1][0];
	} else if (rooms[1] == 1) {
		*asciiFirst = asciiChars[0][1];
		*asciiSecond = asciiChars[1][1];
	} else if (rooms[2] == 1) {
		*asciiFirst = asciiChars[0][2];
		*asciiSecond = asciiChars[1][2];
	} else if (rooms[3] == 1) {
		*asciiFirst = asciiChars[0][3];
		*asciiSecond = asciiChars[1][3];
	} else if (rooms[4] == 1) {
		*asciiFirst = asciiChars[0][4];
		*asciiSecond = asciiChars[1][4];
	}
}

void modifyTempRooms(int asciiChars[][5], int asciiFirst, int asciiSecond) {
	if (rooms[0] == 1) {
		asciiChars[0][0] = asciiFirst;
		asciiChars[1][0] = asciiSecond;
		displayDesiredTemp(asciiChars[0][0], asciiChars[1][0]);
	} else if (rooms[1] == 1) {
		asciiChars[0][1] = asciiFirst;
		asciiChars[1][1] = asciiSecond;
		displayDesiredTemp(asciiChars[0][1], asciiChars[1][1]);
	} else if (rooms[2] == 1) {
		asciiChars[0][2] = asciiFirst;
		asciiChars[1][2] = asciiSecond;
		displayDesiredTemp(asciiChars[0][2], asciiChars[1][2]);
	} else if (rooms[3] == 1) {
		asciiChars[0][3] = asciiFirst;
		asciiChars[1][3] = asciiSecond;
		displayDesiredTemp(asciiChars[0][3], asciiChars[1][3]);
	} else if (rooms[4] == 1) {
		asciiChars[0][4] = asciiFirst;
		asciiChars[1][4] = asciiSecond;
		displayDesiredTemp(asciiChars[0][4], asciiChars[1][4]);
	}
}

void taskTemp() {

	int exitFunc = 0;
	int stopIncrease = 0;
	int stopDecrease = 0;

	if (stopTaskControl && (!countStopTemp)) {
		countStopTemp = 1;
		countTemp = 0;
		color = 0;
		initAsci(&asciiChars, &asciiFirst, &asciiSecond);
		countTaskPress = 0;
	}
	if (!stopTaskTemp) {
		initialTempDisplay();
		selectMinusButton();
		regulateTemp(&stopIncrease, &stopDecrease, countTaskPress, &asciiFirst,
				&asciiSecond);
		modifyTempRooms(&asciiChars, asciiFirst, asciiSecond);
		selectPlusButton();
		if (backButtonDisplayTemp() == 1) {
			return;
		}
		countTaskPress = countTaskPress % 5;
	}
}

void regulateTemp(int *stopIncrease, int *stopDecrease, int countAsci, int *asci1, int *asci2) {
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

TASK (TaskOUT) {
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

TASK (TaskButton) {

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

TASK (TaskPress) {
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

int main(void) {
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

