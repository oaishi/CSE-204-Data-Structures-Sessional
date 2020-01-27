#include<cstdio>
#include<iostream>

using namespace std;

int smally ;

typedef struct points
{
    int x;
    int y;
} p;

p L[3000], R[3000];

void mergeY(p arr[], int l, int m, int r)
{
    int i, j, k;
    int low = m - l + 1;
    int high =  r - m;
    L[low], R[high];
    for (i = 0; i < low ; i++)
    {
        L[i].x = arr[l + i].x;
        L[i].y = arr[l + i].y;
    }
    for (j = 0; j < high ; j++)
    {
        R[j].x = arr[m + 1+ j].x;
        R[j].y = arr[m + 1+ j].y;
    }
    i = 0;
    j = 0;
    k = l;
    while (i < low && j < high)
    {
        if (L[i].y < R[j].y)
        {
            arr[k].x = L[i].x;
            arr[k].y = L[i].y;
            i++;
        }
        else if(L[i].y > R[j].y)
        {
            arr[k].x = R[j].x;
            arr[k].y = R[j].y;
            j++;
        }
        else
        {
            if (L[i].x <= R[j].x)
            {
                arr[k].x = L[i].x;
                arr[k].y = L[i].y;
                i++;
            }
            else if(L[i].x > R[j].x)
            {
                arr[k].x = R[j].x;
                arr[k].y = R[j].y;
                j++;
            }
        }
        k++;
    }
    while (i < low)
    {
        arr[k].x = L[i].x;
        arr[k].y = L[i].y;
        i++;
        k++;
    }

    while (j < high)
    {
        arr[k].x = R[j].x;
        arr[k].y = R[j].y;
        j++;
        k++;
    }
}

void mergeSortY(p arr[], int l, int r)
{
    if (l < r)
    {
        int m = l+(r-l)/2;
        mergeSortY(arr, l, m);
        mergeSortY(arr, m+1, r);
        mergeY(arr, l, m, r);
    }
}


int main()
{
    int arr_size, small;
    cin>>arr_size;
    p values[300];
    int tracer[300];
    for(int i=0; i<arr_size; i++)
    {
        cin>>values[i].x;
        cin>>values[i].y;
    }
    mergeSortY(values, 0, arr_size - 1);
    small=0;
    smally=values[0].y;
    tracer[small]=0;
    small++;
    cout<<endl;
    for(int i=1; i<arr_size; i++)
    {
        if(values[i].x>=smally)
        {
            smally = values[i].y;
            tracer[small]=i;
            small++;
        }
    }
    cout<<small<<endl;
    small--;
    for(int i=0; i<=small; i++)
    {
        cout<<values[tracer[i]].x << " "<< values[tracer[i]].y<<endl;
    }
    return 0;
}

