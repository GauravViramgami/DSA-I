#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n; //Total number of Vertex
    
    scanf("%d", &n);
    
    int arr[n-1][n-1]; //2D Array: arr[i] is an array of children whose parent is i
    int noOfChildren[n-1]; //noOfChildren[i] is the number of children of the parent i
    int parent; //To store the input parents
    
    for (int i = 0; i < n; i++) { //Initialize number of children as 0
        noOfChildren[i] = 0;
    }
    
    for (int i = 1; i < n; i++) { //Add children to its respective parent's array in arr and increment count of children in noOfChildren array
        scanf("%d", &parent);
        arr[parent-1][noOfChildren[parent-1]] = i;
        noOfChildren[parent-1] ++;
    }
    
    int spruce = 1; //Suppose it is a spruce
    for (int i = 0; i < n; i++) { //Iterate through all parents
        int children = noOfChildren[i];
        if (children != 0) { //If number of children is zero then leaf node - so no need to check
            int leafChildren = 0;
            int index = 0;
            while (index < children && leafChildren < 3) { //Else iterate through its children 
                int nextChildren = arr[i][index];
                if (noOfChildren[nextChildren] == 0) { //If the children is leaf vertex then increment the leafChildren count
                    leafChildren ++;
                }
                index ++;
            }
            if (leafChildren < 3) { //It the parent does not have at least 3 children then the tree is not a spruce - break
                spruce = 0;
                break;
            }
        }
    }
    
    if (spruce == 1) { //If spruce then print "Yes" else print "No"
        printf("Yes");
    } else {
        printf("No");
    }
    
    return 0;
}