// Huff man Coding Implementation by Bhim K C


#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define MAX_TREE_HT 50

//************************* HtreeNODE CLASS *******************************/
class HtreeNode{
public:
    string chStr;
    int prob;
    string code;
    HtreeNode *left;
    HtreeNode *right;
    HtreeNode *next;
    bool leftNull, rightNull;
/*------------------ HtreeNODE Constructor -------------------------*/
    HtreeNode(string ch, int p, string c, HtreeNode* l, HtreeNode* r, HtreeNode* n){
        chStr = ch;
        prob = p;
        code = c;
        left = l;
        right = r;
        next = n;
    }
    HtreeNode(){
        chStr = "";
        prob = 0;
        code = "";
        left = NULL;
        right = NULL;
        next = NULL;
        }
    void printNode(HtreeNode* T, ofstream & ofile){
    leftNull = (T->left == NULL) ? true: false;
    rightNull = (T->right == NULL) ? true : false;
    if(leftNull && rightNull){
    ofile << "(" << T->chStr << "," << T->prob << "," << T->code << ",NULL ," << "NULL" << ")->";   
    }else if(rightNull){
    ofile << "(" << T->chStr << "," << T->prob << "," << T->code << "," << T->left->chStr << ", NULL" << ")->";
    }else if(leftNull){
    ofile << "(" << T->chStr << "," << T->prob << "," << T->code << ",NULL " << "," << T->right->chStr << ")->";
    }else{
    ofile << "(" << T->chStr << "," << T->prob << "," << T->code << "," << T->left->chStr << "," << T->right->chStr << ")->";
    }
    }
};

//************************* HuffmanBinaryTree CLASS *******************************/

class HuffmanBinaryTree {
public:
    HtreeNode *listHead;
    HtreeNode *root;
    string str;
    int prob;
/*------------------ HuffmanBinaryTree Constructor -------------------------*/
   
    HuffmanBinaryTree(){
        // this -> listHead = NULL;
        // this -> root = NULL;
    }
/*------------------ Find a spot -------------------------*/
    HtreeNode *findSpot(HtreeNode *node){
        HtreeNode* spot = listHead;
        while((spot->next != NULL) && (spot->next->prob < node->prob)){
            spot = spot->next;
        }
        return spot;
    } //done
/*------------------ Insert function -------------------------*/
    void listInsert(HtreeNode *findspot, HtreeNode *newNode ){
        
        newNode->next = findspot->next;

        findspot->next = newNode;

    } //done
/*------------------ Construt Huffman list -------------------------*/
    HtreeNode *constructHuffmanLList(ifstream &inFile, ofstream &outFile3){
        this->listHead = new HtreeNode("dummy",0,"",NULL,NULL,NULL);
        HtreeNode* newNode;
        while(inFile >> str >> prob){
            newNode = new HtreeNode(str, prob, "", NULL, NULL, NULL);
            listInsert(findSpot(newNode), newNode);
            printList(listHead, outFile3);
        }
        return listHead;       

    }
/*------------------ Construct Huffman Binary Tree -------------------------*/
    HtreeNode *constructHuffmanBinTree(ofstream &outFile3){
    HtreeNode *newNode;
    while(listHead->next->next != NULL){
        newNode = new HtreeNode();
        newNode->prob = listHead->next->prob + listHead->next->next->prob;
        newNode->chStr = listHead->next->chStr + listHead->next->next->chStr;
        newNode->left = listHead->next;
        newNode->right = listHead->next->next;
        newNode->next = NULL;
        listInsert(findSpot(newNode), newNode);
        listHead->next = listHead->next->next->next;
    }
    printList(listHead, outFile3);
    this->root = listHead->next;
    return listHead->next;
    }
/*------------------ PreOrder Traversal-------------------------*/
    void preOrderTraversal(HtreeNode* T, ofstream &outFile1){
        if(isLeaf(T)){
            T->printNode(T, outFile1);
        }else{
            T->printNode(T, outFile1);
            preOrderTraversal(T->left, outFile1);
            preOrderTraversal(T->right, outFile1);
        }
    }
/*------------------ inOrder Traversal-------------------------*/
    void inOrderTraversal(HtreeNode* T, ofstream &outFile1){
        if(isLeaf(T)){
            T->printNode(T, outFile1);
        }else{
            preOrderTraversal(T->left, outFile1);
            T->printNode(T, outFile1);
            preOrderTraversal(T->right, outFile1);
        }
    }
/*------------------ PostOrder Traversal-------------------------*/
    void postOrderTraversal(HtreeNode *T, ofstream &outFile1){
        if(isLeaf(T)){
            T->printNode(T, outFile1);
        }else{
            preOrderTraversal(T->left, outFile1);
            preOrderTraversal(T->right, outFile1);
            T->printNode(T, outFile1);
        }
    }
/*------------------ Construct Char Code-------------------------*/
    void constructCharCode(HtreeNode* T, string code, ofstream &outFile1){
        if(isLeaf(T)){
            T->code = code;
            outFile1 << (T->chStr + "," + T->code) << endl;
        }else{
            constructCharCode(T->left, code+="0", outFile1);
            constructCharCode(T->right, code+="1", outFile1);
        }
    }
/*------------------ Check leaf-------------------------*/

    bool isLeaf(HtreeNode* node){
        if(node->left == NULL && node->right == NULL)
            return true;
        return false;
    }
/*------------------ Print list-------------------------*/
    void printList(HtreeNode *listHead, ofstream &outFile){
        HtreeNode* spot = listHead;
        outFile <<"listHead->";
        while(spot != NULL){
            spot->printNode(spot, outFile);
            spot = spot->next;
        }
        outFile << endl;
    }


};


//************************* Main function *******************************/
int main(int argc, const char * argv[]) {
    ifstream inFile;
    inFile.open(argv[1]); 
    
    ofstream outFile1;
    outFile1.open(argv[2]);
    
    ofstream outFile2;
    outFile2.open(argv[3]);

    HuffmanBinaryTree huffmanTree;
    HtreeNode* listHead = huffmanTree.constructHuffmanLList(inFile, outFile2);
    huffmanTree.printList(listHead, outFile1);
    outFile1 << "\n";

    HtreeNode* root = huffmanTree.constructHuffmanBinTree(outFile2);
    outFile1 << "\n";
    huffmanTree.constructCharCode(root, "", outFile1);
    outFile1 << "\nPreOrder: \n";
    huffmanTree.preOrderTraversal(root, outFile1);
    outFile1 << "\nInOrder:\n";
    huffmanTree.inOrderTraversal(root, outFile1);
outFile1 << "\nPostOrder:\n";
    huffmanTree.postOrderTraversal(root, outFile1);
outFile1 << "\n";

    inFile.close();
    outFile1.close();
    outFile2.close();


}


