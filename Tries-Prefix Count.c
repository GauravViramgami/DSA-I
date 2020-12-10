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
    int prefixes;  
};

struct node *newNode (char c);
struct node *insert (struct node *root, char *word);
struct node *prefixNode (struct node *root, char *word);
void numberOfEndNodes (struct node *root);

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n, count;
    scanf("%d", &n);
    
    struct node *root = newNode('\0');
    
    while (n--) {
        char operation[4] = {'\0'}; //Add or Find
        char word[21] = {'\0'}; //Word to add or find
        scanf("%s", operation);
        scanf("%s", word);
        if (operation[0] == 'a') {
            root = insert(root, word); //Insert if operstion is Add
        } else {
            struct node *endNode = prefixNode(root, word); //Else find the last node of the word
            count = (endNode)?endNode->prefixes:0; //prefixes == Number of words whose prefix is the given word
            printf("%d\n", count);
        }
    }
    return 0;
}

struct node *newNode (char c) {
    struct node *p = (struct node *)malloc(sizeof(struct node)); //Allocate space
    p->parent = NULL;
    p->c = c;
    p->isend = false;
    p->prefixes = 0; //Initialize prefixes as 0
    
    for (int i = 0; i < ALPHABETSIZE; i++) {
        p->children[i] = NULL;
    }
    
    return p;
}

struct node *insert (struct node *root, char *word) {
    int len = strlen(word);
    struct node *curr = root;
    
    for (int i = 0; i < len; i++) {
        int j = charIndex(word[i]);
        
        if (curr->children[j]) {
            curr = curr->children[j];
            curr->prefixes ++; //Increment prefixes of each character which is coming into the new inserted word
        } else {
            struct node *p = newNode(word[i]);
            curr->children[j] = p;
            p->parent = curr;
            curr = curr->children[j];
            curr->prefixes ++; //Increment prefixes of each character which is coming into the new inserted word
        }
    }
    
    curr->isend = true; //End of the word
    
    return root;
}

struct node *prefixNode (struct node *root, char *word) {
    if (root == NULL) {
        return NULL;
    } else {
        int len = strlen(word);
        struct node *curr = root;
        for (int i = 0; i < len; i++) { //Go till the end of the word
            int j = charIndex(word[i]);
            
            if (curr->children[j]) {
                curr = curr->children[j];
            } else {
                return NULL; //Retirn null if any character is missing in the trie => Word in not in the trie
            }
        }
        return curr; //Else return the last node of the word
    }
}