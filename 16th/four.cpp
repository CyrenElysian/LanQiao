# include <bits/stdc++.h>
using namespace std;

void red_black(int n,int k)
{
    int idx=pow(2,n-1)+k-1;
    int change=1;
    while(idx!=1)
    {
        if(idx%2==0)
        {
            idx/=2;
        }
        else
        {
            change*=-1;
            idx/=2;
        }
    }
    if(change==1) cout<<"RED"<<endl;
    else cout<<"BLACK"<<endl;
}

int main()
{
    int m;
    cin>>m;
    while(m--)
    {
        int n,k;
        cin>>n>>k;
    }
}

