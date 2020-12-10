#include <stdio.h>
#include <math.h>

int isHeap(int *arr, int N){
  //Write your logic here.
  int parent, childL, childR; //Define parent, left child and right child
  int i = 0;
  int isHeap = 1; //Initially assume it is a max heap
  while (i < N) {
      parent = arr[i]; //Parent
      if (2*i + 1 < N) { //If it has a left child
          childL = arr[2*i + 1];
          if (parent < childL) { //If heap rule violets return 0
              isHeap = 0;
              break;
          }
      }
      if (2*i + 2 < N) { //If it has a right child
          childR = arr[2*i + 2];
          if (parent < childR) { //If heap rule violets return 0
              isHeap = 0;
              break;
          }
      }
      i++; 
  }
  return isHeap;
}

int main(void) {
  int N;
    
  scanf("%d", &N);
  int arr[N];
  for(int i =0; i<N; i++){
    scanf("%d", &arr[i]);
  }
    
  if(isHeap(arr,N)){
    printf("YES");
  } else {
    printf("NO");
  }
    
  return 0;
}