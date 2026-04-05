// 以下是错误代码

#include <bits/stdc++.h>
using namespace std;

const int N=1e5+10;

// 利用D(X)=E(X^2)-E(X)^2，通过累计前缀和与平方前缀和可以快速计算方差
typedef long long ll;
__int128 prefix_sum[N];
__int128 prefix_sum_sq[N];

struct student
{
    int idx,score;
    bool operator<(student &another)const
    {
        return score<another.score;
    }
}students[N];

int n,k;
ll T;
void prefix()
{
    for(int i=1;i<=n;i++)
    {
        prefix_sum[i]=prefix_sum[i-1]+students[i].score;
        prefix_sum_sq[i]=prefix_sum_sq[i-1]+students[i].score*students[i].score;
    }
}


__int128 var(int l,int r)
{
    // 为了避免精度问题，后续与T比较时将除法优化为乘法
    __int128 one=prefix_sum_sq[r]-prefix_sum_sq[l-1];
    __int128 two=prefix_sum[r]-prefix_sum[l-1];
    return k*one-two*two;
}


int ans=N;
// 代码错误：它只检查了全局排序后连续的 k 个数，但最优解可能对应一个非连续的子集
// 意思是说，排序后改变了分数的顺序，这个算法的窗口只包含了排序后连续的k个数
// 而在原数组[1,x]中的k个数，即使它们在排序后不再连续，但仍然可能满足条件
// 这种算法可能会忽略掉这些解，而这其中大概率包含最优解x

// 必须要理解的是，虽然最终满足条件的数组必然是大小连续，但不一定是全局意义上连续，更有可能是局部范围上连续
void search()
{
    for(int i=1;i+k-1<=n;i++)
    {
        int j=i+k-1;
        __int128 var_=var(i,j);
        if(var_<(__int128)T*k*k)
        {
            int idx_max=1;
            for(int p=i;p<=j;p++) idx_max=max(idx_max,students[p].idx);
            ans=min(ans,idx_max);
        }
    }
}


int main()
{
    cin>>n>>k>>T;
    for(int i=1;i<=n;i++)
    {
        students[i].idx=i;
        cin>>students[i].score;
    }
    sort(students+1,students+n+1);
    prefix();
    if(ans==N) cout<<-1<<endl;
    else cout<<ans<<endl;
    return 0;
}