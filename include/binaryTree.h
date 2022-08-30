#ifndef _BINARYTREE
#define _BINARYTREE

#include "../include/lib.h"

//BINARY TREE STRUCT
struct BTree
{
    int element;
    BTree* left;
    BTree* rigth;
};

struct AOBTree{
    char* element;
    int index;
    float result;
    float rLeft;
    float rRigth;
    AOBTree* left;
    AOBTree* rigth;
};



//BINARY TREE CLASS
class BinaryTree{
private:
    //VARIABLES
    //________________________AOBINARYTREE______________________
    AOBTree* AOfather = NULL;
    //________________________BINARYTREE________________________
    int counterHeigth = 0, heigthFound = 0;
    bool nodoFound = false;
    bool fatherFound = false, btreeCreated = false;
    int fatherNodo = 0;
    int orderCounter = 0, heigthCounter = 0;
    BTree** deleteNodo = NULL;
    BTree** replaceNodo = NULL;
    //________________________CHAR_BINARYTREE____________________

    //FUNCIONES
    //________________________AOBINARYTREE______________________
    void AORoute(Slist* sequence, int inicial, int final);
    void AOGenerate(AOBTree** nodo, AOBTree** father, char* element, int index);
    void AOEvaluate(AOBTree** nodo, float value);
    //________________________BINARYTREE________________________
    void Generate(BTree** nodo, BTree** father, int element);
    void inOrder(BTree** nodo, int** sequence);
    void postOrder(BTree** nodo, int** sequence);
    void preOrder(BTree** nodo, int** sequence);
    void SrchHeigthOf(BTree** nodo, int element);
    void srchNodo(BTree** nodo, int element);
    void srchFather(BTree** nodo, int element);
    void srchLeafs(BTree** nodo, int** sequence);
    void Clear(BTree** nodo);
    void replaceDeleteNodoL(BTree** nodo);
    void replaceDeleteNodoR(BTree** nodo);
    void srchHeigth(BTree** nodo);
public:
    //VARIABLES
    //________________________AOBINARYTREE______________________
    AOBTree* AObinaryTree = NULL;
    //________________________BINARYTREE________________________
    BTree* binaryTree = NULL;
    int lenNodoList = 0;
    int* nodosList = NULL;
    int treeWeigth = 0, treeHeigth = 0;
    //FUNCIONES
    //BinaryTree();
    //________________________AOBINARYTREE______________________
    void BTAOGenerate(Slist* sequence, int lenSequence);
    float BTAOEvaluate(float value);
    //________________________BINARYTREE________________________
    void BTGenerate(int** sequence, int lenSequence);
    int BTSrchHeigth();
    int BTSrchHeigthOf(int element);
    int BTSrchNodo(int element);
    int BTSrchFathers(int** fathersList);
    int BTSrchFatherOf(int element);
    int BTSrchLeafs(int** sequence);
    int BTInOrder(int** sequence);
    int BTPostOrder(int** sequence);
    int BTPreOrder(int** sequence);
    void BTClear();
    void BTDeleteNodo(int element);
    void BTInsertNodo(int element);
};

#include "../lib/binaryTree.cpp"
#include "../lib/AObinaryTree.cpp"

#endif