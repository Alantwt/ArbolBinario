#include "../include/lib.h"
#include "../include/binaryTree.h"

//SEPARAR NUMEROS DE UN WSTRING EN UN ARRAY DE ENTEROS
int w_splitNStringBy(wchar_t* text,wchar_t symbol, int** list){
    wchar_t* cadTemp;
    wchar_t* textTemp;
    cadTemp = (wchar_t*)calloc(1,sizeof(wchar_t));
    textTemp = (wchar_t*)calloc(1,sizeof(wchar_t));
    *list = (int*)calloc(1,sizeof(int));
    int i = 0;

    for(int c = 0; c <= wcslen(text)-1; c++){
        if(text[c] != symbol){
            //SI ENCUENTRA QUE NO ES UN NUMERO ELIMINA LA MEMORIA DEL PUNTERO Y RETORNA 0
            if(isdigit(text[c]) != 1){
                free(*list);
                return 0;
            }

            cadTemp = (wchar_t*)realloc(cadTemp,(c+1)*sizeof(wchar_t));
            *textTemp = text[c];
            wcscat(cadTemp,textTemp);
            wcscpy(textTemp,L"");
        }
        if((text[c] == symbol || c == wcslen(text)-1)&&(_wtoi(cadTemp) != 0)){
            *list = (int*)realloc(*list,(i+1)*sizeof(int));
            //TRANSFORMA LA CADENA EN ENTEROS Y LOS AGREGA A LA LISTA DE INTS 
            *((*list)+i) = _wtoi(cadTemp); 
            wcscpy(cadTemp,L"");
            i++;
        }
    }
    return i;
}
//SEPARAR CARACTERES DE UN WSTRING EN UN ARRAY DE CARACTERES
int w_splitCStringBy(wchar_t* text,wchar_t symbol, wchar_t** list){
    int len = 0;
    *list = (wchar_t*)calloc(1,sizeof(wchar_t));
    for(int i = 0; i <= wcslen(text)-1; i++){
        if(*(text+i) != symbol){
            *(*list+len) = *(text+i); 
            len++;
            *list = (wchar_t*)realloc(*list,(len+1)*sizeof(wchar_t));
        }
    }
    return len;
}

//SEPARAR NUMEROS DE UN STRING EN UN ARRAY DE ENTEROS
int splitNStringBy(char* text, char symbol, int** list){
    if(text != NULL){
        char* cadTemp = NULL;
        char* textTemp = NULL;
        cadTemp = (char*)calloc(1,sizeof(char));
        textTemp = (char*)calloc(1,sizeof(char));
        *list = (int*)calloc(1,sizeof(int));
        int len = 0;

        for(int c = 0; c <= strlen(text);){
            if(text[c] != symbol){
                //SI ENCUENTRA QUE NO ES UN NUMERO ELIMINA LA MEMORIA DEL PUNTERO Y RETORNA 0
                if(isdigit(text[c]) != 1){
                    free(*list);
                    return 0;
                }

                cadTemp = (char*)realloc(cadTemp,(c+1)*sizeof(char));
                *textTemp = text[c];
                strcat(cadTemp,textTemp);
                strcpy(textTemp,"");
            }
            if((text[c] == symbol || c == strlen(text)-1)&&(atoi(cadTemp) != 0)){
                *list = (int*)realloc(*list,(len+1)*sizeof(int));
                //TRANSFORMA LA CADENA EN ENTEROS Y LOS AGREGA A LA LISTA DE INTS 
                *((*list)+len) = atoi(cadTemp); 
                strcpy(cadTemp,"");
                len++;
            }
        }
        return len;
    }
    return 0;
}

//REMOVER NUMEROS REPETIDOS DE UN ARRAY
int removeRepeteadNumbers(int** sequence, int lenSequence){
    int repeatCounter = 0;
    int zeroCounter = 0;
    for(int i = 0; i <= lenSequence-1; i++){
        for(int j = i+1; j <= lenSequence-1; j++){
            if((*((*sequence)+i)) == (*((*sequence)+j))&&((*((*sequence)+i)) != 0)){
                *((*sequence)+j) = 0;
                repeatCounter++;
            }
        }
    }
    for(int i = 0; i <= lenSequence-1; i++){
        while((*((*sequence)+i)) == 0 && zeroCounter <lenSequence){
            for(int j = i; j <= (lenSequence-2)-zeroCounter; j++){
                (*((*sequence)+j)) = (*((*sequence)+(j+1)));
            }
            zeroCounter++;
        }
    }
    *sequence = (int*)realloc(*sequence,(lenSequence-repeatCounter)*sizeof(int));
    return lenSequence-repeatCounter;
}

int srchIndex(int element, int** sequence, int lenSequence){
    for(int i = 0; i <= lenSequence-1; i++){
        if(*(*sequence+i) == element){
            return i;
        }
    }
    return -1;
}

//EVALUAR UNA FUNCION
float fXevaluate(char* function, float value){
    BinaryTree bTree;
    int len = strlen(function);
    int lenList;
    Slist* list;
    char* xFunction = (char*)calloc(len+1,sizeof(char));
    if(xFunction != NULL){
        //COPIO LOS DATOS DE ENTRADA A OTRA VARIABLE IDENTICA PARA NO MODIFICAR LA ENTRADA DEL USUARIO
        for(int i = 0; i <= strlen(function)-1; i++){
            *(xFunction+i) = *(function+i);
        }  
        printf("Linea 82\n");
        //REVISO QUE LA FUNCION ESTE BIEN ESCRITA Y LA ARREGLA, RETORNA LA LONGITUD DEL STRING DE xFunctions
        len = fXcheck(&xFunction,strlen(function));
        printf("Linea 85\n");
        //SEPARA EN ELEMENTOS DE UN ARRAY EL STRING DE LA FUNCION 
        lenList = fXSplit(xFunction,&list);
        //GENERA UN ARBOL BINARIO DE OPERACIONES
        printf("lenList: %d\n",lenList);
        for(int i = 0; i <= lenList-1; i++){
            printf("%d: %s\n",i,(list+i)->element);
        }
        bTree.BTAOGenerate(list,lenList);
        return bTree.BTAOEvaluate(value);
    }
    return 0;
}
//REVISA LA FUNCION DE ENTRADA DEL USUARIO Y DEVUELVE LA LONGITUD DEL STRING
int fXcheck(char** function, int lenFunction){   
    int len = lenFunction;
    char* fTemp = (char*)calloc(len,sizeof(char));
    for(int i = 0; i <= len-1; i++){
        *(fTemp+i) = *(*function+i);
    }
    for(int i = 0; i <= len-1; i++){
        if(*(*function+i) == 'x'){
            if(isdigit(*(*function+(i-1))) == 1){
                len = len + 1;
                *function = (char*)realloc(*function,len*sizeof(char));
                for(int c = i; c <= len-1; c++){
                    *(*function+(c+1)) = *(fTemp+c);
                } 
                *(*function+i) = '*';
                for(int i = 0; i <= len-1; i++){
                    *(fTemp+i) = *(*function+i);
                }
            }
        }
    }
    *(*function+len) = '\0';
    return len;
}
//SEPARA LA FUNCION DE ENTREDA EN ELEMENTOS DE UN ARRAY Y DEVUELVE LA LONGITUD
int fXSplit(char* function, Slist** list){
    free(list);
    *list = (Slist*)calloc(1,sizeof(Slist));
    int len = 0;
    int cLen = 0;
    int iNum = 0;
    char* sCad = (char*)calloc(2,sizeof(char));
    char* nCad = (char*)calloc(2,sizeof(char));
    char* cadTemp = (char*)calloc(2,sizeof(char));
    strcpy(nCad,"");
    int i = 0;
    printf("Function: %s\n",function);
    while(i <= strlen(function)-1){
        printf("\n%c, (==+: %d || ==-: %d || ==*: %d || ==/: %d || ==^: %d)&&(!= .: %d)\n",*(function+i),*(function+i) == '+',*(function+i) == '-',*(function+i) == '*',*(function+i) == '/',*(function+i) == '^',*(function+i) != '.');
        if((((*(function+i) == '+')||(*(function+i) == '-')||(*(function+i) == '*')||(*(function+i) == '/')||(*(function+i) == '^'))&&(*(function+i) != '.'))){
            printf("If\n");
            iNum = i+1;
            if(i < strlen(function)-1){
                //SIGNOS ARITMETICOS
                (*list+len)->element = (char*)calloc(2,sizeof(char));
                *sCad = *(function+i);
                printf("Linea 144");
                strcat(sCad,"\0");
                strcpy((*list+len)->element,sCad);
                len = len+1;
                *list = (Slist*)realloc(*list,(len+1)*sizeof(Slist));
                printf("Linea 149");
            }

            //ESPACIO EN MEMORIA PARA LA LISTA DE LA FUNCION
            cLen = 0;
            strcpy(nCad,"");
        }
        else{
            printf("Else\n");
            //SIEMPRE QUE NO SEA UN OPERADOR VERIFICA SI ES UN NUMERO Y LO AGREGA A UN STRING PARA DESPUES 
            //CUANDO DETECTA UN SIGNO AGREGA LA CADENA CORRESPONDIENTE AL NUMERO AL ARRAY 
            for(int c = iNum; c <= strlen(function)-1; c++){
                if((isdigit(*(function+c)) == 1)||(*(function+c) == 'x')||(*(function+c) == '.')){
                    cLen  = cLen+1;
                    printf("Linea 162\n");
                    nCad = (char*)realloc(nCad,(cLen+2)*sizeof(char));
                    printf("Linea 164\n");
                    printf("%c ",*(function+c));
                    *cadTemp = *(function+c);
                    *(nCad+(cLen-1)) = *cadTemp;
                }
                else{
                    break;
                }
                i = c;
            }
            *(nCad+cLen) = '\0';
            printf("\nnCad: %s\n",nCad);
            (*list+len)->element = (char*)calloc(cLen+2,sizeof(char));
            //strcpy((*list+len)->element,nCad);
            printf("Linea 176\n");
            for(int i = 0; i <= cLen-1; i++){
                *((*list+len)->element+i) = *(nCad+i);
            }
            len = len+1;
            *list = (Slist*)realloc(*list,(len+1)*sizeof(Slist));
            cLen = 0;
            strcpy(nCad,"");
        }
        i++;
    }
    return len;
}

int readString(String* string){
    free(*string);
    fflush(stdin);
    *string = (String)calloc(1,sizeof(char));
    if(*string != NULL){
        int sLen = 0;
        char buffer = ' ';
        while (true){
            if((buffer = getchar()) != '\n'){ 
                *((*string)+sLen) = buffer;
                sLen++;
                *string = (String)realloc(*string,(sLen+1)*sizeof(char));
            }else break;
        }	
        *((*string)+sLen) = '\0';
        return sLen;
    }
}

int readSchar(char** string){
    free(*string);
    *string = (char*)calloc(1,sizeof(char));
    if(*string != NULL){
        int sLen = 0;
        char buffer = ' ';
        fflush(stdin);
        while(true){
            if((buffer = getchar()) != '\n'){
                *((*string)+sLen) = buffer;
                sLen++;
                printf("Linea 222: %d\n",sLen);
                *string = (char*)realloc(*string,(sLen+3)*sizeof(char));
                if(string == NULL){
                    printf("\nError de memoria en la pocicion de %c\n",buffer);
                }
                else{
                   printf("con memoria\n"); 
                }
                printf("Linea 225\n");
            }else{
                printf("Finale de la cadena\n");
                break;
            }
        }
        *((*string)+sLen) = '\0';
        printf("Entra: %s, len: %d\n",*string,sLen);
        return sLen;
    }
    else printf("Memoria no agregada a la cadena de caracteres");
}
//CONVERTIR TODAS LAS LETRAS A MAYUSCULAS
//A h T m O p q N
//*((*string)+0) = A
void upperSChar(wchar_t** string, int len){
  if(*string != NULL){
        for (int i = 0; i < len; ++i)
        {
           *((*string)+i) = towupper(*((*string)+i)) ;//toupper*((*string)+i);c
        }   
    }
}