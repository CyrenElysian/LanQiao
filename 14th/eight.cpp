#include <bits/stdc++.h>
using namespace std;
// 能通过90%样例

const int N=1e5+10;
typedef long long ll;
ll a[N];
ll pre_xor[N];


int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    for(int i=1;i<=n;i++)
    {
        pre_xor[i]=pre_xor[i-1]^a[i];
    }

    ll res=0;
    for(int len=0;len<n;len++)
    {
        for(int l=1;l+len<=n;l++)
        {
            int r=l+len;
            if(len==0) res+=a[l];
            else
            {

                res+=pre_xor[r]^pre_xor[l-1];
            }
        }
    }
    cout<<res<<endl;
    return 0;
}
