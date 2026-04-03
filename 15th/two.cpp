#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll N=1e5+10;

struct soldier
{
    ll cost,count;
    bool operator<(soldier s)const
    {
        return count<s.count;
    }
}soldiers[N];


// struct cmp
// {
//     bool operator()(PII &a,PII &b)const
//     {
//         return a.second<b.second;
//     }
// };


int n,s;
ll total;
ll prefix_sum[N]; // prefix_sun[i]表示前i+1个士兵分别训练一次的成本
void initial()
{
    cin>>n>>s;
    for(int i=0;i<n;i++)
    {
        ll cost,count;
        cin>>cost>>count;
        soldiers[i]={cost,count};
    }
    sort(soldiers,soldiers+n);
    reverse(soldiers,soldiers+n);

    prefix_sum[0]=soldiers[0].cost;
    for(int i=1;i<n;i++) prefix_sum[i]=prefix_sum[i-1]+soldiers[i].cost;
}


void train()
{
    int idx=n-1;
    while(idx>=0 && prefix_sum[idx]>s)
    {
        ll min_count=soldiers[idx].count;
        total+=min_count*s;
        for(int i=0;i<=idx;i++)
        {
            soldiers[i].count-=min_count;
            if(soldiers[i].count==0)
            {
                idx=i-1;
                break;
            }
        }
        if(idx<0) break;
    }
    for(int i=idx;i>=0;i--)
    {
        total+=soldiers[i].cost*soldiers[i].count;
    }
}

int main()
{
    initial();
    train();
    cout<<total<<endl;
    return 0;
}

// 时间复杂度略高