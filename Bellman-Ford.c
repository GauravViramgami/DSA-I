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

Graph *createGraph (int n);
void addEdge (Graph *G, int u, int v, int weight);

void bellmanFord (Graph *G, int u);

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

    bellmanFord(G, 0);

    return 0;
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

void bellmanFord (Graph *G, int u) {
  int n = G->n;
  int distance[n];

  for (int i = 0; i < n; i++) {
    distance[i] = INT_MAX;
  }

  distance[u] = 0;

  for (int i = 0; i < n-1; i++) {
    for (int j = 0; j < n; j++) {
      Node *temp = G->Adj[j];
      //printf("distance %d: %d\n", j, distance[j]);
      while (temp != NULL) {
        if (distance[j] != INT_MAX && distance[temp->value] > distance[j] + temp->weight) {
          distance[temp->value] = distance[j] + temp->weight;
        }
        temp = temp->next;
      }
    }
  }

  for (int i = 0; i < n; i++) {
    printf("%d: %d\n", i, distance[i]);
  }
}