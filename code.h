#include "ee.h"

#include "stm32f4xx.h"
#include "lcd_log.h"

#include <stdio.h>

void azzeraVariabiliControl();
void taskControl();
void initAsci(int asciChars[][5], int *asciFirst, int *asciSecond);
void modifyTempRooms(int asciChars[][5], int asciFirst, int asciSecond);
void taskTemp();
void taskUmid();
void taskLuci();
void regulateTemp(int *stopIncrease, int *stopDecrease, int countAsci, int *asci1, int *asci2);
void initializeOnOffLuci(int *on, int *off, int *onRoom, int *offRoom);
void OnOffRooms(int on, int off, int *onRoom, int *offRoom);
