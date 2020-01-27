#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

struct listNode
{
    int item;
    struct listNode * next;
};

struct listNode * list; //head

void initializeList()
{
    list = 0;  //initially set to NULL
}

int insertItem(int item) //insert at the beginning of the linked list
{
    struct listNode * newNode ;
    newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
    newNode->item = item ;
    newNode->next = list ; //point to previous first node
    list = newNode ; //set list to point to newnode as this is now the first node
    return SUCCESS_VALUE ;
}


int deleteItem(int item)
{
    struct listNode *temp, *prev ;
    temp = list ; //start at the beginning
    while (temp != 0)
    {
        if (temp->item == item) break ;
        prev = temp;
        temp = temp->next ; //move to next node
    }
    if (temp == 0) return NULL_VALUE ; //item not found to delete
    if (temp == list) //delete the first node
    {
        list = list->next ;
        free(temp) ;
    }
    else
    {
        prev->next = temp->next ;
        free(temp);
    }
    return SUCCESS_VALUE ;
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

int insertLast(int item)
{
    //write your codes here
    struct listNode *newNode, *temp ;
    newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
    newNode->item = item ;
    newNode->next = NULL ; //point to previous first node
    temp = list;
    while(temp->next != NULL)
        temp=temp->next;
    temp->next = newNode;
    printf("Successfully added \n");
    return SUCCESS_VALUE;
}

int insertBefore(int oldItem, int newItem)
{
    //write your codes here
    struct listNode *newNode, *left, *right ;
    newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
    newNode->item = newItem;
    left = list;
    if(left->item == oldItem)
    {
        insertItem(newItem);
        return SUCCESS_VALUE;
    }
    right = left->next;
    if(right == NULL)
    {
        insertItem(newItem);
        return SUCCESS_VALUE;
    }
    while(right->item != oldItem )
    {
        left=right;
        right = right->next;
        if(right == NULL)
        {
            insertItem(newItem);
            return SUCCESS_VALUE;
        }
    }
    left->next= newNode;
    newNode->next = right;
    return SUCCESS_VALUE;
}

int deleteAfter(int item)
{
    //write your codes here
    struct listNode  *left, *newNode;
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
    free(newNode);
    return SUCCESS_VALUE;
}

int deleteLast()
{
    //write your codes here
    struct listNode  *left, *newNode;
    if(list == NULL )
    {
        printf("List is Empty\n");
        return NULL_VALUE;
    }
    left = list;
    if(left->next == NULL)
    {
        list = 0;
        free(left);
        return SUCCESS_VALUE;
    }
    while(left->next->next != NULL)
        left = left->next;
    newNode = left->next;
    free(newNode);
    left->next = NULL;
    return SUCCESS_VALUE;
}

int main(void)
{
    initializeList();
    while(1)
    {
        printf("1. Insert new item. 2. Delete item. 3. Search item. \n");
        printf("4. Insert Last. 5. Print. 6. Insert Before. \n");
        printf("7. Delete last element. 8. Delete After\n");

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
            scanf("%d",&item);
            deleteItem(item);
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
            int old , newit;
            printf("Insert the item to be followed by:");
            scanf("%d", &old);
            printf("Insert the item to be inserted:");
            scanf("%d", &newit);
            insertBefore(old,newit);
        }
        else if(ch==7)
        {
            deleteLast();
        }
        else if(ch==8)
        {
            int old ;
            printf("The item deletion will be followed by:");
            scanf("%d", &old);
            deleteAfter(old);
        }
        else
            break;
    }

}
