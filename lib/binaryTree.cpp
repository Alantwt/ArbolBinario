#include "../include/lib.h"

//____________________________________________________GENERAR ARBOL BINARIO____________________________________________________________________________________
void BinaryTree::BTGenerate(int** sequence, int lenSequence){
    treeWeigth = 0;
    Clear(&binaryTree);
    BTree* father  = NULL;
    treeWeigth = 0;
    for(int i = 0; i <= lenSequence-1; i++){
        Generate(&binaryTree,&father,*(*sequence+i));
    }
    //treeWeigth = lenSequence;
    btreeCreated = true;
}
void BinaryTree::Generate(BTree** nodo, BTree** father, int element){
    if(*nodo == NULL){
        treeWeigth++;
        //printf("nuevo nodo: %d\n",element);
        free(*nodo);
        *nodo = (BTree*)calloc(1,sizeof(BTree));
        (*nodo)->element = element;
        (*nodo)->rigth = NULL;
        (*nodo)->left = NULL;
        if(*father != NULL){
            //printf("father: %d, son: %d\n",(*father)->element,element);
            if(element > (*father)->element){
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
        //printf("nodo: %d\n",(*nodo)->element);
        if(element > (*nodo)->element){
            //SI EL VALOR DE LA SECUENCIA ES MAYOR AL NODO HACE UN PROCESO RECURSIVO PARA MANDAR AL NODO HIJO DE LA PARTE DERECHA A ESTA MISMA FUNCION
            Generate(&(*nodo)->rigth, &*nodo, element);
        }
        if(element < (*nodo)->element){
            //SI EL VALOR DE LA SECUENCIA ES MENOR AL NODO HACE UN PROCESO RECURSIVO PARA MANDAR AL NODO HIJO DE LA PARTE IZQUIERDA A ESTA MISMA FUNCION
            Generate(&(*nodo)->left, &*nodo, element);
        }
    }
}
//____________________________________________________BUSCAR LA ALTURA DEL ARBOL BINARIO____________________________________________________________________________________
int BinaryTree::BTSrchHeigth(){
    treeHeigth = 0;
    if(btreeCreated == true){
        srchHeigth(&binaryTree);
        return treeHeigth;
    }
}
void BinaryTree::srchHeigth(BTree** nodo){
    if((*nodo) != NULL){
        heigthCounter++;
        if((*nodo)->left == NULL && (*nodo)->rigth == NULL && (*nodo)->element > treeHeigth){
            treeHeigth = heigthCounter;
        }
        if((*nodo)->left != NULL){
            srchHeigth(&(*nodo)->left);
        }
        if((*nodo)->rigth != NULL){
            srchHeigth(&(*nodo)->rigth);
        }
        heigthCounter--;
    }
}
//____________________________________________________BUSCAR LA ALTURA DE UN NODO____________________________________________________________________________________
int BinaryTree::BTSrchHeigthOf(int element){
    counterHeigth = 0;
    nodoFound = false;
    SrchHeigthOf(&binaryTree,element);
    if(nodoFound == true){
       return heigthFound; 
    }
    else return 0;
}
void BinaryTree::SrchHeigthOf(BTree** nodo, int element){
    counterHeigth++;
    if(*(nodo) != NULL){
        if(element == (*nodo)->element){
           heigthFound = counterHeigth;
           nodoFound = true;
        }
        if((*nodo)->left != NULL){
            SrchHeigthOf(&(*nodo)->left,element);
        }
        if((*nodo) != NULL){
            SrchHeigthOf(&(*nodo)->rigth,element);
        }
    }//else printf("Sin Elementos\n");
    counterHeigth--;
}
//____________________________________________________BUSCAR UN NODO____________________________________________________________________________________
int BinaryTree::BTSrchNodo(int element){
    if(btreeCreated == true){
        free(nodosList);
        nodosList = (int*)calloc(1,sizeof(int));
        nodoFound = false;
        lenNodoList = 0;
        srchNodo(&binaryTree,element);
        if(nodoFound == true)return lenNodoList;
        else{
            free(nodosList);
            lenNodoList = 0; 
            return 0;
        }
    }
    else return 0;
}
void BinaryTree::srchNodo(BTree** nodo, int element){
    if((*nodo)->element == element){
        nodoFound = true;
        *(nodosList+lenNodoList) = (*nodo)->element;
        lenNodoList++;
        nodosList = (int*)realloc(nodosList,(lenNodoList)*sizeof(int));
        deleteNodo = &(*nodo);
    }
    if(nodoFound == false){
        *(nodosList+lenNodoList) = (*nodo)->element;
        lenNodoList++;
        nodosList = (int*)realloc(nodosList,(lenNodoList+1)*sizeof(int));
        if((element < (*nodo)->element)&&((*nodo)->left != NULL)){
            srchNodo(&(*nodo)->left,element);
        }
        if((element > (*nodo)->element)&&((*nodo)->rigth != NULL)){
            srchNodo(&(*nodo)->rigth,element);
        }
    }
}
//____________________________________________________BUSCAR TODOS LOS NODOS PADRES____________________________________________________________________________________
int BinaryTree::BTSrchFathers(int** fathersList){
    free(*fathersList);
    *fathersList = (int*)calloc(1,sizeof(int));
    int* sequense = NULL;
    int lenSequence = BTInOrder(&sequense);
    int lenFathers = 0, father;
    for(int i = 0; i <= lenSequence-1; i++){
        father = BTSrchFatherOf(*(sequense+i));
        if(father != 0){
            *(*fathersList+lenFathers) = father;
            lenFathers++;
            *fathersList = (int*)realloc(*fathersList,(lenFathers+1)*sizeof(int));
        }
    }
    return lenFathers;
}
//____________________________________________________BUSCAR EL NODO PADRE DE UN NODO____________________________________________________________________________________
int BinaryTree::BTSrchFatherOf(int element){
    fatherNodo = 0;
    fatherFound = false;
    srchFather(&binaryTree, element);
    if(fatherFound == true)return fatherNodo;
    else return 0;
}
void BinaryTree::srchFather(BTree** nodo, int element){
    if(*nodo != NULL && fatherFound == false){
        if((*nodo)->left != NULL){
            if((*nodo)->left->element == element){
                fatherFound = true;
            }
        }
        if((*nodo)->rigth != NULL){
            if((*nodo)->rigth->element == element){
                fatherFound = true;
            }
        }
        if(fatherFound == true){
            fatherNodo = (*nodo)->element;
        }
        else {
            srchFather(&(*nodo)->left,element);
            srchFather(&(*nodo)->rigth,element);
        }
    }
    else return;
}
//____________________________________________________BUSCAR TODOS LOS NODO HOJA____________________________________________________________________________________
int BinaryTree::BTSrchLeafs(int** sequence){
    if(btreeCreated == true){
        free(*sequence);
        *sequence = (int*)calloc(1,sizeof(int));
        lenNodoList = 0;
        srchLeafs(&binaryTree,sequence);
        return lenNodoList;
    }
    else return 0;
}
void BinaryTree::srchLeafs(BTree** nodo, int** sequence){
    if(((*nodo)->left == NULL)&&((*nodo)->rigth == NULL)){
        *(*sequence+lenNodoList) = (*nodo)->element;
        lenNodoList++;
        *sequence= (int*)realloc(*sequence,(lenNodoList+1)*sizeof(int));
    }
    if((*nodo)->left != NULL){
        srchLeafs(&(*nodo)->left,sequence);
    }
    if((*nodo)->rigth != NULL){
        srchLeafs(&(*nodo)->rigth,sequence);
    }
}
//____________________________________________________RECORRER EL ARBOL INORDER____________________________________________________________________________________
int BinaryTree::BTInOrder(int** sequence){
    orderCounter = 0;
    free(*sequence);
    *sequence = (int*)calloc(1,sizeof(int));
    if(btreeCreated == true){
        inOrder(&binaryTree,sequence);
        return treeWeigth;
    }
    else{
        orderCounter = 0; 
        return 0;
    }
}
//PROCESO RECURSIVO INORDER
void BinaryTree::inOrder(BTree** nodo, int** sequence){
    if(*nodo != NULL){
        if(orderCounter == treeWeigth)return;
        if((*nodo)->left != NULL){
            inOrder(&(*nodo)->left,sequence);
        }
        *(*sequence+orderCounter) = (*nodo)->element;
        orderCounter++;
        *sequence = (int*)realloc(*sequence,(orderCounter+1)*sizeof(int));
        if((*nodo)->rigth != NULL){
            inOrder(&(*nodo)->rigth,sequence);
        }
    }   
}
//____________________________________________________RECORRER EL ARBOL POSTORDER____________________________________________________________________________________
int BinaryTree::BTPostOrder(int** sequence){
    orderCounter = 0;
    free(*sequence);
    *sequence = (int*)calloc(1,sizeof(int));
    if(btreeCreated == true){
        postOrder(&binaryTree,sequence);
        return treeWeigth;
    }
    else{
        orderCounter = 0; 
        return 0;
    }
}
//PROCESO RECURSIVO POSTORDER
void BinaryTree::postOrder(BTree** nodo, int** sequence){
    if(*nodo != NULL){
        if(counterHeigth == treeWeigth)return; 
        if((*nodo)->left != NULL){
            postOrder(&(*nodo)->left,sequence); 
        }
        if((*nodo)->rigth != NULL){
            postOrder(&(*nodo)->rigth,sequence); 
        }
        *(*sequence+orderCounter) = (*nodo)->element;
        orderCounter++;
        *sequence = (int*)realloc(*sequence,(orderCounter+1)*sizeof(int));
    }
}
//____________________________________________________RECORRER EL ARBOL PREORDER____________________________________________________________________________________
int BinaryTree::BTPreOrder(int** sequence){
    orderCounter = 0;
    free(*sequence);
    *sequence = (int*)calloc(1,sizeof(int));
    if(btreeCreated == true){
        preOrder(&binaryTree,sequence);
        return treeWeigth;
    }
    else{
        orderCounter = 0; 
        return 0;
    }
}
//PROCESO RECURSIVO PREORDER
void BinaryTree::preOrder(BTree** nodo, int** sequence){
    if(*nodo != NULL){
        if(counterHeigth == treeWeigth)return;
        *(*sequence+orderCounter) = (*nodo)->element;
        orderCounter++;
        *sequence = (int*)realloc(*sequence,(orderCounter+1)*sizeof(int));
        if((*nodo)->left != NULL){
            preOrder(&(*nodo)->left,sequence);
        }
        if((*nodo)->rigth != NULL){
            preOrder(&(*nodo)->rigth,sequence);
        }
    }
}
//____________________________________________________BORRAR/LIMPIAR EL ARBOL BINARIO____________________________________________________________________________________
void BinaryTree::BTClear(){
    Clear(&binaryTree);
    btreeCreated = false;
}
void BinaryTree::Clear(BTree** nodo){
    if(*nodo != NULL){
        if((*nodo)->left != NULL){
            Clear(&(*nodo)->left);
            (*nodo)->left = NULL;
        }
        if((*nodo)->rigth != NULL){
            Clear(&(*nodo)->rigth);
            (*nodo)->rigth = NULL;
        }
        *nodo = NULL;
    }
    btreeCreated = false;
}
//____________________________________________________BORRAR UN NODO EN CONCRETO____________________________________________________________________________________
void BinaryTree::BTDeleteNodo(int element){
    if(BTSrchNodo(element) != 0 && element != 0){
        free(replaceNodo);
        BTree* nodoTemp = (BTree*)calloc(1,sizeof(BTree));
        nodoTemp->element = 0;
        replaceNodo = (BTree**)calloc(1,sizeof(BTree));//&(*deleteNodo)->left;
        replaceNodo = &nodoTemp;  
        printf("Borrar: %d\n",(*deleteNodo)->element);

        //BORRAR EL ELEMENTO SELECCIONADO
        if((*deleteNodo)->left == NULL && (*deleteNodo)->rigth == NULL){
            (*deleteNodo) = NULL;
        }
        else{
            if((*deleteNodo)->left != NULL){
                replaceDeleteNodoL(&(*deleteNodo)->left);
            }
            else if((*deleteNodo)->rigth != NULL){
                replaceDeleteNodoL(&(*deleteNodo)->rigth);
                replaceDeleteNodoR(&(*deleteNodo)->rigth);
            }
            (*deleteNodo)->element = (*replaceNodo)->element;
        }
        //BORRAR EL ELEMENTO QUE SE REEMPLAZO
        if((*replaceNodo)->left == NULL && (*replaceNodo)->rigth == NULL){
            (*replaceNodo) = NULL;
        }
        else{
            if((*replaceNodo)->left != NULL){
                (*replaceNodo) = (*replaceNodo)->left;
            }
            else if((*replaceNodo)->rigth != NULL){
                (*replaceNodo) = (*replaceNodo)->rigth;
            }
        }
        treeWeigth--;
    }
}
void BinaryTree::replaceDeleteNodoL(BTree** nodo){  
    if((*nodo)->element > (*replaceNodo)->element){
        replaceNodo = &(*nodo);
    }
    if((*nodo)->left != NULL){
        replaceDeleteNodoL(&(*nodo)->left);
    }
    if((*nodo)->rigth != NULL){
        replaceDeleteNodoL(&(*nodo)->rigth);
    }
}
void BinaryTree::replaceDeleteNodoR(BTree** nodo){
    if((*nodo)->element < (*replaceNodo)->element){
        replaceNodo = &(*nodo);
    }
    if((*nodo)->left != NULL){
        replaceDeleteNodoR(&(*nodo)->left);
    }
    if((*nodo)->rigth != NULL){
        replaceDeleteNodoR(&(*nodo)->rigth);
    }
}
//____________________________________________________INSERTAR UN NODO EN CONCRETO____________________________________________________________________________________
void BinaryTree::BTInsertNodo(int element){
    Generate(&binaryTree,NULL,element);
    treeWeigth++;
}   