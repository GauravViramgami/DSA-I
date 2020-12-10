#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

#define ALPHABETSIZE 26 //ALPHABET size

int charIndex (char c) {
    return (int)c - 97; //Character Index
}

struct node {
    struct node *children[ALPHABETSIZE];
    struct node *parent;
    char c;
    bool isend;
    int suffix;  
};

struct node *newNode (char c);
struct node *insert (struct node *root, char* word, int suffix);
void dfs (struct node *root);

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    char string[1000]; //input string
    scanf("%s", string);
    
    struct node *root = newNode('\0');
    int len = strlen(string);
    
    for (int i = 0; i < len; i++) { //For all suffixes
        char word[1000] = {'\0'};
        strncpy(word, &(string[i]), len - i); //Copy the suffix in word
        root = insert(root, word, i); //Insert it in the trie, suffix index = i
    }
    
    dfs(root); //Do DFS
    
    return 0;
}

struct node *newNode (char c) {
    struct node *p = (struct node *)malloc(sizeof(struct node)); //Allocate space
    p->parent = NULL;
    p->c = c;
    p->isend = false;
    
    for (int i = 0; i < ALPHABETSIZE; i++) {
        p->children[i] = NULL;
    }
    
    return p;
}

struct node *insert (struct node *root, char* word, int suffix) { //Insert new word
    int len = strlen(word);
    struct node *curr = root;
    
    for (int i = 0; i < len; i++) {
        int j = charIndex(word[i]);
        
        if (curr->children[j]) {
            curr = curr->children[j];
        } else {
            struct node *p = newNode(word[i]); //Insert character if not there
            p->parent = curr;
            curr->children[j] = p;
            curr = curr->children[j];
        }
    }
    
    curr->isend = true;
    curr->suffix = suffix; //Give its suffix index
    
    return root;
}

void dfs (struct node *root) { //DFS
    if (root == NULL) { //If NULL then return
        return;
    } else {
        if (root->isend) { //If it is end of word then print its suffix index
            printf("%d ", root->suffix);
        }
        
        for (int i = 0; i < ALPHABETSIZE; i++) { //Do it for its all children
            if (root->children[i]) {
                dfs(root->children[i]);
            }
        }
    }
}