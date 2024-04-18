///////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h> // Include limits.h for INT_MIN

#define SIZE 1000 // The limit of expression length
/////////////////////////////////////////////////

typedef struct _listnode{
   char item;
   struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int size;
   ListNode *head;
 } LinkedList;

////////////////////////////////// stack  ///////////////////////

typedef struct stack{
	LinkedList ll;
} Stack;

//////////////////////// function prototypes /////////////////////////////

void infixtoPrefix(char* infix, char* prefix); // You should not change the prototypes of these functions

int precedence(char op); // You may use this utility function or rewrite your own precedence () function

////////////////////////////////////////////////////////////////////////////
void push(Stack *s, char item);
int pop(Stack *s);
int peek(Stack *s);
int isEmptyStack(Stack *s);

////////////////////////////////////////////////////////////////////////////
void printList(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, char item);
int removeNode(LinkedList *ll, int index);
void removeAllItems(LinkedList *ll);

////////////////////////////////////////////////////////////////////////////

int main()
{
    char infix[SIZE];
    char prefix[SIZE];

    printf("Enter an infix expression:\n");
    scanf("%[^\n]%*c",infix);

    infixtoPrefix(infix, prefix);
    printf("The prefix expression is \n");
    printf("%s\n",prefix);
    return 0;
}

void infixtoPrefix(char* infix, char* prefix) 
{
   //add your code here
   int size=0;
   int i=0, k=0, temp;
   Stack s1;
	s1.ll.head = NULL;
	s1.ll.size = 0;
   //reverse the infix array
	for(i=0; infix[i] != '\0'; i++)
	{
		if(infix[i] == '(')
		{
			push(&s1, ')');
		}
		else if(infix[i] == ')')
		{
			push(&s1, '(');
		}
		else
		{
			push(&s1, infix[i]);
		}
	}
	//Print the contents of the stack s1
    //printf("Contents of the stack s1:\n");
    //printList(&(s1.ll));
	i=0; //set i back to 0
	//clear stack and pop back into infix for reversed expression
	while(!isEmptyStack(&s1))
	{
		temp = pop(&s1);
		infix[i] = temp;
		i++;
	}
	infix[i] = '\0';
	//printf("The new infix expression is \n");
    //printf("%s\n",infix);

	i=0; //reiterate i to be back to 0;
	//newinfix to postfix ---------------------------------------------------
	while(infix[i] != '\0')
	{
		//catch alphabets and put it into the postfix array directly
		if(isalnum(infix[i]) != 0)
		{
			prefix[k] = infix[i];  
			k++; //iterate next for postfix array
		}
		//consider open brackets, and direct push 
		else if(infix[i] == '(')
		{
			push(&s1, infix[i]);
		}
		//encountering close brackets, pop till open bracket in stack
		else if(infix[i] == ')')
		{
			while(peek(&s1) != '(') //stop at the '(' itself
			{
				temp = pop(&s1);
				prefix[k] = temp;
				//printf("the character added to postfix is %c\n", temp);
				k++;
			}
			temp = pop(&s1); //pop out the '(' itself
		}
		//empty stack or top of stack is '(' or infix > stack, just push
		else if(isEmptyStack(&s1) || peek(&s1) == '(' || precedence(infix[i]) >= precedence(peek(&s1)))
		{
			push(&s1, infix[i]);
			//printf("infix pushed is %c\n", infix[i]);
		}
		//if infix <= stack
		else if(precedence(infix[i]) < precedence(peek(&s1)))
		{
			//remove when stack is not empty OR remove when top of stack is not '(' remove when precedence of infix is still lesser than stack 
			while(!isEmptyStack(&s1) && peek(&s1) != '(' && precedence(infix[i]) < precedence(peek(&s1)))
			{
				temp = pop(&s1);
				prefix[k] = temp;
				k++;	
			}
			push(&s1, infix[i]);
		}
		i++;
		// Print the contents of the stack s1
		//printf("Contents of the stack s1:\n");
		//printList(&(s1.ll));
   }
	while(!isEmptyStack(&s1)) //when array iteration finishes, pop out all operation left in stack
   {
    temp = pop(&s1);
    prefix[k] = temp;
    k++;
   }

    prefix[k] = '\0'; //null character addition
	
	
	//reverse the prefix by pushing into stack
	for(k=0; prefix[k] != '\0'; k++)
	{
		push(&s1, prefix[k]);
	}

	for(k=0; !isEmptyStack(&s1); k++)
	{
		temp = pop(&s1);
		prefix[k] = temp;
	}

	prefix[k] = '\0';
}


int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}
/////////////////////////////////////////////////////////////////////

void push(Stack *s, char item){
   insertNode(&(s->ll), 0, item);
}

int pop(Stack *s){
   char item;
   if(!isEmptyStack(s)){
    item = ((s->ll).head)->item;
    removeNode(&(s->ll), 0);
    return item;
   }
    return INT_MIN;
}

int peek(Stack *s){
   return ((s->ll).head)->item;
}

int isEmptyStack(Stack *s){
   if ((s->ll).size == 0)
      return 1;
   return 0;
}

////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%c ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}

ListNode * findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, char value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
