#ifndef _FUNCTIONS
#define _FUNCTIONS

#include "../include/lib.h"


using namespace std;


struct Slist{
    char* element;
};

typedef char* String; 



//FUNCIONES
int w_splitNStringBy(wchar_t* text,wchar_t symbol, int** list);
int w_splitCStringBy(wchar_t* text,wchar_t symbol, wchar_t** list);
int splitNStringBy(char* text, char symbol, int** list);
float fXevaluate(char* function, int value);
int fXcheck(char** function, int lenFunction);
int fXSplit(char* function, Slist** list);
float fEvaluate(char* function, float value);
int removeRepeteadNumbers(int** sequence, int lenSequence);
int srchIndex(int element, int** sequence, int lenSequence);
void upperSChar(wchar_t** string, int len);

int readString(String* string);
int readSchar(char** string);
#include "../lib/functions.cpp"

#endif