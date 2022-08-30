#include "../include/lib.h"


//____________________________________________________GENERAR ARBOL BINARIO DE OPERACIONES ARITMETICAS____________________________________________________________________________________
void BinaryTree::BTAOGenerate(Slist* sequence, int lenSequence){
    //FUNCION DE ENTRADA DE DATOS DEL USUARIO PARA GENERAR UN ARBOL BINARIO
    Slist* sequenceTemp = (Slist*)calloc(lenSequence,sizeof(Slist));
    char* cTemp = (char*)calloc(1,sizeof(char));
    for(int i = 0; i <= lenSequence-1; i++){
        (sequenceTemp+i)->element = (char*)calloc(strlen((sequence+i)->element),sizeof(char));
        strcpy((sequenceTemp+i)->element,(sequence+i)->element);
    }
    AORoute(sequenceTemp,0,lenSequence-1);
    const char xd[5] = "null";
    for(int i = 0; i <= lenSequence-1; i++){
        if(strcmp((sequenceTemp+i)->element,xd) != 0){
            AOGenerate(&AObinaryTree,&AOfather,(sequenceTemp+i)->element,i);
        }
    }
}
// 0      1    2   3   4   5   6     7    8   9  10    11
//[-],[0.775],[*],[x],[^],[2],[+],[1.77],[*],[x],[+],[2.530]
void BinaryTree::AORoute(Slist* sequence, int inicial, int final){
    //GENERAR EL ORDEN EN EL QUE SE ENVIAN LOS DATOS AL ARBOLBINARIO
    if(final > 0){
        for(int i = final; i >= inicial; i--){
            if((strcmp((sequence+i)->element,"+") == 0)||(strcmp((sequence+i)->element,"-") == 0)){
                AOGenerate(&AObinaryTree,&AOfather,(sequence+i)->element,i);
                strcpy((sequence+i)->element,"null");
                (sequence+i)->element = (char*)realloc((sequence+i)->element,5*sizeof(char));
                AORoute(sequence,inicial,i-1);
                AORoute(sequence,i+1,final);   
            }
        }
        for(int i = final; i >= inicial; i--){
            if((strcmp((sequence+i)->element,"*") == 0)||(strcmp((sequence+i)->element,"/") == 0)){
                AOGenerate(&AObinaryTree,&AOfather,(sequence+i)->element,i);
                strcpy((sequence+i)->element,"null");
                (sequence+i)->element = (char*)realloc((sequence+i)->element,5*sizeof(char));
                AORoute(sequence,inicial,i-1);
                AORoute(sequence,i+1,final);   
            }
        }
        for(int i = final; i >= inicial; i--){
            if(strcmp((sequence+i)->element,"^") == 0){
                AOGenerate(&AObinaryTree,&AOfather,(sequence+i)->element,i);
                strcpy((sequence+i)->element,"null");
                (sequence+i)->element = (char*)realloc((sequence+i)->element,5*sizeof(char));
                AORoute(sequence,inicial,i-1);
                AORoute(sequence,i+1,final);   
            }
        }
    }
}   
void BinaryTree::AOGenerate(AOBTree** nodo, AOBTree** father, char* element, int index){
    //GENERAR UN ARBOL BINARIO DE OPERACIONES ARITMETICAS
    if(*nodo == NULL){
        free(*nodo);
        *nodo = (AOBTree*)calloc(1,sizeof(AOBTree));
        (*nodo)->index = index;
        (*nodo)->element = (char*)calloc(strlen(element)+1,sizeof(char));
        strcpy((*nodo)->element,element);
        (*nodo)->left = NULL;
        (*nodo)->rigth = NULL;

        if(*father != NULL){
            if(index > (*father)->index){
                //SI EL ELEMENTO ES MAYOR QUE EL NODO PADRE SE POSICIONA A LA DERECHA DEL NODO PADRE
                (*father)->rigth = *nodo;
            }else{
                //SI EL ELEMENTO ES MENOR SE POSICIONA A LA IZQUIERDA DEL NODO PADRE
                (*father)->left = *nodo;
            }
        } 
        else{
            //SI EL NODO PADRE ES NULL SIGNIFICA QUE EL EL NODO RAIZ Y RETORNA
            return;
        }
    }else{
        //ENTRA AQUI SI EL NODO ACTUAL ES DIFERENTE A NULL, OSEA SI TIENE MEMORIA Y ESTA LLENO
        if(index > (*nodo)->index){
            //SI EL VALOR DE LA SECUENCIA ES MAYOR AL NODO HACE UN PROCESO RECURSIVO PARA MANDAR AL NODO HIJO DE LA PARTE DERECHA A ESTA MISMA FUNCION
            AOGenerate(&(*nodo)->rigth, &*nodo, element,index);
        }
        if(index < (*nodo)->index){
            //SI EL VALOR DE LA SECUENCIA ES MENOR AL NODO HACE UN PROCESO RECURSIVO PARA MANDAR AL NODO HIJO DE LA PARTE IZQUIERDA A ESTA MISMA FUNCION
            AOGenerate(&(*nodo)->left, &*nodo, element,index);
        }
    }
}

//____________________________________________________EVALUAR LA OPERACION DEL ARBOL____________________________________________________________________________________
float BinaryTree::BTAOEvaluate(float value){
    AOEvaluate(&AObinaryTree,value);
    return AObinaryTree->result;
}

void BinaryTree::AOEvaluate(AOBTree** nodo, float value){
    if(*nodo != NULL){
        if((isdigit(*(*nodo)->element) != 1)&&(*(*nodo)->element != 'x')){
            if((*nodo)->left != NULL){
                AOEvaluate(&(*nodo)->left,value);
                (*nodo)->rLeft = (*nodo)->left->result;
            }
            else{
                if((strcmp((*nodo)->element,"+") == 0)||(strcmp((*nodo)->element,"-") == 0)) (*nodo)->rLeft = 0.0;
                else if((strcmp((*nodo)->element,"*") == 0)||(strcmp((*nodo)->element,"/") == 0)) (*nodo)->rLeft = 1.0;
            }
            if((*nodo)->rigth != NULL){
                AOEvaluate(&(*nodo)->rigth,value);
                (*nodo)->rRigth = (*nodo)->rigth->result;
            }
            else{

                if((strcmp((*nodo)->element,"+") == 0)||(strcmp((*nodo)->element,"-") == 0)) (*nodo)->rRigth = 0.0;
                else if((strcmp((*nodo)->element,"*") == 0)||(strcmp((*nodo)->element,"/") == 0)) (*nodo)->rRigth = 1.0;
                else if(strcmp((*nodo)->element,"^") == 0) (*nodo)->rRigth = 1;
            }

            //OBTENER LOS RESULTADOS
            if(strcmp((*nodo)->element,"+") == 0) (*nodo)->result = (*nodo)->rLeft+(*nodo)->rRigth;
            else if(strcmp((*nodo)->element,"-") == 0) (*nodo)->result = (*nodo)->rLeft - (*nodo)->rRigth;
            else if(strcmp((*nodo)->element,"*") == 0) (*nodo)->result = (*nodo)->rLeft * (*nodo)->rRigth;
            else if(strcmp((*nodo)->element,"/") == 0){
                if((*nodo)->rRigth != 0.0){
                    (*nodo)->result = (*nodo)->rLeft / (*nodo)->rRigth;
                }
                else{
                    printf("\nDivision por '0' no contemplada\n");
                    exit(0);
                }
            }
            else if(strcmp((*nodo)->element,"^") == 0){
                (*nodo)->result = (*nodo)->rLeft;
                for(int i = 0; i <= (int)(*nodo)->rRigth-2; i++){
                    (*nodo)->result = (*nodo)->result * (*nodo)->rLeft;  
                }
            }
        }
        else{

            if(strcmp((*nodo)->element,"x") == 0){
                sprintf((*nodo)->element,"%f",value);
            }
            for(int i = 0; i <= strlen((*nodo)->element)-1 ; i++){
                if((isdigit(*((*nodo)->element+i)) != 1)&&(*((*nodo)->element+i) != '.')){
                    printf("error");
                    exit(0);
                }
            }
            (*nodo)->result = atof((*nodo)->element);
        }
    }
}