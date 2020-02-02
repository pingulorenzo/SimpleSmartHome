#include "stm32f4_discovery.h"
#include "stm32f4_discovery_lcd.h"

#define RECT1_X           (0)
#define RECT1_Y           (20)

#define HEIGHT_RECT1		(150)
#define WIDTH_RECT1			(30)

#define RECT2_X           RECT1_X
#define RECT2_Y           RECT1_Y + 48

#define HEIGHT_RECT2		HEIGHT_RECT1 - 10
#define WIDTH_RECT2			WIDTH_RECT1

#define RECT3_X           RECT2_X
#define RECT3_Y           RECT2_Y + 48

#define HEIGHT_RECT3		HEIGHT_RECT1 + 100
#define WIDTH_RECT3			WIDTH_RECT2

#define RECT4_X           RECT3_X
#define RECT4_Y           RECT3_Y + 48

#define HEIGHT_RECT4		HEIGHT_RECT1 + 80
#define WIDTH_RECT4			WIDTH_RECT3

#define RECT5_X           RECT4_X
#define RECT5_Y           RECT4_Y + 48

#define HEIGHT_RECT5		100
#define WIDTH_RECT5			WIDTH_RECT4

#define ASCII1MIN			49
#define ASCII1MAX			51

#define ASCII2MIN			53
#define ASCII2MAX			48

#define ASCIIU1MIN			49
#define ASCIIU1MAX			57

#define ASCII1DEFAULT		50
#define ASCII2DEFAULT		51
#define ASCIIU1DEFAULT		53
#define ASCIIU2DEFAULT		48

#define NROOMS				5

extern volatile int count;
extern volatile int countControl;
extern volatile int countTemp;
extern volatile int countUmid;
extern volatile int countLuci;
extern volatile int color;
extern volatile int countColor;
extern int controlFlag;
extern int controlFlagLuci;
extern int stopTaskOut;
extern int rooms[];
extern int controls[];
extern int stopTaskControl;

extern int stopTaskTemp;
extern int stopTaskUmid;
extern int stopTaskLuci;
extern int countStopTemp;
extern int countStop;
extern int countStopOut;
extern int countStopUmid;
extern int countStopLuci;
extern int countTaskPress;

void selectSoggiorno();
void selectCam1();
void selectCam2();
void selectSalaPranzo();
void selectCucina();
void selectTempControl();
void selectUmidControl();
void selectLuciControl();
void displayHeadingControl();
int selectBackButtonControl();
int selectBackButtonLuci();
int selectBackButtonTemp();
int selectBackButtonUmid();
void initialUmidDisplay();
void initialTempDisplay();
void displayDesiredTemp(char, char);
void displayDesiredUmid(char, char);
void displayCurrentTemp(char, char);
void displayCurrentUmid(char, char);
void selectMinusTemp();
void selectPlusTemp();
void selectMinusUmid();
void selectPlusUmid();
void selectAccendi(int*, int*, int*);
void selectSpegni(int*, int*, int*);
void selectAuto(int*, int*, int*);
void displayOnOff(int, int, int);
void initialSettingsLuci();
