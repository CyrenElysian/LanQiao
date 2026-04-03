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


int n;
ll s;
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
    reverse(soldiers,soldiers+n);  // 将士兵按训练次数降序排列

}


ll ans = 0;
void train()
{
    for (int i = 0; i < n; i++)
    {
        ans += soldiers[i].cost * soldiers[i].count; // 全个人训练，成本上限
    }

    ll sum_cost = 0, sum_single_cost = 0;
    for (ll i = 0; i < n; i++) 
    {
        sum_cost += soldiers[i].cost * soldiers[i].count; // 累计训练总成本
        sum_single_cost += soldiers[i].cost; // 累计单次训练成本
        ll x = soldiers[i].count; // 当进行过x次集体训练后，对未达到训练目标的士兵各单独训练一次的成本会低于s，此时进行单独训练
        // 又由于soldiers[]按找count降序排列，所有在soldiers[i]之后的士兵已经完成训练了，成本为x*s，现在只要加上单独训练的成本即可
        ll cur = x * s + (sum_cost - x * sum_single_cost); // (sum_cost - x * sum_single_cost)为剩余成本
        ans = min(ans, cur);
    }
}

int main()
{
    initial();
    train();
    cout<<ans<<endl;
    return 0;
}