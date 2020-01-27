#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#define inf 100000;
using namespace std;
int p[101],countl,countr;
char str[100],stri[100];
int s[100][100];
int Matrix_chain(int n)
{
    int m[n][n];
    int i,j,k,l,q;
    for (i=1; i<n; i++)
        m[i][i] = 0;
    for(l=2; l<=n; l++)
    {
        for(i=1; i<=(n-l+1); i++)
        {
            j=i+l-1;
            m[i][j]= inf;
            for(k=i; k<=j-1; k++)
            {
                q = m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];
                if(q<m[i][j])
                {
                    m[i][j]=q;
                    s[i][j]=k;
                }
            }
        }
    }
    return m[1][n-1];
}

void Mult(int i,int j)
{
    if(i<j)
    {
        Mult(i, s[i][j]);
        Mult(s[i][j]+1,j);
    }
    /*if(i!=j){
    for(int k=1;k<=strlen(stri);k++)
    {
        if(stri[k]==str[i])
            countl=k;
        else if(stri[k]==str[j]){
            countr=k;
            break;
        }
    }
    char d,e;
    d= str[i];
    stri[countl]='(';
    for(countl++;countl<=(strlen(stri)+1);countl++)
    {
        e=stri[countl];
        stri[countl]=d;
        d = e;
    }
    d = stri[countr+2];
    stri[countr+2]=')';
    countr+=3;
    for(countr;countr<=(strlen(stri)+1);countr++)
    {
        e=stri[countr];
        stri[countr]=d;
        d = e;
    }
    }*/
}
int main()
{
    int number , c ;
    bool run = true;
    cin>>number;
    int j=0;
    //str[j]=' ';
    //stri[j]=' ';
    for(int i=1; i<=number; i++)
    {
        //str[i] = 'A'+i-1;
        //stri[i]=str[i];
        if(j==0)
        cin>>p[j++];
        else
        {
            cin>>c;
            if(c!=p[j])
            {
                run = false;
            }
            else
                j++;
        }
        cin>>p[j];
    }

    //str[number+1]='\0';
    //stri[number+1]='\0';
    if(run){
    cout<<Matrix_chain(number+1)<<endl;
    Mult(1,number);
    //cout<<stri<<endl;
    }
    else
       cout<<"Error!"<<endl;
}
