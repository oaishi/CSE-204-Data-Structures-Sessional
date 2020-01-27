#include<stdio.h>
#define MAX_HEAP_SIZE 100000
#define MAXREAL 999999.0

class HeapItem
{
public:
    int data; //actual data that is stored
    float key; //key value of the data, heap is constructed based on key
};

//MinHeap class, minimum item stored at the root of heap tree
class MinHeap
{
public:
    HeapItem * A; //stores heap items, e.g., nodes
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
        map = 0; //set to NULL after deletion
        A = 0;//set to NULL after deletion
    }

    void initialize(int v[], int n)
    {
        heapLength = n;
        for(int i=0; i<n; i++) //nodes are stored from index 1 instead of 0 in the heap
        {
            A[i+1].data = v[i];
            A[i+1].key = MAXREAL;
            map[v[i]] = i+1; //data is stored at which heap node
        }
    }

    void insertItem(int data, float key)
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
        map[data] = heapLength;
        buHeapify(heapLength);
    }

    HeapItem removeMin()
    {
        //write your codes here
        HeapItem tt;
        if(Empty())
        {
            tt.data = -1;
            return tt;
        }
        tt = A[1];
        A[1]=A[heapLength];
        heapLength--;
        heapify(1);
        return tt;
    }

    void updateKey(int data, float key)
    {
        //Write your codes here.
        if(data<0)
            return;
        int j;
        bool m = true;
        for(j=1; j<=heapLength; j++)
        {
            if(A[j].data == data)
            {
                m = false;
                break;
            }
        }
        if(m)
        {
            printf("Data Not Found\n");
            return;
        }
        float temp = getKey(data);
        if(temp==key)
            return;
        int i = map[data];
        A[i].key = key;
        if(temp>key)
        {
            buHeapify(i);
        }
        else if(temp<key)
        {
            heapify(i);
        }
        return;
    }

    float getKey(int data)
    {
        int i = map[data];
        return A[i].key;
    }

    void heapify(int i)
    {
        int l,r,smallest;
        while(1)
        {
            l=2*i;      //left child index
            r=2*i+1;    //right child index
            smallest=i;

            if(l>heapLength && r>heapLength)
                break; //nothing to do, we are at bottom
            else if(r>heapLength)
                smallest = l;
            else if(l>heapLength)
                smallest = r;
            else if( A[l].key < A[r].key )
                smallest = l;
            else
                smallest = r;

            if(A[i].key <= A[smallest].key)
                break;	//we are done heapifying
            else
            {
                //swap nodes with smallest child, adjust map array accordingly
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
            printf(" (%d,%.2f) -> ", A[i].data, A[i].key);
        }
        printf("\n");
    }

    bool Empty()
    {
        if(heapLength==0)
            return true;
        else
            return false;
    }
};


int main()
{
    int choice;
    int data;
    float key;
    MinHeap heap;
    bool exit = false;
    while(!exit)
    {
        printf("1. Insert 2. RemoveMin 3.Update 4. Print 5. Exit.\n");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            scanf("%d%f",&data,&key);
            heap.insertItem(data, key);
            heap.printHeap();
            break;
        case 2:
            HeapItem item;
            item = heap.removeMin();
            if(item.data==-1)
                printf("Heap Empty\n");
            else
                printf("Removed: (%d,%.2f)\n", item.data, item.key);
            heap.printHeap();
            break;
        case 3:
            scanf("%d%f",&data,&key);
            heap.updateKey(data,key);
            heap.printHeap();
            break;
        case 4:
            heap.printHeap();
            break;
        case 5:
            exit = true;
            break;
        default:
            continue;
        }
    }
    return 0;
}
