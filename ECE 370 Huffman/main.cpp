#include <iostream>
#include <fstream>

using namespace std;

struct node{
    int freq; //probability/frequency info
    char letter; //English letter
    bool saved;
    node* left;
    node* right; //these are linked list pointers to the next nodes
    node();
};

node::node(){
    //zero the node out by default
    left = NULL;
    right = NULL;
    letter = 0;
    saved = false;
}

void swapNodes(node *&nodeA, node *&nodeB){//need to use addresses otherwise the actual nodes won't be swapped
    //function will swap the values contained in the nodes
    node *temp;
    temp = new node; //initialize node
    temp = nodeA;
    nodeA = nodeB;
    nodeB = temp;
}

void huffTree(node *&huffRoot,int &sampleNum, ifstream &fileA){ //so far, I can't pass a structure array through,
    //and variable have to be passed via their addresses, otherwise program won't build

    //function will order the nodes from largest to smallest,
    //then begin to merge them according to huffman
    //first read in all the values
    int i,j,currentNode,left2merge;
    currentNode = sampleNum; //we want to look at the last(smallest) node in the array at all times with this number, for the most part
    left2merge = sampleNum; //Counts how many samples are left in the list to be merged
    node *nodeList[52]; //list of nodes, tried to use SAMPMAX global variable, but only works using 52
    node *mergedNode;






    //first we populate the nodeList with all samples
    for(i=0;i<sampleNum;i++){
        nodeList[i] = new node; //node must be initialized this way for each index, or program will crash

        fileA >> nodeList[i]->letter;
        //cout<<nodeList[i]->letter; //test code
        fileA >> nodeList[i]->freq;
        //cout<<"\t"<<nodeList[i]->freq<<endl; //test code
    }//for




while(left2merge>1){//this should loop the reordering and merging of the nodes until there are only two nodes left to be merged
    //we will need something to loop through, reordering the nodes after each time we merge them

    //now we need to cycle through the list of samples and reorder them
currentNode = left2merge;

    for(i=1;i<left2merge+1;i++){
        currentNode = i;
    while(currentNode>0){

            if(nodeList[currentNode]->freq > nodeList[currentNode-1]->freq){
                        //if the current node is larger than the previous, swap them
                        //this will order the smaller nodes toward the end of the array, index n-1
                        swapNodes(nodeList[currentNode],nodeList[currentNode-1]);
                        //cout<<"swapped: "<<nodeList[j]->freq<<"\t"<<nodeList[j-1]->freq<<endl;
                        currentNode--;
            }//if
            else{
                break;
            }//else
    }//while


        }//for



         //test code to check if nodes are ordered
    cout<<"Nodes after ordering:\nIndex:\tValue:"<<endl;
    for(i=0;i<left2merge;i++){
        //test code to see if list got ordered correctly
        cout<<i<<"\t"<<nodeList[i]->freq<<endl;
    }//for



        //nodes are reordered, now we need to take the smallest two and merge them
    mergedNode = new node;//this will store the new merged node, starts us with a new blank node
    mergedNode->left = nodeList[left2merge-1];
    mergedNode->right = nodeList[left2merge-2];
    mergedNode->freq = nodeList[left2merge-1]->freq + nodeList[left2merge-2]->freq;
    //cout<<"Merging: "<<nodeList[left2merge-1]->freq<<"\t"<<nodeList[left2merge-2]->freq<<endl;
    nodeList[left2merge-2] = mergedNode;//reinserting the merged node

    //cout<<nodeList[left2merge-2]->freq<<endl;
    left2merge--;//decrement index counter so we don't access already used nodes

    //once current node hits 1, there are only 2 more nodes left to order, one of which is useless anyway.
    //The one at index zero is the root of the huffman tree

    huffRoot = nodeList[0];//output root to main function
    /*
    cout<<"Root Node Values"<<endl;
    cout<<"Freq: "<<nodeList[0]->freq<<endl;
    cout<<"Letter: "<<nodeList[0]->letter<<endl;
    */


    }//while
return;
}

void huffSolve(node *huffRoot,node *currentNode, int &bitCount, int &saveIndex, char letters[], int binaryCode[][26], bool &noSamp){
    if((currentNode->left != NULL)&&(currentNode->left->saved==false)){
        //checking left side of tree first
        binaryCode[saveIndex][bitCount] = 0;//setting all left branches to 0
        if((currentNode->left->saved == true)&&(currentNode->right->saved == true)){
            //if the current node is an internal node, flag it so it isn't considered later
            currentNode->saved = true;
            noSamp = true;
            return;
        }
        bitCount++;
        huffSolve(huffRoot, currentNode->left, bitCount, saveIndex, letters, binaryCode, noSamp); //recursively check left subtree then right subtree
        return;
    }
    if(currentNode->letter != 0){
        letters[saveIndex] = currentNode->letter;//save letter to array
        binaryCode[saveIndex][bitCount] = 0;//because this is the final left branch
        currentNode->saved = true; //we saved this leaf node
        saveIndex++;//increment to the next space in array
        return;
    }
    if((currentNode->right != NULL)&&(currentNode->right->saved == false)){
        binaryCode[saveIndex][bitCount] = 1;//setting all right branches to 1
        if((currentNode->left->saved == true)&&(currentNode->right->saved == true)){
            //if current node is internal, flag it so it isn't considered later
            currentNode->saved = true;
            noSamp = true;
            return;
        }
        bitCount++;
        huffSolve(huffRoot,currentNode->right,bitCount, saveIndex, letters, binaryCode, noSamp);//recursively check left subtree then right subtree
        return;
    }
    if((currentNode->left != NULL && currentNode->left->saved == true)&& (currentNode->right != NULL && currentNode->right->saved == true)){
            //error checking
        currentNode->saved = true;
        noSamp = true;
        return;
    }

}
void codeSort(char letters[], int binaryCode[][26],int sampNum){
    int delta = sampNum;
    int A = 0;
    int B = 0;
    int flag;
    while(delta>1){
        delta /= 2;
        do{
            flag = 1;
            for(A=0;A<sampNum-delta;A++){
                B=A+delta;
                if(letters[A]>letters[B]){
                    char temp;
                    char binTemp[26];
                    temp = letters[A];
                    letters[A]=letters[B];
                    letters[B]=temp;
                    for(int i=0;i<26;i++){
                        binTemp[i] = binaryCode[A][i];
                        binaryCode[A][i]=binaryCode[B][i];
                        binaryCode[B][i]=binTemp[i];
                    }
                    flag=0;
                }
            }
        }
        while(flag==0);
    }
}

void huffCodes(node *&huffRoot, int sampNum){
    //This will figure out the codes for each English letter(leaf)
    //code will be binary from root to leaf
    //Basically, traverse the tree in
    int i,j,zIndex;
    char letters[26];//create an array to hold up to 26 possible letters,
    //when a letter has been assigned a binary code, the letter will be saved here
    int binaryCode[26][26];//this array stores the binary code of each letter that is completed.
    //The index of letter array corresponds to the first index of this array
    int saveIndex = 0;//This is the index that will be used to save values to the letters and BinaryCode arrays correctly
    int bitCount = 0;//How many bits are going to be stored in array, serves as the index
    bool noSamp = false; //keeps track of whether a node is a leaf(letter) or not
    node *currentNode;//a node that we can manipulate so we don't mess up the original huff tree

    for(i=0;i<sampNum;i++){
        bitCount = 0;//resetting for each new entry
        currentNode = huffRoot;
        huffSolve(huffRoot, currentNode,bitCount,saveIndex, letters,binaryCode, noSamp);
        if(noSamp){
            for(zIndex = 0;zIndex<bitCount;zIndex++){
                binaryCode[saveIndex][zIndex] = 0;//padding binary code with zeroes for blank space
            }//for
            i--;
            noSamp = false;
            cout<<i<<"\t"<<noSamp<<"\t"<<bitCount<<endl;
        }//if



        }//for
        //sort samples in alphabetical order and reverse binary
        codeSort(letters,binaryCode,sampNum);

        cout<<"Code Key:"<<endl;
        for(j=0;j<sampNum;j++){
                cout<<letters[j]<<"\t";
                for(i=0;i<26;i++){

            cout<<binaryCode[j][i];
                }
                cout<<endl;
        }
        return;

    }//void




int main()
{
    int SAMPMAX = 52; //sample space contains no more than 52 samples
    int sampleNum,i;
    node *huffRoot; //this will be the root node after passing through huff function
    huffRoot = new node;//initialize node


    ifstream fileA;
    ifstream fileB;

    fileA.open("a3-1.txt");
    fileB.open("a3-2.txt");

    fileA >> sampleNum;
    cout<<"Number of Samples: "<<sampleNum<<endl;

    huffTree(huffRoot, sampleNum,fileA);
    huffCodes(huffRoot,sampleNum);


}
