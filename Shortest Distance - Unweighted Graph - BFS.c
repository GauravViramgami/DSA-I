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
    int parent; //Parent to calculate distance
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

Graph *createGraph (int n);
void addEdge (Graph *G, int u, int v);

QNode *newNode (int k);
Queue *createQueue ();
void enQueue (Queue *Q, int key);
void deQueue (Queue *Q);

int bfs (Graph *G, int u);

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int t;
    scanf("%d", &t);
    
    while (t--) {
        int n, m;
        scanf("%d", &n);
        scanf("%d", &m);
        
        Graph *G = createGraph(n); //Create Graph
        
        while (m--) {
            int u, v;
            scanf("%d", &u);
            scanf("%d", &v);
            addEdge(G, u-1, v-1); //Add Edge
        }
        
        int count = bfs(G, 0);
        printf("%d\n", count); //Print shortest distance
    }
    return 0;
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

void deQueue (Queue *Q) { //Dequeue in the Queue
    if (Q->front == NULL) { //If queue is empty then retuen
        return;
    }
    
    QNode *p = Q->front;
    
    Q->front = Q->front->next; //Else assign front as the next of the front in the Queue
    
    if (Q->front == NULL) { //If queue becomes empty then assign rear as NULL
        Q->rear = NULL;
    }
    
    free(p); //Free the pointer
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
    temp1->parent = u;
    temp1->next = G->Adj[u];
    G->Adj[u] = temp1; //Adding u - v 
    
    Node* temp2 = (Node *)malloc(sizeof(Node));
    temp2->value = u;
    temp2->parent = v;
    temp2->next = G->Adj[v];
    G->Adj[v] = temp2; //Adding v - u
    G->m ++; //Incrementing number of edges
}

int bfs (Graph *G, int u) { //BFS
    
    Queue *Q = createQueue(); //Creating queue
    enQueue(Q, u); //Enque the source
    
    int n = G->n;
    int distance[n];
    distance[u] = 0; //Array to store distence from source
    
    if (u == n-1) { //If the source is equal to destination return 0
        return 0;
    }
    
    int visited[n];
    for (int i = 0; i < n; i++) {
        visited[i] = 0; //Initialize visited array as 0
    }
    
    visited[u] = 1; //Source is visited
    while (Q->front) { //While queue is not empty
        
        int v = Q->front->key;
        deQueue(Q); //Deque first element
        
        Node *temp = G->Adj[v]; //Go to its Adj List members
        while (temp) {
            if (visited[temp->value] == 0) { //If it is not visited vist it and enque
                enQueue(Q, temp->value);
                visited[temp->value] = 1;
                distance[temp->value] = distance[temp->parent] + 1; //Update its distance from the source
            }
            
            if (temp->value == n-1) { //If it is destination then retuen the distance
                return distance[n-1];
            }
            
            temp = temp->next;
        }
    }
    
    return distance[n-1]; //This retuen will not be called if there is a path from 1 to N (Which is assured in the question)
}