#include <CUnit/CUnit.h>
#include <CUnit/Automated.h>

#define NROOMS 5

typedef unsigned char   uint8_t;

char asciiChars[4][NROOMS] = 	{{'z', 'z', 'z', 'z', 'z'},
                                {'z', 'z', 'z', 'z', 'z'},
                                {'z', 'z', 'z', 'z', 'z'},
                                {'z', 'z', 'z', 'z', 'z'}};

int onRoom[5] = { 0, 0, 0, 0, 0 };
int offRoom[5] = { 1, 1, 1, 1, 1 };
int autRoom[5] = { 0, 0, 0, 0, 0 };

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

void BT_case(uint8_t bt_input){
    /* Gestione comando BLUETOOTH */
    uint8_t bt_high, bt_low, bt;
    bt = bt_input;
    bt_high = bt >> 4;
	bt_low = bt & 0x0F;
    if (bt != 0xFF){
    	switch(bt_high){
		case 0x01:
			asciiChars[0][0] = ((bt_low + 15) % 100) / 10 + '0';
			asciiChars[1][0] = (bt_low + 15) % 10 + '0';
			break;
		case 0x02:
			asciiChars[2][0] = bt_low + '0';
			asciiChars[3][0] = 0 + '0';
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
			asciiChars[2][1] = bt_low + '0';
			asciiChars[3][1] = 0 + '0';
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
			asciiChars[2][2] = bt_low + '0';
			asciiChars[3][2] = 0 + '0';
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
			asciiChars[2][3] = bt_low + '0';
			asciiChars[3][3] = 0 + '0';
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

void selectSoggiorno() {
	if (color) {
		stopTaskOut = 1;
		stopTaskControl = 0;
		countStop = 0;
		rooms[0] = 1;
	}
}

void selectCam1() {
	if (color) {
		stopTaskOut = 1;
		stopTaskControl = 0;
		countStop = 0;
		rooms[1] = 1;
	}
}

void selectCam2() {
	if (color) {
		stopTaskOut = 1;
		stopTaskControl = 0;
		countStop = 0;
		rooms[2] = 1;
	}
}

void selectSalaPranzo() {
	if (color) {
		stopTaskOut = 1;
		stopTaskControl = 0;
		countStop = 0;
		rooms[3] = 1;
	}
}

void selectCucina() {
	if (color) {
		stopTaskOut = 1;
		stopTaskControl = 0;
		countStop = 0;
		rooms[4] = 1;
	}
}

void TaskOUT() {
	countTaskPress++;
	if (!stopTaskOut) {
		if (stopTaskControl && (!countStopOut)) {
			countStopOut = 1;
			count = 0;
			color = 0;
			for (int i = 0; i < 5; i++) {
				rooms[i] = 0;
			}
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
}

void TaskPress(int GPIO_test) {
	static int oldState;
	static int newState;

	newState = GPIO_test;
	if (newState && oldState) {
		color = 1;
	} else {
		color = 0;
	}

	oldState = newState;
}

void test_bt (){
	BT_case(0x61);
	CU_ASSERT_EQUAL(onRoom[1], 1);
	CU_ASSERT_EQUAL(offRoom[1], 0);
	CU_ASSERT_EQUAL(autRoom[1], 0);

	BT_case(0x62);
	CU_ASSERT_EQUAL(onRoom[1], 0);
	CU_ASSERT_EQUAL(offRoom[1], 1);
	CU_ASSERT_EQUAL(autRoom[1], 0);

	BT_case(0x63);
	CU_ASSERT_EQUAL(onRoom[1], 0);
	CU_ASSERT_EQUAL(offRoom[1], 0);
	CU_ASSERT_EQUAL(autRoom[1], 1);
}

void test_press (){
	TaskPress(1);
	TaskPress(1);
	TaskOUT();

	CU_ASSERT_EQUAL(stopTaskOut, 1);
	CU_ASSERT_EQUAL(stopTaskControl, 0);
	CU_ASSERT_EQUAL(countStop, 0);
	CU_ASSERT_EQUAL(rooms[0], 1);
}

int main(int argc, char* argv[])
{
    if(CUE_SUCCESS != CU_initialize_registry())
    {
        printf("Could not initialize CUnit registry!\r\n");
        
        return CU_get_error();
    }

    CU_set_error_action(CUEA_FAIL);

    CU_pSuite suite1 = CU_add_suite("myTest", NULL, NULL);

    CU_add_test(suite1, "TestBT", test_bt);
    CU_add_test(suite1, "TestPress", test_press);


    // Running all the tests
    CU_automated_run_tests();

    CU_cleanup_registry();

    return EXIT_SUCCESS;
}