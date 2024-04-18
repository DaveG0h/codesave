//Graph Connection (Directed graph)

#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode
{
    int vertex;
	struct _listnode *next;
} ListNode;
typedef ListNode StackNode;

typedef struct _graph{
    int V;
    int E;
    int *visited; //store the visited vertices
    int **matrix;
}Graph;

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} Stack;

// You should not change the prototypes of these functions
//////STACK///////////////////////////////////////////
void push(Stack *sPtr, int vertex);
int pop(Stack *sPtr);
int peek(Stack s);
int isEmptyStack(Stack s);
void removeAllItemsFromStack(Stack *sPtr);
////GRAPH////////////////////////////////////////////
void printGraphMatrix(Graph );
////////////////////////////////////////////

int Connected (Graph);

int main()
{
    Graph g;
    int i,j;
    

    printf("Enter the number of vertices:\n");
    scanf("%d",&g.V);

    g.E = 0;
    g.matrix = (int **)malloc(g.V*sizeof(int *)); //allocate MEM for each column
    for(i=0;i<g.V;i++)
        g.matrix[i] = (int *)malloc(g.V*sizeof(int)); //allocate MEM for each row

    for(i=0;i<g.V;i++)
       for(j=0;j<g.V;j++)
           g.matrix[i][j] = 0; //assign 0 to each value in matrix
	
	g.visited = (int *) malloc(sizeof(int)*g.V);
    for(i=0;i<g.V;i++) g.visited[i] = 0; //assign visited to 0 
    
    
    int V1, V2;
    printf("Enter a directed edge: (press a to stop)\n");
    while(scanf("%d %d",&V1,&V2)==2)
    {
        if(V1>0 && V1<=g.V && V2>0 && V2<=g.V)
        {
            g.matrix[V1-1][V2-1] = 1;
            g.E++;
        }
        else
            break;
        printf("Enter a directed edge: (press a to stop)\n");
    }
    scanf("%*c");
    
    
    int res = Connected(g);
    if(res == 1)
        printf("The graph is strongly connected.\n");
    else
        printf("The graph is not strongly connected.\n");

    return 0;
}

int Connected (Graph g) 
{ 
    //write your code here 
    Stack *s = malloc(sizeof(Stack)); 
    s->head = NULL; 
    s->size = 0; 
 
    int root = 0; 
 
    for (int i=0; i<g.V; i++) { 
        for (int j=0; j<g.V; j++) { 
            if (g.matrix[i][j]) { //if vertice exist
                root = i+1; //value = index+1
                goto check_root; 
            } 
        } 
    } 
 
    check_root: 
    if (!root) { //no vertices --> return 0
        removeAllItemsFromStack(s); 
        free(s); 
        return 0; 
    } 
 
    //DFS
    push(s, root); 
    g.visited[root-1] = 1; 
    while (!isEmptyStack(*s)) { 
        int current = peek(*s); 
        pop(s);     
 
        for (int i=0; i<g.V; i++) { 
            if (g.matrix[current-1][i]) { 
                if (!g.visited[i]) { 
                    push(s, i+1); 
                    g.visited[i] = 1; 
                } 
            } 
        } 
    } 
    
    //check if any vertices that is not visited
    for (int i=0; i<g.V; i++) { 
        if (!g.visited[i]) { 
            removeAllItemsFromStack(s); 
            free(s); 
            return 0; 
        } 
        g.visited[i] = 0; 
    } 
 
    removeAllItemsFromStack(s); 
    push(s, root); 
    g.visited[root-1] = 1; 
    while (!isEmptyStack(*s)) { 
        int current = peek(*s); 
        pop(s); 
 
        for (int i=0; i<g.V; i++) { 
            if (g.matrix[i][current-1]) { 
                if (!g.visited[i]) { 
                    push(s, i+1); 
                    g.visited[i] = 1; 
                } 
            } 
        } 
    } 
 
    for (int i=0; i<g.V; i++) { 
        if (!g.visited[i]) { 
            removeAllItemsFromStack(s); 
            free(s); 
            return 0; 
        } 
    } 
 
    removeAllItemsFromStack(s); 
    free(s); 
    return 1; 
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

void push(Stack *sPtr, int vertex)
{
	StackNode *newNode;
    newNode= malloc(sizeof(StackNode));
    newNode->vertex = vertex;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr)
{
    if(sPtr==NULL || sPtr->head==NULL){
        return 0;
    }
    else{
       StackNode *temp = sPtr->head;
       sPtr->head = sPtr->head->next;
       free(temp);
       sPtr->size--;
       return 1;
    }
}

int isEmptyStack(Stack s)
{
     if(s.size==0) return 1;
     else return 0;
}

int peek(Stack s){
    return s.head->vertex;
}

void removeAllItemsFromStack(Stack *sPtr)
{
	while(pop(sPtr));
}
