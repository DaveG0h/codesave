// Shortest Distances
#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode
{
    int vertex;
	struct _listnode *next;
} ListNode;

typedef struct _graph{
    int V;
    int E;
    int *visited;
    int **matrix;
}Graph;

typedef ListNode QueueNode;

typedef struct _queue{
   int size;
   QueueNode *head;
   QueueNode *tail;
} Queue;

int SD (Graph G, int v, int w);

void printGraphMatrix(Graph );

// You should not change the prototypes of these functions
void enqueue(Queue *qPtr, int item);
int dequeue(Queue *qPtr);
int getFront(Queue q);
int isEmptyQueue(Queue q);
void removeAllItemsFromQueue(Queue *qPtr);

int main()
{
    Graph g;
    int i,j;

    printf("Enter the number of vertices:\n");
    scanf("%d",&g.V);

    g.E = 0;
    g.matrix = (int **)malloc(g.V*sizeof(int *)); //memory for each row of matrix
    for(i=0;i<g.V;i++)
        g.matrix[i] = (int *)malloc(g.V*sizeof(int)); //memory for each column of matrix by indexing row

    for(i=0;i<g.V;i++)
       for(j=0;j<g.V;j++)
           g.matrix[i][j] = 0; //assigning 0 to each box in matrix

    g.visited = (int *) malloc(sizeof(int)*g.V); //memory for visited list (seperated from matrix)
    for(i=0;i<g.V;i++) g.visited[i] = 0; //assigning 0 to row of visited list

    int V1, V2;
    printf("Enter two vertices which are adjacent to each other:\n");
    while(scanf("%d %d",&V1,&V2)==2) //==2 means it successfully read 2 integers
    {
        if(V1>0 && V1<=g.V && V2>0 && V2<=g.V)
        { //V1-1 and V2-1 because index=value-1, value of vertices is smaller than no. of vertices
            g.matrix[V1-1][V2-1] = 1;
            g.matrix[V2-1][V1-1] = 1;
            g.E++;
        }
        else
            break;
        printf("Enter two vertices which are adjacent to each other: (press a to stop)\n");
    }
    scanf("%*c");
    // printGraphMatrix(g);
    
    printf("Enter two vertices for finding their shortest distance: (press a to stop)\n");
    scanf("%d %d", &i, &j);

    int d = SD(g,i,j);
    if(d==-1)
        printf("%d and %d are unconnected.\n",i,j);
    else
        printf("The shortest distance is %d\n",d);
    return 0;
}

int SD(Graph g, int v, int z){ //BFS runs through at neighbouring node before moving on
    //index on matrix = value-1;
    // Write your code here
    //take the root, check the row of matrix, get all value that is =1 on matrix, then enqueue,
    //dequeue and check the row of that node's matrix, enequeue all value that is =1 and not visited
    Queue q;
    q.head = q.tail = NULL;
    q.size = 0;

    int *distance = (int *)malloc(sizeof(int) * g.V);
    for (int i = 0; i < g.V; i++) {
        distance[i] = -1;
    }

    //root = v
    g.visited[v-1] = 1;
    distance[v-1] = 0;
    enqueue(&q, v);

    while (!isEmptyQueue(q)) {
        int currentVertex = dequeue(&q);
        //row enqueue
        for (int i = 0; i < g.V; i++) {
            //check for connection + unvisited
            if (g.matrix[currentVertex - 1][i] == 1 && !g.visited[i]) {
                g.visited[i] = 1;
                distance[i] = distance[currentVertex - 1] + 1;
                enqueue(&q, i + 1); 

                if (i + 1 == z) {
                    int result = distance[i];
                    free(distance);
                    removeAllItemsFromQueue(&q);
                    return result;
                }
            }
        }
    }
    int result = distance[z - 1];
    free(distance);
    return result;
}

void printGraphMatrix(Graph g)
{
    int i,j;

    for(i=0;i<g.V;i++){
        for(j=0;j<g.V;j++)
            printf("%d\t",g.matrix[i][j]);
        printf("\n");
    }

}


void enqueue(Queue *qPtr, int item) {
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    if(newNode==NULL) exit(0);

    newNode->vertex = item;
    newNode->next = NULL;

    if(isEmptyQueue(*qPtr))
        qPtr->head=newNode;
    else
        qPtr->tail->next = newNode;

    qPtr->tail = newNode;
    qPtr->size++;
}

int dequeue(Queue *qPtr) {
    if(qPtr==NULL || qPtr->head==NULL){ //Queue is empty or NULL pointer
        return 0;
    }
    else{
       int headValue = qPtr->head->vertex;
       QueueNode *temp = qPtr->head;
       qPtr->head = qPtr->head->next;
       if(qPtr->head == NULL) //Queue is emptied
           qPtr->tail = NULL;

       free(temp);
       qPtr->size--;
       return headValue;
    }
}

int getFront(Queue q){
    return q.head->vertex;
}

int isEmptyQueue(Queue q) {
    if(q.size==0) return 1;
    else return 0;
}

void removeAllItemsFromQueue(Queue *qPtr)
{
	while(dequeue(qPtr));
}