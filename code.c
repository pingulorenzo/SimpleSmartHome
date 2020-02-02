#include "gui.h"
#include "code.h"

char asciiFirst;
char asciiSecond;
char asciiChars[4][NROOMS] = 		{{ASCII1DEFAULT, ASCII1DEFAULT, ASCII1DEFAULT, ASCII1DEFAULT, ASCII1DEFAULT},
									{ASCII2DEFAULT, ASCII2DEFAULT, ASCII2DEFAULT, ASCII2DEFAULT, ASCII2DEFAULT},
									{ASCIIU1DEFAULT, ASCIIU1DEFAULT, ASCIIU1DEFAULT, ASCIIU1DEFAULT, ASCIIU1DEFAULT},
									{ASCIIU2DEFAULT, ASCIIU2DEFAULT, ASCIIU2DEFAULT, ASCIIU2DEFAULT, ASCIIU2DEFAULT}};
char asciiCurrentChars[4][NROOMS] = 	{{'z', 'z', 'z', 'z', 'z'},
									{'z', 'z', 'z', 'z', 'z'},
									{'z', 'z', 'z', 'z', 'z'},
									{'z', 'z', 'z', 'z', 'z'}};

int onRoom[5] = { 1, 0, 0, 0, 0 };
int offRoom[5] = { 1, 0, 0, 0, 0 };
int autRoom[5] = { 1, 0, 0, 0, 0 };
int on = 0;
int off = 0;
int aut = 0;

uint16_t current_temp, current_luce;
uint8_t current_temp_D, current_temp_U, current_umid, current_umid_D, current_umid_U;
float floatTemp;

GPIO_InitTypeDef GPIO_InitStructure;
USART_InitTypeDef USART_InitStructure;

/* SysTick ISR2 */
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
				selectLuciControl();
				break;
			}
			case 2: {
				selectUmidControl();
				break;
			}
			case 3: {
				if (selectBackButtonControl() == 1) {
					return;
				}
				break;
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

void initAsciiTemp(char asciiChars[][5], char *asciiFirst, char *asciiSecond) {
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

void initAsciiUmid(char asciiChars[][5], char *asciiFirst, char *asciiSecond) {
	if (rooms[0] == 1) {
		*asciiFirst = asciiChars[2][0];
		*asciiSecond = asciiChars[3][0];
	} else if (rooms[1] == 1) {
		*asciiFirst = asciiChars[2][1];
		*asciiSecond = asciiChars[3][1];
	} else if (rooms[2] == 1) {
		*asciiFirst = asciiChars[2][2];
		*asciiSecond = asciiChars[3][2];
	} else if (rooms[3] == 1) {
		*asciiFirst = asciiChars[2][3];
		*asciiSecond = asciiChars[3][3];
	} else if (rooms[4] == 1) {
		*asciiFirst = asciiChars[2][4];
		*asciiSecond = asciiChars[3][4];
	}
}

void modifyTempRooms(char asciiChars[][5], char asciiFirst, char asciiSecond) {
	if (rooms[0] == 1) {
		asciiChars[0][0] = asciiFirst;
		asciiChars[1][0] = asciiSecond;
		displayDesiredTemp(asciiChars[0][0], asciiChars[1][0]);
		displayCurrentTemp(asciiCurrentChars[0][0], asciiCurrentChars[1][0]);
	} else if (rooms[1] == 1) {
		asciiChars[0][1] = asciiFirst;
		asciiChars[1][1] = asciiSecond;
		displayDesiredTemp(asciiChars[0][1], asciiChars[1][1]);
		displayCurrentTemp(asciiCurrentChars[0][1], asciiCurrentChars[1][1]);
	} else if (rooms[2] == 1) {
		asciiChars[0][2] = asciiFirst;
		asciiChars[1][2] = asciiSecond;
		displayDesiredTemp(asciiChars[0][2], asciiChars[1][2]);
		displayCurrentTemp(asciiCurrentChars[0][2], asciiCurrentChars[1][2]);
	} else if (rooms[3] == 1) {
		asciiChars[0][3] = asciiFirst;
		asciiChars[1][3] = asciiSecond;
		displayDesiredTemp(asciiChars[0][3], asciiChars[1][3]);
		displayCurrentTemp(asciiCurrentChars[0][3], asciiCurrentChars[1][3]);
	} else if (rooms[4] == 1) {
		asciiChars[0][4] = asciiFirst;
		asciiChars[1][4] = asciiSecond;
		displayDesiredTemp(asciiChars[0][4], asciiChars[1][4]);
		displayCurrentTemp(asciiCurrentChars[0][4], asciiCurrentChars[1][4]);
	}
}

void modifyUmidRooms(char asciiChars[][5], char asciiFirst, char asciiSecond) {
	if (rooms[0] == 1) {
		asciiChars[2][0] = asciiFirst;
		asciiChars[3][0] = asciiSecond;
		displayDesiredUmid(asciiChars[2][0], asciiChars[3][0]);
		displayCurrentUmid(asciiCurrentChars[2][0], asciiCurrentChars[3][0]);
	} else if (rooms[1] == 1) {
		asciiChars[2][1] = asciiFirst;
		asciiChars[3][1] = asciiSecond;
		displayDesiredUmid(asciiChars[2][1], asciiChars[3][1]);
		displayCurrentUmid(asciiCurrentChars[2][1], asciiCurrentChars[3][1]);
	} else if (rooms[2] == 1) {
		asciiChars[2][2] = asciiFirst;
		asciiChars[3][2] = asciiSecond;
		displayDesiredUmid(asciiChars[2][2], asciiChars[3][2]);
		displayCurrentUmid(asciiCurrentChars[2][2], asciiCurrentChars[3][2]);
	} else if (rooms[3] == 1) {
		asciiChars[2][3] = asciiFirst;
		asciiChars[3][3] = asciiSecond;
		displayDesiredUmid(asciiChars[2][3], asciiChars[3][3]);
		displayCurrentUmid(asciiCurrentChars[2][3], asciiCurrentChars[3][3]);
	} else if (rooms[4] == 1) {
		asciiChars[2][4] = asciiFirst;
		asciiChars[3][4] = asciiSecond;
		displayDesiredUmid(asciiChars[2][4], asciiChars[3][4]);
		displayCurrentUmid(asciiCurrentChars[2][4], asciiCurrentChars[3][4]);
	}
}

void taskTemp() {

	int stopIncrease = 0;
	int stopDecrease = 0;

	if (stopTaskControl && (!countStopTemp)) {
		countStopTemp = 1;
		countTemp = 0;
		color = 0;
		initAsciiTemp(asciiChars, &asciiFirst, &asciiSecond);
		countTaskPress = 0;
	}
	if (!stopTaskTemp) {
		initialTempDisplay();
		selectMinusTemp();
		regulateTemp(&stopIncrease, &stopDecrease, countTaskPress, &asciiFirst,
				&asciiSecond);
		modifyTempRooms(asciiChars, asciiFirst, asciiSecond);
		selectPlusTemp();
		if (selectBackButtonTemp() == 1) {
			return;
		}
		countTaskPress = countTaskPress % 5;
	}
}

void taskLuci() {

	initializeOnOffLuci(&on, &off, &aut, onRoom, offRoom, autRoom);

	if (stopTaskControl && (!countStopLuci)) {
		countTaskPress = 0;
		controlFlagLuci = 0;
		countStopLuci = 1;
		countLuci = 0;
		color = 0;
	}
	if (!stopTaskLuci) {
		if (countTaskPress >= 3) {
			controlFlagLuci = 1;
		}
		initialSettingsLuci();
		if (controlFlagLuci == 1) {
			switch (countLuci) {
			case 0:
				selectAccendi(&on, &off, &aut);
				break;

			case 1:
				selectSpegni(&on, &off, &aut);
				break;

			case 2:
				selectAuto(&on, &off, &aut);
				break;

			case 3:
				if (selectBackButtonLuci() == 1) {
					return;
				}
				break;
			}
		}
	}
	OnOffRooms(on, off, aut, onRoom, offRoom, autRoom);
}

void taskUmid() {

	int stopIncrease = 0;
	int stopDecrease = 0;

	if (stopTaskControl && (!countStopUmid)) {
		countStopUmid = 1;
		countUmid = 0;
		color = 0;
		initAsciiUmid(asciiChars, &asciiFirst, &asciiSecond);
		countTaskPress = 0;
	}
	if (!stopTaskUmid) {
		initialUmidDisplay();
		selectMinusUmid();
		regulateUmid(&stopIncrease, &stopDecrease, countTaskPress, &asciiFirst,
				&asciiSecond);
		modifyUmidRooms(asciiChars, asciiFirst, asciiSecond);
		selectPlusUmid();
		if (selectBackButtonUmid() == 1) {
			return;
		}
		countTaskPress = countTaskPress % 5;
	}
}

void regulateTemp(int *stopIncrease, int *stopDecrease, int countAscii, char *ascii1, char *ascii2) {
	if (color && !countTemp && countAscii == 5) {
		if (((*ascii1) == ASCII1MIN) && ((*ascii2) == ASCII2MIN)) {
			*stopDecrease = 1;
		}
		if (((*ascii2) >= 49) && (!(*stopDecrease))) {
			(*ascii2)--;
		} else if ((*ascii2) == 48) {
			(*ascii1)--;
			(*ascii2) = 57;
		}
	} else if (color && (countTemp == 1) && (countAscii == 5)) {
		if (((*ascii1) == ASCII1MAX) && ((*ascii2) == ASCII2MAX)) {
			*stopIncrease = 1;
		}
		if (((*ascii2) <= 56) && (!(*stopIncrease))) {
			(*ascii2)++;
		} else if ((*ascii2) == 57) {
			(*ascii1)++;
			(*ascii2) = 48;
		}
	}
}

void regulateUmid(int *stopIncrease, int *stopDecrease, int countAscii, char *ascii1, char *ascii2) {
	if (color && !countUmid && countAscii == 5) {
		if ((*ascii1) == ASCIIU1MIN) {
			*stopDecrease = 1;
		}
		if (((*ascii1) >= 49) && (!(*stopDecrease))) {
			(*ascii1)--;
		}
	} else if (color && (countUmid == 1) && (countAscii == 5)) {
		if ((*ascii1) == ASCIIU1MAX) {
			*stopIncrease = 1;
		}
		if (((*ascii1) <= 56) && (!(*stopIncrease))) {
			(*ascii1)++;
		}
	}
}

void initializeOnOffLuci(int *on, int *off, int *aut, int *onRoom, int *offRoom, int *autRoom) {
	if (rooms[0] == 1) {
		*on = onRoom[0];
		*off = offRoom[0];
		*aut = autRoom[0];
	} else if (rooms[1] == 1) {
		*on = onRoom[1];
		*off = offRoom[1];
		*aut = autRoom[1];
	} else if (rooms[2] == 1) {
		*on = onRoom[2];
		*off = offRoom[2];
		*aut = autRoom[2];
	} else if (rooms[3] == 1) {
		*on = onRoom[3];
		*off = offRoom[3];
		*aut = autRoom[3];
	} else if (rooms[4] == 1) {
		*on = onRoom[4];
		*off = offRoom[4];
		*aut = autRoom[4];
	}
}

void OnOffRooms(int on, int off, int aut, int *onRoom, int *offRoom, int *autRoom) {
	if (rooms[0] == 1) {
		onRoom[0] = on;
		offRoom[0] = off;
		autRoom[0] = aut;
		displayOnOff(onRoom[0], offRoom[0], autRoom[0]);
	} else if (rooms[1] == 1) {
		onRoom[1] = on;
		offRoom[1] = off;
		autRoom[1] = aut;
		displayOnOff(onRoom[1], offRoom[1], autRoom[1]);
	} else if (rooms[2] == 1) {
		onRoom[2] = on;
		offRoom[2] = off;
		autRoom[2] = aut;
		displayOnOff(onRoom[2], offRoom[2], autRoom[2]);
	} else if (rooms[3] == 1) {
		onRoom[3] = on;
		offRoom[3] = off;
		autRoom[3] = aut;
		displayOnOff(onRoom[3], offRoom[3], autRoom[3]);
	} else if (rooms[4] == 1) {
		onRoom[4] = on;
		offRoom[4] = off;
		autRoom[4] = aut;
		displayOnOff(onRoom[4], offRoom[4], autRoom[4]);
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
		case 0:
			selectSoggiorno();
			break;
		case 1:
			selectCam1();
			break;
		case 2:
			selectCam2();
			break;
		case 3:
			selectSalaPranzo();
			break;
		case 4:
			selectCucina();
			break;
		}

	}
	if (!stopTaskControl) {
		taskControl();
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

TASK (TaskButton) {
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
		} else if (!stopTaskTemp){
			countTemp++;
			countTemp = countTemp % 3;
		} else if (!stopTaskLuci){
			countLuci++;
			countLuci = countLuci % 4;
		} else if (!stopTaskUmid){
			countUmid++;
			countUmid = countUmid % 3;
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

TASK (TaskSensors) {
	uint8_t value[6];

	USART_SendData(USART3, 'z');

	while(!USART_GetFlagStatus(USART3, USART_FLAG_RXNE));
	value[0] = USART_ReceiveData(USART3);

	while(!USART_GetFlagStatus(USART3, USART_FLAG_RXNE));
	value[1] = USART_ReceiveData(USART3);

	while(!USART_GetFlagStatus(USART3, USART_FLAG_RXNE));
	value[2] = USART_ReceiveData(USART3);

	while(!USART_GetFlagStatus(USART3, USART_FLAG_RXNE));
	value[3] = USART_ReceiveData(USART3);

	while(!USART_GetFlagStatus(USART3, USART_FLAG_RXNE));
	value[4] = USART_ReceiveData(USART3);

	while(!USART_GetFlagStatus(USART3, USART_FLAG_RXNE));
	value[5] = USART_ReceiveData(USART3);

	/* Temp Rebuilt */
    current_temp = value[0] << 8 | value[1];
    floatTemp = current_temp / 100;
    if (current_temp % 100 > 49){
        current_temp /= 100 + 1;
    } else {
        current_temp /= 100;
    }

    /* Temp Char Casting */
    current_temp_U = current_temp % 10 + '0';
    current_temp_D = (current_temp % 100) / 10 + '0';
    for (int i = 0; i < NROOMS; i++){
    	asciiCurrentChars[0][i] = current_temp_D;
    	asciiCurrentChars[1][i] = current_temp_U;
    }

    /* Luce Rebuilt */
    current_luce = value[2] << 8 | value[3];

    /* Umid Rebult and Casting*/
    current_umid = value[4];
    current_umid_U = (current_umid % 10) + '0';
    current_umid_D = (current_umid % 100) / 10 + '0';
    for (int i = 0; i < NROOMS; i++){
    	asciiCurrentChars[2][i] = current_umid_D;
    	asciiCurrentChars[3][i] = current_umid_U;
    }

    /* Gestione comando BLUETOOTH */
    uint8_t bt_high, bt_low, bt;
    bt = value[5];
    bt_high = bt >> 4;
	bt_low = bt & 0x0F;
    if (bt != 0xFF){
    	switch(bt_high){
		case 0x01:
			asciiChars[0][0] = ((bt_low + 15) % 100) / 10 + '0';
			asciiChars[1][0] = (bt_low + 15) % 10 + '0';
			break;
		case 0x02:
			asciiChars[2][4] = bt_low + '0';
			asciiChars[3][4] = 0 + '0';
			break;
		case 0x03:
			switch(bt_low){
			case 0x01:
				onRoom[0] = 1;
				offRoom[0] = 0;
				autRoom[0] = 0;
				break;
			case 0x02:
				onRoom[0] = 0;
				offRoom[0] = 1;
				autRoom[0] = 0;
				break;
			case 0x03:
				onRoom[0] = 0;
				offRoom[0] = 0;
				autRoom[0] = 1;
				break;
			}
			break;
		case 0x04:
			asciiChars[0][1] = ((bt_low + 15) % 100) / 10 + '0';
			asciiChars[1][1] = (bt_low + 15) % 10 + '0';
			break;
		case 0x05:
			asciiChars[2][4] = bt_low + '0';
			asciiChars[3][4] = 0 + '0';
			break;
		case 0x06:
			switch(bt_low){
			case 0x01:
				onRoom[1] = 1;
				offRoom[1] = 0;
				autRoom[1] = 0;
				break;
			case 0x02:
				onRoom[1] = 0;
				offRoom[1] = 1;
				autRoom[1] = 0;
				break;
			case 0x03:
				onRoom[1] = 0;
				offRoom[1] = 0;
				autRoom[1] = 1;
				break;
			}
			break;
		case 0x07:
			asciiChars[0][2] = ((bt_low + 15) % 100) / 10 + '0';
			asciiChars[1][2] = (bt_low + 15) % 10 + '0';
			break;
		case 0x08:
			asciiChars[2][4] = bt_low + '0';
			asciiChars[3][4] = 0 + '0';
			break;
		case 0x09:
			switch(bt_low){
			case 0x01:
				onRoom[2] = 1;
				offRoom[2] = 0;
				autRoom[2] = 0;
				break;
			case 0x02:
				onRoom[2] = 0;
				offRoom[2] = 1;
				autRoom[2] = 0;
				break;
			case 0x03:
				onRoom[2] = 0;
				offRoom[2] = 0;
				autRoom[2] = 1;
				break;
			}
			break;
		case 0x0A:
			asciiChars[0][3] = ((bt_low + 15) % 100) / 10 + '0';
			asciiChars[1][3] = (bt_low + 15) % 10 + '0';
			break;
		case 0x0B:
			asciiChars[2][4] = bt_low + '0';
			asciiChars[3][4] = 0 + '0';
			break;
		case 0x0C:
			switch(bt_low){
			case 0x01:
				onRoom[3] = 1;
				offRoom[3] = 0;
				autRoom[3] = 0;
				break;
			case 0x02:
				onRoom[3] = 0;
				offRoom[3] = 1;
				autRoom[3] = 0;
				break;
			case 0x03:
				onRoom[3] = 0;
				offRoom[3] = 0;
				autRoom[3] = 1;
				break;
			}
			break;
		case 0x0D:
			asciiChars[0][4] = ((bt_low + 15) % 100) / 10 + '0';
			asciiChars[1][4] = (bt_low + 15) % 10 + '0';
			break;
		case 0x0E:
			asciiChars[2][4] = bt_low + '0';
			asciiChars[3][4] = 0 + '0';
			break;
		case 0x0F:
			switch(bt_low){
			case 0x01:
				onRoom[4] = 1;
				offRoom[4] = 0;
				autRoom[4] = 0;
				break;
			case 0x02:
				onRoom[4] = 0;
				offRoom[4] = 1;
				autRoom[4] = 0;
				break;
			case 0x03:
				onRoom[4] = 0;
				offRoom[4] = 0;
				autRoom[4] = 1;
				break;
			}
			break;
		}
    }

}

int main(void) {
	SystemInit();

	/*Initialize Erika related stuffs*/
	EE_system_init();

	/*Initialize systick */
	EE_systick_set_period(MILLISECONDS_TO_TICKS(1, SystemCoreClock));
	EE_systick_enable_int();
	EE_systick_start();

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Initialize the LCD */
	STM32f4_Discovery_LCD_Init();

	LCD_Clear(White);
	LCD_SetBackColor(Green);
	LCD_SetTextColor(Black);

	/* Initialize USART3 GPIO */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); //Enable clock for GPIOB
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART3); //Connect PC10 to USART3_Tx
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART3); //Connect PC11 to USART3_Rx
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; //GPIO_Mode_Alternate Function
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	/* Initialize USART3 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl =	USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART3, &USART_InitStructure);
	USART_Cmd(USART3, ENABLE);

	/* Program cyclic alarms which will fire after an initial offset,
	 * and after that periodically
	 * */
	SetRelAlarm(AlarmButton, 10, 20);
	SetRelAlarm(AlarmOUT, 10, 200);
	SetRelAlarm(AlarmPress, 10, 750);
	SetRelAlarm(AlarmSensors, 10, 1000);

	/* Forever loop: background activities (if any) should go here */
	for (;;){

	}

}

