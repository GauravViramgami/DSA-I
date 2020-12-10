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

typedef struct heapNode {
  int value;
  int distance;
} heapNode;

typedef struct heap {
  int size;
  int totalVertex;
  int *position;
  struct heapNode **heapArray;
} heap;

Graph *createGraph (int n);
void addEdge (Graph *G, int u, int v, int weight);
void shortestPath (Graph *G, int u);

heapNode *newHeapNode (int value, int distance);
heap *createHeap (int totalVertex);
void swapHeap (heapNode **node1, heapNode **node2);
void updateHeap (heap *heap, int parentIndex);
heapNode *deleteMin (heap *heap);
void updateDistenceInHeap (heap *heap, int value, int distance);

void Dijkstra (Graph *G, int u);

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    Graph *G = createGraph(7);
    addEdge(G, 0, 1, 10);
    addEdge(G, 0, 2, 80);
    addEdge(G, 1, 2, 6);
    addEdge(G, 2, 3, 70);
    addEdge(G, 1, 4, 20);
    addEdge(G, 4, 5, 50);
    addEdge(G, 5, 6, 5);
    addEdge(G, 4, 6, 10);

    Dijkstra(G, 0);

    return 0;
}

heapNode *newHeapNode (int value, int distance) {
  heapNode *p = (heapNode *)malloc(sizeof(heapNode));
  p->value = value;
  p->distance = distance;
  
  return p;
}

heap *createHeap (int totalVertex) {
  heap *p = (heap *)malloc(sizeof(heap));
  p->size = 0;
  p->totalVertex = totalVertex;
  p->position = (int *)malloc(totalVertex*sizeof(int));
  p->heapArray = (heapNode **)malloc(totalVertex*sizeof(heapNode *));

  return p; 
}

void swapHeap (heapNode **node1, heapNode **node2) {
  heapNode *temp = *node1;
  *node1 = *node2;
  *node2 = temp;
}

void updateHeap (heap *heap, int parentIndex) {
  int smallerNodeIndex = parentIndex;
  int leftChildIndex = 2*parentIndex + 1;
  int rightChildIndex = 2*parentIndex + 2;

  if (leftChildIndex < heap->size && heap->heapArray[leftChildIndex]->distance < heap->heapArray[smallerNodeIndex]->distance) {
    smallerNodeIndex = leftChildIndex;
  }

  if (rightChildIndex < heap->size && heap->heapArray[rightChildIndex]->distance < heap->heapArray[smallerNodeIndex]->distance) {
    smallerNodeIndex = rightChildIndex;
  }

  if (smallerNodeIndex != parentIndex) {
    heapNode *smaller = heap->heapArray[smallerNodeIndex];
    heapNode *toSwapWith = heap->heapArray[parentIndex];

    heap->position[smaller->value] = parentIndex;
    heap->position[toSwapWith->value] = smallerNodeIndex;

    swapHeap(&heap->heapArray[smallerNodeIndex], &heap->heapArray[parentIndex]);

    updateHeap(heap, smallerNodeIndex);
  }
}

heapNode *deleteMin (heap *heap) {
  if (heap->size == 0) {
    return NULL;
  }

  heapNode *minimum = heap->heapArray[0];
  heapNode *lastNode = heap->heapArray[heap->size - 1];

  heap->heapArray[0] = lastNode;

  heap->position[minimum->value] = heap->size - 1;
  heap->position[lastNode->value] = 0;

  heap->size --;

  updateHeap(heap, 0);

  return minimum;
}

void updateDistenceInHeap (heap *heap, int value, int distance) {
  int index = heap->position[value];

  heap->heapArray[index]->distance = distance;

  while (index > 0 && heap->heapArray[index]->distance < heap->heapArray[(index - 1)/2]->distance) {
    heap->position[heap->heapArray[index]->value] = (index - 1)/2;
    heap->position[heap->heapArray[(index - 1)/2]->value] = index;

    swapHeap(&heap->heapArray[index], &heap->heapArray[(index - 1)/2]);

    index = (index - 1)/2; 
  }
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
    
    Node* temp2 = (Node *)malloc(sizeof(Node));
    temp2->value = u;
    temp2->weight = weight;
    temp2->next = G->Adj[v];
    G->Adj[v] = temp2; //Adding v - u
    G->m ++; //Incrementing number of edges
}

void Dijkstra (Graph *G, int u) {
  int n = G->n;
  int distance[n];

  heap *heap = createHeap(n);

  for (int i = 0; i < n; i++) {
    distance[i] = INT_MAX;
    heap->heapArray[i] = newHeapNode(i, distance[i]);
    heap->position[i] = i;
  }

  distance[u] = 0;
  updateDistenceInHeap(heap, u, distance[u]);

  heap->size = n;

  while (heap->size > 0) {
    heapNode *minimum  = deleteMin(heap);
    int value = minimum->value;
    printf("%d ", value);

    Node *temp = G->Adj[value];

    while (temp != NULL) {
      if (heap->position[temp->value] < heap->size && distance[temp->value] > distance[value] + temp->weight) {
        distance[temp->value] = distance[value] + temp->weight;
        
        updateDistenceInHeap(heap, temp->value, distance[temp->value]);
      }

      temp = temp->next;
    }
  }
}
