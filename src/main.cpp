#include "../include/main.h"


int main(){
    wchar_t* inputSequence  = (wchar_t*)calloc(11,sizeof(wchar_t));
    wchar_t* inSequence = NULL;
    _getws(inputSequence);
    int lenSequence = w_splitCStringBy(inputSequence,L',',&inSequence);
    _putws(inSequence);
    upperSChar(&inSequence,wcslen(inputSequence));
    for(int i = 0; i <= lenSequence-1; i++){
        printf("char: %c\n",*(inSequence+i));
    }
    int* sequence = (int*)calloc(lenSequence,sizeof(int));
    for(int i = 0; i <= lenSequence-1; i++){
        *(sequence+i) = *(inSequence+i);
        printf("int: %d\n",*(sequence+i));
    }
    BinaryTree bTree;
    int* inOrder = NULL;
    bTree.BTGenerate(&sequence,lenSequence);
    bTree.BTPreOrder(&inOrder);
    for(int i = 0; i <= lenSequence-1; i ++){
        printf("c: %c\n",*(inOrder+i));
    }
}
