#include "ee.h"

#include "stm32f4xx.h"

#include <stdio.h>

void azzeraVariabiliControl();
void taskControl();
void initAsciiTemp(int asciiChars[][5], int *asciiFirst, int *asciiSecond);
void initAsciiUmid(int asciiChars[][5], int *asciiFirst, int *asciiSecond);
void modifyTempRooms(int asciiChars[][5], int asciiFirst, int asciiSecond);
void modifyUmidRooms(int asciiChars[][5], int asciiFirst, int asciiSecond);
void taskTemp();
void taskUmid();
void taskLuci();
void regulateTemp(int*, int*, int, int*, int*);
void regulateUmid(int*, int*, int, int*, int*);
void initializeOnOffLuci(int*, int*, int*, int*, int*, int*);
void OnOffRooms(int, int, int, int*, int*, int*);
