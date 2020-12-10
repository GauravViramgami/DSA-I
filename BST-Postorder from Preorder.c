#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

void generatePostOrder (int* preOrder, int* postOrder, int startIndexPre, int endIndexPre, int startIndexPost, int endIndexPost);

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n; //Number of nodes in BST
    scanf("%d", &n);
    
    int preOrder[n];
    for (int i = 0; i < n; i++) { //Store the input in preOrder
        scanf("%d", &preOrder[i]);
    }
    
    int postOrder[n];
    generatePostOrder(preOrder, postOrder, 0, n-1, 0, n-1); //Store the output in postOrder
    
    for (int i = 0; i < n; i++) { //Print postOrder
        printf("%d ", postOrder[i]);
    }
    
    return 0;
}

void generatePostOrder (int* preOrder, int* postOrder, int startIndexPre, int endIndexPre, int startIndexPost, int endIndexPost) { //Recursive function 
    
    if (startIndexPre == endIndexPre) { //If there is only one element in subtree - End of that subtree
        int node = preOrder[startIndexPre];
        postOrder[endIndexPost] = node;
    } else if (startIndexPre < endIndexPre) { //Else if size of subtree > 0
        int node = preOrder[startIndexPre]; //First element in preorder of subtree is last element in postOrder of subtree
        postOrder[endIndexPost] = node;
        int leftTreeStartIndexPre = startIndexPre + 1; //Divide the tree into two subtrees - left and right
        int leftTreeStartIndexPost = startIndexPost; //Indexes for the preOrder array and postOrder array
        int rightTreeEndIndexPre = endIndexPre;
        int rightTreeEndIndexPost = endIndexPost - 1;
        
        int index = startIndexPre + 1;
        int indexPost = startIndexPost;
        while (index <= endIndexPre && preOrder[index] <= node) { //Finding end index of left subtree using the BST property - left child <= node <= right child
            index ++;
            indexPost ++;
        }
        
        int leftTreeEndIndexPre = index - 1;
        int leftTreeEndIndexPost = indexPost - 1;
        int rightTreeStartIndexPre = index;
        int rightTreeStartIndexPost = indexPost;
        
        generatePostOrder(preOrder, postOrder, leftTreeStartIndexPre, leftTreeEndIndexPre, leftTreeStartIndexPost, leftTreeEndIndexPost); //Run the function recursively on left subtree
        generatePostOrder(preOrder, postOrder, rightTreeStartIndexPre, rightTreeEndIndexPre, rightTreeStartIndexPost, rightTreeEndIndexPost); //Run the function recursively on right subtree
    }
}