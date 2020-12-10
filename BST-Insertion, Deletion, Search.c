#include <stdio.h>
#include <stdlib.h>

struct node{
  int data; 
  struct node *right_child;
  struct node *left_child;
};

// Function to create a new node with data x.
struct node* new_node(int x){
  struct node *p;
  p = malloc(sizeof(struct node));
  p->data = x;
  p->left_child = NULL;
  p->right_child = NULL;

  return p;
}

// Function to insert a node
struct node* insert(struct node *root, int x){
  if(root == NULL)
    return new_node(x);
  else if(x > root->data)
    root->right_child = insert(root->right_child,x);
  else
    root->left_child = insert(root->left_child,x);
  return root; 
}


struct node* search(struct node *root, int x)
{
    if(root==NULL || root->data==x) //if root->data is x then the element is found
        return root;
    else if(x>root->data) // x is greater, so we will search the right subtree
        return search(root->right_child, x);
    else //x is smaller than the data, so we will search the left subtree
        return search(root->left_child,x);
}


void inorder(struct node *root){
  if(root != NULL){
    inorder(root->left_child);
    printf(" %d ", root->data);
    inorder(root->right_child);
  }
}


//function to find the minimum value in a node
struct node* find_minimum(struct node *root)
{
    if(root == NULL)
        return NULL;
    else if(root->left_child != NULL) // node with minimum value will have no left child
        return find_minimum(root->left_child); // left most element will be minimum
    return root;
}


// funnction to delete a node
struct node* delete(struct node *root, int x)
{
    //searching for the item to be deleted
    if(root==NULL)
        return NULL;
    if (x>root->data)
        root->right_child = delete(root->right_child, x);
    else if(x<root->data)
        root->left_child = delete(root->left_child, x);
    else
    {
        //No Children
        if(root->left_child==NULL && root->right_child==NULL)
        {
            free(root);
            return NULL;
        }

        //One Child
        else if(root->left_child==NULL || root->right_child==NULL)
        {
            struct node *temp;
            if(root->left_child==NULL)
                temp = root->right_child;
            else
                temp = root->left_child;
            free(root);
            return temp;
        }

        //Two Children
        else
        {
            struct node *temp = find_minimum(root->right_child);
            root->data = temp->data;
            root->right_child = delete(root->right_child, temp->data);
        }
    }
    return root;
}


int main(){
  struct node *root;
  root = new_node(20);

  insert(root,5);
  insert(root,1);
  insert(root,15);
  insert(root,9);
  insert(root,7);
  insert(root,12);
  insert(root,30);
  insert(root,25);
  insert(root,40);
  insert(root, 45);
  insert(root, 42);

  inorder(root);
  printf("\n");
  
  delete(root,45);
  inorder(root);
  printf("\n");
  
  delete(root,20);
  inorder(root);
  printf("\n");
  
}