#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

struct listNode
{
    int item;
    struct listNode * next;
};

struct listNode * list;
struct listNode * tail;

void initializeList()
{
    list = 0;  //initially set to NULL
    tail = 0;
}

struct listNode * searchItem(int item)
{
    struct listNode * temp ;
    temp = list ; //start at the beginning
    while (temp != 0)
    {
        if (temp->item == item) return temp ;
        temp = temp->next ; //move to next node
    }
    return 0 ; //0 means invalid pointer in C, also called NULL value in C
}

void printList()
{
    struct listNode * temp;
    temp = list;
    while(temp!=0)
    {
        printf("%d->", temp->item);
        temp = temp->next;
    }
    printf("\n");
}

//add required codes to insert item at the beginning, remember to properly set the tail pointer!
int insertItem( int newItem)
{
    //write your codes here
    struct listNode * newNode ;
    newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
    newNode->item = newItem ;
    newNode->next = list ;
    if(list == 0)
        tail = newNode;//point to previous first node
    list = newNode ; //set list to point to newnode as this is now the first node
    return SUCCESS_VALUE ;
}

//add required codes to delete item, remember to properly set the tail pointer!
int deleteAfter(int item)
{
    struct listNode  *left, *newNode;
    if(list == 0)
    {
        printf("Insert items first\n");
        return NULL_VALUE;
    }
    left = list;
    if(left->next == NULL)
    {
        printf("No Item Found to be deleted\n");
        return NULL_VALUE;
    }
    while(left->item != item )
    {
        left=left->next;
        if(left == NULL || left->next == NULL)
        {
            printf("No Item Found to be deleted\n");
            return NULL_VALUE;
        }
    }
    if(left->item != item)
    {
        printf("No Item Found to be deleted");
        return NULL_VALUE;
    }
    newNode = left->next;
    left->next = newNode->next;
    if(newNode == tail)
        tail = left;
    free(newNode);
    return SUCCESS_VALUE;
}

int insertLast(int item)
{
    //write your codes here
    struct listNode * newNode ;
    newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
    newNode->item = item ;
    newNode->next = NULL;
    tail->next = newNode;
    tail = newNode;
    return SUCCESS_VALUE;
}


int main(void)
{
    initializeList();
    while(1)
    {
        printf("1. Insert new item. 2. Delete item. 3. Search item. \n");
        printf("4. Insert last. 5. Print. 6. Exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(item);
        }
        else if(ch==2)
        {
            int item;
            scanf("%d", &item);
            deleteAfter(item);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            struct listNode * res = searchItem(item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==4)
        {
            int item;
            scanf("%d", &item);
            insertLast(item);
        }
        else if(ch==5)
        {
            printList();
        }
        else if(ch==6)
        {
            exit(1);
        }
    }
}
