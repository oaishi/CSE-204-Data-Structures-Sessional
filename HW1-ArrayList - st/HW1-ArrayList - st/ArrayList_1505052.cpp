#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define LIST_INIT_SIZE 2
#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

int listMaxSize;
int * list;
int length;

void initializeList()
{
    listMaxSize = LIST_INIT_SIZE;
    list = (int*)malloc(sizeof(int)*listMaxSize) ;
    length = 0 ;
}

void shrink()
{
    if( (2*length) <= listMaxSize && listMaxSize!= LIST_INIT_SIZE)
    {
        // printf("%d %d \n" ,listMaxSize , length);
        int * tempList ;
        //allocate new memory space for tempList
        listMaxSize =  listMaxSize / 2 ;
        tempList = (int*) malloc (listMaxSize*sizeof(int)) ;
        int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        free(list) ; //free the memory allocated before
        list = tempList ;
    }
    //printf("%d %d \n" ,listMaxSize , length);
}

int searchItem(int item)
{
    int i = 0;
    for (i = 0; i < length; i++)
    {
        if( list[i] == item ) return (i+1);
    }
    return NULL_VALUE;
}

int insertItem(int newitem)
{
    int * tempList ;
    if (length == listMaxSize)
    {
        //allocate new memory space for tempList
        listMaxSize = 2 * listMaxSize ;
        tempList = (int*) malloc (listMaxSize*sizeof(int)) ;
        int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        free(list) ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
    };

    list[length] = newitem ; //store new item
    length++ ;
    return SUCCESS_VALUE ;
}


int deleteItemAt(int position) //version 2, do not preserve order of items
{
    if ( position >= length ) return NULL_VALUE;
    list[position] = list[length-1] ;
    length-- ;
    shrink();
    return SUCCESS_VALUE ;
}

int deleteItem(int item)
{
    int position;
    position = searchItem(item) ;
    if ( position == NULL_VALUE ) return NULL_VALUE;
    deleteItemAt(position) ;
    return SUCCESS_VALUE ;
}

void printList()
{
    int i;
    for(i=0; i<length; i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

int getlength()
{
    return length;
}

int insertItemAt(int pos, int item)
{
    if (pos >= length || pos<0)
    {
        printf("error!");
        return NULL_VALUE;
    }
    else
    {
        int item1;
        if (length == listMaxSize)
        {
            int * tempList ;
            //allocate new memory space for tempList
            listMaxSize = 2 * listMaxSize ;
            tempList = (int*) malloc (listMaxSize*sizeof(int)) ;
            int i;
            for( i = 0; i < length ; i++ )
            {
                tempList[i] = list[i] ; //copy all items from list to tempList
            }
            free(list) ; //free the memory allocated before
            list = tempList ; //make list to point to new memory
        }
        item1 = list[pos];
        list[length]=item1;
        list[pos] = item;
        length++;
        return SUCCESS_VALUE;
    }
}

void deleteLast()
{
    length--;
    //printf("%d", length);
    shrink();
}

void clear ()
{
    free(list);
    initializeList();
}

void deleteAll ()
{
    length = 0;
    shrink();
}

int main(void)
{
    initializeList();
    while(1)
    {
        printf("1. Insert new item.\n2. Delete item at.\n3. Delete item.\n");
        printf("4. Get Current Length.\n5. Print.\n6. Insert Item at a Fixed Position.\n");
        printf("7. Delete Last Element \n8. Delete All Element. \n9. Clear the List.\n");
        printf("10. Search Item\n11.Exit.\n");
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
            int pos;
            scanf("%d", &pos);
            deleteItemAt(pos);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            deleteItem(item);
        }

        else if(ch==4)
        {
            int gt_length;
            gt_length = getlength();
            printf("Current length : " );
            printf("%d\n", gt_length);
        }

        else if(ch==5)
        {
            printList();
        }
        else if(ch==6)
        {
            int item,pos;
            printf("Enter the position : \n");
            scanf ("%d", & pos);
            printf("Enter the value : \n");
            scanf ("%d", &item );
            printf("%d",insertItemAt(pos,item));
        }
        else if(ch ==7)
            deleteLast( );
        else if(ch==8)
            deleteAll( );
        else if(ch==9)
            clear();
        else if (ch==10)
        {
            int i;
            printf("Insert the item to be searched:");
            scanf("%d", &i);
            printf("%d" ,searchItem(i));
            printf("\n");
        }
        else if(ch==11)
        {
            free(list);
            exit(1);
        }
    }
}

//int main(void)
//{
//    initializeList();
//    char fix[40];
//    while(1)
//    {
//        printf("Enter your string:");
//        scanf("%s", fix);
//        int str=strlen(fix);
//        int i=0;
//        while(i<str)
//        {
//            if(fix[i]>47 && fix[i]<58)
//            {
//                int value = fix[i] - 48;
//                insertItem(value);
//            }
//            else
//            {
//                int a = list[length-2];
//                int b = list[length-1];
//                deleteLast();
//                deleteLast();
//                if(fix[i]=='+')
//                    insertItem(a+b);
//                else if(fix[i]=='-')
//                    insertItem(a-b);
//                else if(fix[i]=='*')
//                    insertItem(a*b);
//                else if(fix[i]=='/' && b!=0)
//                    insertItem(a/b);
//            }
//            i++;
//        }
//        int result = list[length-1];
//        deleteLast();
//        if(getlength()!=0)
//            printf("The string you entered is invalid!\n");
//        else
//            printf("Your answer is :%d\n", result);
//        clear();
//    }
//    free(list);
//}
//
