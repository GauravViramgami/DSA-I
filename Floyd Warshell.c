#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

typedef struct Node { //Node of Adj List
    int value;
    struct Node* next;
    int weight;
} Node;

typedef struct Graph { //Graph
    int n;
    int m;
    Node** Adj;  
} Graph;

int min (int a, int b);

Graph *createGraph (int n);
void addEdge (Graph *G, int u, int v, int weight);

void floydWarshall (Graph *G);

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    Graph *G = createGraph(8);
    addEdge(G, 0, 1, 10);
    addEdge(G, 0, 7, 8);
    addEdge(G, 1, 5, 2);
    addEdge(G, 2, 1, 1);
    addEdge(G, 2, 3, 1);
    addEdge(G, 3, 4, 3);
    addEdge(G, 4, 5, -1);
    addEdge(G, 5, 2, -2);
    addEdge(G, 6, 1, -4);
    addEdge(G, 6, 5, -1);
    addEdge(G, 7, 6, 1);

    floydWarshall(G);

    return 0;
}

int min (int a, int b) {
  return (a < b)?a:b;
}

Graph *createGraph (int n) { //Create Graph
    Graph *G = (Graph *)malloc(sizeof(Graph));
    G->n = n; //Vertexes
    G->m = 0; //Edges
    G->Adj = (Node **)malloc(n*sizeof(Node *)); //Adj List
    for (int i = 0; i < n; i++) {
        G->Adj[i] = NULL; //NULL Adj List Nodes initially
    }
    
    return G;
}

void addEdge (Graph *G, int u, int v, int weight) { //Adding edge
    Node* temp1 = (Node *)malloc(sizeof(Node));
    temp1->value = v;
    temp1->weight = weight;
    temp1->next = G->Adj[u];
    G->Adj[u] = temp1; //Adding u - v 
    G->m ++; //Incrementing number of edges
}

void floydWarshall (Graph *G) {
  int n = G->n;
  int arr[n][n][n];

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      arr[i][j][0] = INT_MAX;
    }
  }

  for (int i = 0; i < n; i++) {
    Node *temp = G->Adj[i];
    while (temp != NULL) {
      arr[i][temp->value][0] = temp->weight;
      temp = temp->next;
    }
  }

  for (int k = 1; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (arr[i][k][k-1] == INT_MAX || arr[k][j][k-1] == INT_MAX) {
          arr[i][j][k] = arr[i][j][k-1];
        } else {
            arr[i][j][k] = min(arr[i][j][k-1], arr[i][k][k-1] + arr[k][j][k-1]);
        }
      }
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d ", arr[i][j][n-1]);
    }
    printf("\n");
  }
}