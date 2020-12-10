#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

struct node { //Define Node
  int data;
  struct node *leftChild;
  struct node *rightChild;
  int height; //To print height
};

int max(int a, int b);
int height(struct node *root);
struct node *newNode(int data);
struct node *insert(struct node *root, int data);

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int t;
    scanf("%d", &t);
    
    while (t--) {
        int n;
        scanf("%d", &n);
        
        int node;
        struct node *root = NULL; //Initialize root with NULL
        for (int i = 0; i < n; i++) {
            scanf("%d", &node);
            root = insert(root, node); //Insert each data
        }
        
        printf("%d\n", root->height); //Print the height of the root
    }
    return 0;
}

int max (int a, int b) {
    return (a > b)?a:b; //Return max
}

int height (struct node *root) { //Return height
    if (root == NULL) {
        return 0;
    } else {
        return root->height;
    }
}

struct node *newNode (int data) { //Return a pointer after creating a new node
    struct node *p = (struct node *)malloc(sizeof(struct node));
    p->data = data;
    p->leftChild = NULL;
    p->rightChild = NULL;
    p->height = 1; //Assign height = 1 as it is a leaf node initially
    
    return p;
}

struct node *insert (struct node *root, int data) {
    if (root == NULL) { //If root is NULL then make a root
        return newNode(data);
    } else if (data > root->data) { //Else traverse through the BST to find correct place and insert the data (leftChild <= node <= rightChild)
        root->rightChild = insert(root->rightChild, data);
    } else {
        root->leftChild = insert(root->leftChild, data);
    }
    
    root->height = 1 + max(height(root->leftChild), height(root->rightChild)); //Reassign the height as one new node is added
    
    return root;
}