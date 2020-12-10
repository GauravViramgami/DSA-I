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
} Node;

typedef struct Graph { //Graph
    int n;
    int m;
    Node** Adj;  
} Graph;

typedef struct QNode { //Node of Queue
    int key;
    struct QNode *next;
} QNode;

typedef struct Queue { //Queue
    struct QNode *front, *rear;
} Queue;

int max (int a, int b);

Graph *createGraph (int n);
void addEdge (Graph *G, int u, int v);

QNode *newNode (int k);
Queue *createQueue ();
void enQueue (Queue *Q, int key);
int deQueue (Queue *Q);

void sortDAG (Graph *G);

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    Graph *G = createGraph(8);
    addEdge(G, 0, 2);
    addEdge(G, 0, 3);
    addEdge(G, 0, 4);
    addEdge(G, 1, 2);
    addEdge(G, 1, 7);
    addEdge(G, 2, 5);
    addEdge(G, 3, 5);
    addEdge(G, 3, 7);
    addEdge(G, 4, 7);
    addEdge(G, 5, 6);
    addEdge(G, 6, 7);
    sortDAG(G);
    
    return 0;
}

int max (int a, int b) {
  return (a > b)?a:b;
}

QNode *newNode (int key) { //Create newnode to add into Queue
    QNode *p = (QNode *)malloc(sizeof(QNode));
    p->key = key;
    p->next = NULL;
    return p;
}

Queue *createQueue () { //Create Queue
    Queue *Q = (Queue *)malloc(sizeof(Queue));
    Q->front = Q->rear = NULL;
    return Q;
}

void enQueue (Queue *Q, int key) { //Enqueue in the Queue
    QNode *p = newNode(key);
    
    if (Q->rear == NULL) {
        Q->front = Q->rear = p; //If queue is empty then add p as front and rear
        return;
    }
    
    Q->rear->next = p; //Else add as rear
    Q->rear = p;
}

int deQueue (Queue *Q) { //Dequeue in the Queue
    if (Q->front == NULL) { //If queue is empty then retuen
        return 0;
    }
    
    QNode *p = Q->front;
    int value = p->key;
    
    Q->front = Q->front->next; //Else assign front as the next of the front in the Queue
    
    if (Q->front == NULL) { //If queue becomes empty then assign rear as NULL
        Q->rear = NULL;
    }
    
    free(p); //Free the pointer
    return value;
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

void addEdge (Graph *G, int u, int v) { //Adding edge
    Node* temp1 = (Node *)malloc(sizeof(Node));
    temp1->value = v;
    temp1->next = G->Adj[u];
    G->Adj[u] = temp1; //Adding u - v 
    
    G->m ++; //Incrementing number of edges
}

void sortDAG (Graph *G) {
  int n = G->n;
  int inDegree[n], LPT[n];
  for (int i = 0; i < n; i++) {
    inDegree[i] = 0;
    LPT[i] = 0;
  }

  for (int i = 0; i < n; i++) {
    Node *temp = G->Adj[i];
    while (temp != NULL) {
      inDegree[temp->value] ++;
      temp = temp->next; 
    }
  }

  Queue *Q = createQueue();

  for (int i = 0; i < n; i++) {
    if (inDegree[i] == 0) {
      enQueue(Q, i);
      inDegree[i] = -1;
    }
  }
  
  while (Q->front != NULL) {
    int first = deQueue(Q);
    printf("%d ", first);
    Node *temp2 = G->Adj[first];
    while (temp2 != NULL) {
      inDegree[temp2->value] --;
      LPT[temp2->value] = max(LPT[temp2->value], 1 + LPT[first]);
      if (inDegree[temp2->value] == 0) {
        enQueue(Q, temp2->value);
        inDegree[temp2->value] = -1;
      }
      temp2 = temp2->next;
    }
  }

  printf("\n");
  for (int i = 0; i < n; i++) {
    printf("%d ", LPT[i]);
  }
}