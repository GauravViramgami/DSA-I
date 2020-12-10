#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

void insertHeap (long long int *heap, long long int num, int len);
void updateHeap (long long int *heap, long long int index, long long int l);
void swap (long long int *a, long long int *b);

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    long long int n, d, k;
    scanf("%lld %lld %lld", &n, &d, &k);
    long long int heap[n];
    for (long long int i = 0; i < n; i++) {
        long long int num;
        scanf("%lld", &num);
        insertHeap(heap, num, i); //Insert heap
    }
    long long int count = 0;
    while (d > 0 && count < k+1) {
        d -= heap[0]; //Take max of heap
        count++; //Increase count
        heap[0] = floor(heap[0]/2); //Update the power of club
        updateHeap(heap, 0, n); //Update the heap
    }
    if (count <= k) {
        printf("%lld", count);
    } else {
        printf("-1"); //If count is more than k
    }
    
    return 0;
}

void swap (long long int *a, long long int *b) { //Swaping
    long long int temp = *a;
    *a = *b;
    *b = temp;
}

void insertHeap (long long int *heap, long long int num, int len) { //Insert heap
    heap[len] = num;
    long long int child_index = len; //Child index
    long long int parent_index = floor((len-1)/2); //Parent index
    while (parent_index >= 0 && heap[parent_index] < heap[child_index]) { //Swap till heap law violets
        swap(&heap[parent_index], &heap[child_index]);
        child_index = parent_index;
        parent_index = floor((child_index - 1)/2);
    }
}

void updateHeap (long long int *heap, long long int index, long long int l) { //Update heap
    long long int parent_index = index; //Parent index
    long long int lchild_index = 2*index + 1; //left child index
    long long int rchild_index = 2*index + 2; //right child index
    
    while (lchild_index < l || rchild_index < l) { //Till one of the child is last child
        if (rchild_index >= l) { //If there is only one child in last index
            if (heap[parent_index] < heap[lchild_index]) { //If heap rule violets than swap 
                swap(&heap[parent_index], &heap[lchild_index]);
            }
            break; //break since last child
        } else {
            long long int max_index = (heap[lchild_index] > heap[rchild_index])?lchild_index:rchild_index; //Max value between left and right childs
            if (heap[parent_index] < heap[max_index]) { //If geap rule violets than swap
                swap(&heap[parent_index], &heap[max_index]);
                parent_index = max_index;
                lchild_index = 2*parent_index + 1;
                rchild_index = 2*parent_index + 2;
            } else {
                break; //Else break since it is in correct place
            }
        }
    }
}