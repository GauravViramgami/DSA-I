#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int T; //Test cases
    scanf("%d", &T);
    while (T--) {
        int N; //len
        scanf("%d", &N);
        int A[N]; //Input array
        int f[100001]; //frequency - ith index has frequency of i in input array
        int frequency[N][2]; //2d array of length Nx2 containing input elements along with its frequency
        for (int i = 0; i < 100001; i++) { //Initialize f with zeros
            f[i] = 0;
        }
        for (int i = 0; i < N; i++) {
            scanf("%d", &A[i]); //Input array
            f[A[i]]++; //Increament frequency of A[i]th element in f
        }
        for (int i = 0; i < N; i++) { //2d array (element, frequency)
            frequency[i][0] = A[i];
            frequency[i][1] = f[A[i]];
        }
        
        int h[N]; //height = right nearest greater element
        int stack[N][2]; //2d stack (element, frequency)
        int i_stack = -1; //stack index
        for (int i = N-1; i >=0; i--) {
            if (i_stack < 0) { //If stack is empty then append and its height will be -1
                i_stack++;
                stack[i_stack][0] = frequency[i][0];
                stack[i_stack][1] = frequency[i][1];
                h[i] = -1;
            } else {
                while (i_stack >=0 && frequency[i][1] >= stack[i_stack][1]) { //Go while elements in stack are less than or equal to the current element and keep deleting those elements from the stack
                    stack[i_stack][0] = '\0';
                    stack[i_stack][1] = '\0';
                    i_stack--;
                }
                if (i_stack < 0) { //If stack is empty than element's height = -1 and append it to the stack
                    h[i] = -1;
                    i_stack++;
                    stack[i_stack][0] = frequency[i][0];
                    stack[i_stack][1] = frequency[i][1];
                } else { //Else height is the i_stack th element of the stack 
                    h[i] = stack[i_stack][0];
                    i_stack++;
                    stack[i_stack][0] = frequency[i][0]; //Append to the stack
                    stack[i_stack][1] = frequency[i][1];
                }
            }
        }
        
        for (int i = 0; i < N; i++) { //Print each height
            printf("%d ", h[i]); 
        }
        printf("\n");
    }
    return 0;
}