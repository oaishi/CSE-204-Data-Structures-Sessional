#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

struct listNode
{
    int item;
    struct listNode * next;
    struct listNode * prev;
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

int insertFirst(int item) //insert at the beginning
{
    struct listNode * newNode ;
    newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
    newNode->item = item ;

    if(list==0) //inserting the first item
    {
        newNode->next = 0;
        newNode->prev = 0;
        list = newNode;
        tail = newNode;
    }
    else
    {
        newNode->next = list;
        list->prev = newNode;
        newNode->prev = 0;
        list = newNode;
    }
    return SUCCESS_VALUE ;
}


int deleteAfter(int item)
{
    //write your codes here
    struct listNode  *temp, *newNode;
    if(list == 0)
    {
        printf("Insert items First.\n");
        return NULL_VALUE;
    }
    newNode = searchItem(item);
    if( newNode == tail || newNode ==0)
    {
        printf("Nothing to be deleted.\n");
        return NULL_VALUE;
    }
    temp = newNode->next;
    if(temp == NULL)
    {
        printf("Nothing to be deleted.\n");
        return NULL_VALUE;
    }
    newNode->next = newNode->next->next;
    if(temp == tail)
    {
        tail = newNode;
        free(temp);
        return SUCCESS_VALUE;
    }
    free(temp);
    temp->next->prev = newNode;
    return SUCCESS_VALUE;
}

int deleteLast()
{
    //write your codes here
    if(list == 0)
        return NULL_VALUE;
    struct listNode  *temp ;
    temp = tail;
    if(tail == list)
    {
        free(temp);
        list=0;
        tail =0;
        return SUCCESS_VALUE;
    }
    tail->prev->next=NULL;
    tail = tail->prev;
    free(temp);
    return SUCCESS_VALUE;
}

void printListForward()
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

void printListBackward()
{
    //will print the list backward starting from the tail position
     if(tail==0)
     {
         printf("Insert item first.\n");
         return;
     }
     struct listNode *temp;
     temp = tail;
     while(temp!=0)
     {
         printf("%d->" , temp->item);
         temp = temp->prev;
     }
     printf("\n");
     free(temp);
     return;
}


int main(void)
{
    initializeList();
    while(1)
    {
        printf("1. Insert new item. 2. Delete item. 3. Search item. \n");
        printf("4. Print forward. 5. Print backward. 6. Delete last 7. Exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertFirst(item);
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
            printListForward();
        }
        else if(ch==5)
        {
            printListBackward();
        }
        else if(ch==6)
        {
            int item = deleteLast();
            if(item!=NULL_VALUE) printf("Deleted: %d\n", item);
            //printListBackward();
        }
        else
            exit(1);
    }

}
