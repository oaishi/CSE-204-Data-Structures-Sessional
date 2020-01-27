#include<stdio.h>
#include<stdlib.h>
#define MAX_HEAP_SIZE 100000
#define MAXREAL 999999.0
#include<iostream>

using namespace std;
class HeapItem
{
public:
    char data;
    float key;
    HeapItem *left, *right;
};
class MinHeap
{
public:
    HeapItem * A;
    int heapLength;
    int * map;

    MinHeap() //constructor
    {
        A = new HeapItem[MAX_HEAP_SIZE];
        map = new int[MAX_HEAP_SIZE];
        heapLength=0;
    }

    ~MinHeap() //destructor
    {
        if(map) delete [] map;
        if(A) delete [] A;
        map = 0;
        A = 0;
    }

    void insertItem(char data, float key)
    {
        if(data<0)
        {
            printf("Negative data can't be inserted\n");
            return;
        }
        heapLength++;
        if(heapLength==MAX_HEAP_SIZE)
        {
            heapLength--;
            return;
        }
        A[heapLength].data = data;
        A[heapLength].key = key;
        A[heapLength].left =0;
        A[heapLength].right = 0;
        map[data] = heapLength;
        buHeapify(heapLength);
    }

    void insertIt(char data, float key, HeapItem *left, HeapItem *right)
    {

        heapLength++;
        if(heapLength==MAX_HEAP_SIZE)
        {
            heapLength--;
            return;
        }
        HeapItem hp;
        hp.data = data;
        hp.key = key;
        hp.left = left;
        hp.right = right;
        A[heapLength] = hp;
        map[data] = heapLength;
        buHeapify(heapLength);
    }

    HeapItem removeMin()
    {
        //write your codes here
        HeapItem tt;
        if(Empty())
        {
            tt.data = '1';
            return tt;
        }
        tt.data = A[1].data;
        tt.key = A[1].key;
        tt.left = A[1].left;
        tt.right = A[1].right;
        if(heapLength>1)
        A[1]=A[heapLength];

        heapLength--;
        heapify(1);
        return tt;
    }

    void heapify(int i)
    {
        int l,r,smallest;
        while(1)
        {
            l=2*i;
            r=2*i+1;
            smallest=i;

            if(l>heapLength && r>heapLength)
                break;
            else if(r>heapLength)
                smallest = l;
            else if(l>heapLength)
                smallest = r;
            else if( A[l].key < A[r].key )
                smallest = l;
            else
                smallest = r;
            if(A[i].key <= A[smallest].key)
                break;
            else
            {
                HeapItem t;
                t=A[i];
                A[i]=A[smallest];
                map[A[i].data]=i;
                A[smallest]=t;
                map[A[smallest].data]=smallest;
                i=smallest;
            }

        }
    }

    void buHeapify(int i)
    {
        if(heapLength ==0 || heapLength==1)
            return;
        int j;
        while(i>1)
        {
            if(i%2)
                j= (i-1)/2;
            else
                j=i/2;
            if(A[j].key>A[i].key)
            {
                HeapItem tem = A[i];
                A[i] = A[j];
                A[j] = tem;
                map[A[i].data]=i;
                map[A[j].data]=j;
                i=j;
            }
            else
                return;
        }
    }

    void printHeap()
    {
        printf("Heap length: %d\n", heapLength);
        for(int i=1; i<=heapLength; i++)
        {
            printf(" (%c,%.2f) -> ", A[i].data, A[i].key);
        }
        printf("\n");
    }

    void printcodes(HeapItem *root , int top , int codes[])
    {
        if(root->left)
        {
            codes[top] = 0;
            printcodes(root->left,top+1,codes);
        }
        if(root->right)
        {
            codes[top] = 1;
            printcodes(root->right,top+1,codes);
        }
        if(!(root->left) && !(root->right) )
        {
            printf("  %c : %0.0f  -  %d - ",root->data, root->key , top);
            for(int i=0;i<top;i++)
                printf("%d",codes[i]);
            printf("\n");
        }
        return;
    }

    bool Empty()
    {
        if(heapLength==0)
            return true;
        else
            return false;
    }

    int length()
    {
        return heapLength;
    }

    void huffcode()
    {
        HeapItem hp;
        while(heapLength >1)
        {
            HeapItem *hp1 = (HeapItem*)malloc(sizeof(HeapItem));
            HeapItem *hp2 = (HeapItem*)malloc(sizeof(HeapItem));
            hp = removeMin();
            hp1->data = hp.data;
            hp1->key = hp.key;
            hp1->left = hp.left;
            hp1->right = hp.right;
            hp = removeMin();
            hp2->data = hp.data;
            hp2->key = hp.key;
            hp2->left = hp.left;
            hp2->right = hp.right;
            insertIt('1',hp1->key + hp2->key,hp1,hp2);
        }
    }


};

int main()
{
    MinHeap heap;
    HeapItem *hp1 = (HeapItem*)malloc(sizeof(HeapItem));
    HeapItem *hp2 = (HeapItem*)malloc(sizeof(HeapItem));
    int choice , codes[100];
    char da;
    int data;
    float key, arr_size;
    scanf("%f",&arr_size);
    for(int i=0; i<arr_size; i++)
    {
        cin>>da>>key;
        heap.insertIt(da, key , 0 ,0);
    }
    heap.huffcode();
    cout<<"CHAR-FREQ-LENGTH-CODE"<<endl;
    HeapItem hp = heap.removeMin();
    heap.printcodes(&hp,0,codes);
    return 0;
}
