#include <iostream>

using namespace std;

typedef long long int lli;

int main()
{
    lli n,counts=0,countb=0,small,big,input;
    cin>>n;
    small=1000000001;
    big=-1;
    for(lli i =0; i<n; i++)
    {
        cin>>input;
        if(input<small)
        {
            counts=1;
            small=input;
        }
        else if(input==small)
            counts++;
        if(input>big)
        {
            countb=1;
            big = input;
        }
        else if(input==big)
            countb++;
    }
    big = big-small ;
    if(big!=0)
        countb = countb*counts;
    else
        countb=0;
    cout<<big<<" " << countb<<endl;
    return 0;
}
