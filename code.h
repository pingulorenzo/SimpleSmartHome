#include "ee.h"

#include "stm32f4xx.h"

#include <stdio.h>

void azzeraVariabiliControl();
void taskControl();
void initAsciiTemp(char asciiChars[][5], char*, char*);
void initAsciiUmid(char asciiChars[][5], char*, char*);
void modifyTempRooms(char asciiChars[][5], char, char);
void modifyUmidRooms(char asciiChars[][5], char, char);
void taskTemp();
void taskUmid();
void taskLuci();
void regulateTemp(int*, int*, int, char*, char*);
void regulateUmid(int*, int*, int, char*, char*);
void initializeOnOffLuci(int*, int*, int*, int*, int*, int*);
void OnOffRooms(int, int, int, int*, int*, int*);
