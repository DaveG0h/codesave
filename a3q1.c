//coalesced hashing
#include <stdio.h>
#include <stdlib.h>

#define TABLESIZE 37
#define PRIME     13

enum Marker {EMPTY,USED};

typedef struct _slot{
    int key;
    enum Marker indicator;
    int next;
} HashSlot;

int HashInsert(int key, HashSlot hashTable[]);
int HashFind(int key, HashSlot hashTable[]);

int hash(int key)
{
    return (key % TABLESIZE);
}

int main()
{
    int opt;
    int i;
    int key;
    int index;
    HashSlot hashTable[TABLESIZE];

    for(i=0;i<TABLESIZE;i++){
        hashTable[i].next = -1;
        hashTable[i].key = 0;
        hashTable[i].indicator = EMPTY;
    }

    printf("============= Hash Table ============\n");
    printf("|1. Insert a key to the hash table  |\n");
    printf("|2. Search a key in the hash table  |\n");
    printf("|3. Print the hash table            |\n");
    printf("|4. Quit                            |\n");
    printf("=====================================\n");

    printf("Enter selection: ");
    scanf("%d",&opt);
    while(opt>=1 && opt <=3){
        switch(opt){
        case 1:
            printf("Enter a key to be inserted:\n");
            scanf("%d",&key);
            index = HashInsert(key,hashTable);
            if(index <0)
                printf("Duplicate key\n");
            else if(index < TABLESIZE)
                printf("Insert %d at index %d\n",key, index);
            else
                printf("Table is full.\n");
            break;
        case 2:
            printf("Enter a key for searching in the HashTable:\n");
            scanf("%d",&key);
            index = HashFind(key, hashTable);

            if(index!=-1)
                printf("%d is found at index %d.\n",key,index);
            else
                printf("%d is not found.\n",key);
            break;

        case 3:
            printf("index:\t key \t next\n");
            for(i=0;i<TABLESIZE;i++) printf("%d\t%d\t%d\n",i, hashTable[i].key,hashTable[i].next);
            break;
        }
        printf("Enter selection: ");
        scanf("%d",&opt);
    }
    return 0;
}

int HashInsert(int key, HashSlot hashTable[])
{
    // Write your code here
    int i=0, indexed, updatenextIndex;
    //check table full
    for(i=0; i<=TABLESIZE; i++)
    {
        if(hashTable[i].indicator == EMPTY) //if empty, break out of loop
        {
            break;
        }
    }
    if(i>TABLESIZE) return TABLESIZE + 1;
    //check dupe
    for(i=0; i<=TABLESIZE; i++)
    {
        if(hashTable[i].key == key)
        {
            return -1;
        }
    }
    
    indexed = hash(key); //insert
    //consider if the index is empty,
    if(hashTable[indexed].indicator == EMPTY)
    {
        hashTable[indexed].key = key;
        hashTable[indexed].indicator = USED;
        return indexed;
    }
    //not empty
    else //indicator is USED
    {
        if(hashTable[indexed].next == -1) //.next = -1,
        {
            //linear probing until find an empty slot, update key of empty slot and .next of collision
            updatenextIndex = indexed;
            while(hashTable[indexed].indicator == USED)
            {
                indexed+=1;
                if(indexed == TABLESIZE)
                {
                    indexed = 0;
                }
            }
            hashTable[indexed].key = key;
            hashTable[indexed].indicator = USED;
            hashTable[updatenextIndex].next = indexed;
            return indexed;
        }
        else //next != -1
        {
            //find index until .next == -1
            while(hashTable[indexed].next != -1)
            {
                indexed = hashTable[indexed].next;
                updatenextIndex = indexed; //save the last index right before -1
            }
            
            //check if empty,
            if(hashTable[indexed].indicator == EMPTY)
            {
                hashTable[indexed].key = key;
                hashTable[indexed].indicator = USED;
                hashTable[updatenextIndex].next = indexed;
                return indexed;
            }
            //else linar probe
            else 
            {
                while(hashTable[indexed].indicator == USED)
                {
                    indexed+=1;
                    if(indexed == TABLESIZE)
                    {
                        indexed = 0;
                    }
                }

                hashTable[indexed].key = key;
                hashTable[indexed].indicator = USED;
                hashTable[updatenextIndex].next = indexed;

                return indexed;
            }
        }
    } 



}

int HashFind(int key, HashSlot hashTable[])
{
    // Write your code here
    int i=0;
    for(i=0; i<=TABLESIZE; i++)
    {
        if(hashTable[i].key == key)
        {
            return i;
        }
    }
    return -1;
}