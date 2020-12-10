#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

#define ALPHABETSIZE 26 //ALPHABET Size

int charIndex (char c) { //Character index
    return (int)c - 97;
}

int count = 0; //Count for Suffixes

struct node {
    struct node *children[ALPHABETSIZE];
    struct node *parent;
    char c;
    bool isend;    
};

struct node *newNode (char c);
struct node *insert (struct node *root, char *word);
void numberOfSuffix (struct node *root);

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    char string[1200]; //Input string
    
    scanf("%s", string);
    
    int len = strlen(string); //Length of string
    
    struct node *root = newNode('\0'); //Initialize node as empty
    
    for (int i = 0; i < len; i++) {
        for (int j = i; j < len; j++) {
            char word[1200] = {'\0'}; //A Suffix
            strncpy(word, &(string[i]), j-i+1); //Store the suffix in word
            root = insert(root, word); //Insert it in the trie
        }
    }
    
    numberOfSuffix(root); //Count number of Suffixes
    printf("%d", count); //Print number of suffixes
    return 0;
}

struct node *newNode (char c) { 
    struct node *p = (struct node *)malloc(sizeof(struct node)); //Allocate space
    p->parent = NULL;
    p->isend = false;
    p->c = c;
    
    for (int i = 0; i < ALPHABETSIZE; i++) {
        p->children[i] = NULL;
    }
    return p;
}

struct node *insert (struct node *root, char *word) {
    int len = strlen(word); //Length of the word
    struct node *curr = root;
    
    for (int i = 0; i < len; i++) {
        int j = charIndex(word[i]); //Character index
        
        if (curr->children[j]) {
            curr = curr->children[j]; //If it is there then go to next character
        } else {
            struct node *p = newNode(word[i]); //Else create a new node for that character
            curr->children[j] = p;
            p->parent = curr;
            curr = curr->children[j];
        }
    }
    
    curr->isend = true; //End of the suffix
    
    return root;
}

void numberOfSuffix (struct node *root) {
    if (root == NULL) { //If NULL then return
        return;
    } else {
        if (root->isend) { //If it is end of some suffix then increment count
            count ++;
        }
        for (int i = 0; i < ALPHABETSIZE; i++) { //Go to its children
            if (root->children[i]) {
                numberOfSuffix(root->children[i]);
            }
        }
    }
}