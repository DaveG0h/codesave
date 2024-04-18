////////////////////////////////////////////////////////////

//#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

////////////////////////////////////////////////////////////

typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode;

//////////////////////////////////////////////////////

int searchList(ListNode *head, int value);

//////////////////////////////////////////////////////

void main()
{
	ListNode *head, *p, *temp;
	int n;


	head=NULL;
	p=NULL;		// pointing to the last node in the list
	printf("Enter a list of numbers, terminated by the value -1:\n");

 ////////////////////////////////////////////////////////////////////

 // Question 2
 //Write your program code here
    scanf("%d", &n);
    while (n != -1)
    {
        if (head == NULL)
        {
            head = (ListNode *)malloc(sizeof(ListNode));
            p = head;
        }
        else
        {
            p->next=(ListNode *)malloc(sizeof(ListNode));
            p=p->next;
        }
        p->item=n;
        scanf("%d", &n);
    }
    p->next=NULL;
    printf("Current list: ");
    temp = head;
    while(temp!= NULL)
    {
        printf("%d ", temp->item);
        temp = temp->next;
    }
//////////////////////////////////////////////////////////////////////

//search for a value in the list. Q3

	printf("Enter value to search for:");
	scanf("%d", &n);
	searchList(head,n);
    

/////////////////////////////////////////////////////////

    //free up memory for question 4
	//this part is wrong. It will cause problems.
/*	p = head;
	while (p!= NULL) {
		free(p);  --> free p but then you assign p=p->next (unassignable since p lost its memory)
		p=p->next; 
	}
*/


    // Question 4
	//rewrite the free up using temporary pointer temp.
    p = head;
    while (p != NULL)
    {
        temp = p->next;
        free(p);
        p=temp;
    }
/////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////

int searchList(ListNode *head, int value)
{
    ListNode *temp;
    int i;
////////////////////////////////////////////////////////////////////

 // Question 3
 //Write your program code here
    temp = head;
    for (i=0; temp->item != value; i++)
    {
        temp = temp->next;
    }
    printf("Value %d found at index %d", value, i);
//////////////////////////////////////////////////////////////////////
}