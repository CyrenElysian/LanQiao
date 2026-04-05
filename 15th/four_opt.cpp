#include <bits/stdc++.h>
using namespace std;

const int N=1e5+10;
typedef long long ll;
int n,k;
ll T;
vector<ll> a;

bool check(int x)
{
    if(x<k) return false; // 如果数据量少于k，则必然不能满足要求
    // 按顺序提取前x个数，每次只研究这一部分，而不是直接研究全局
    vector<ll> b(a.begin(),a.begin()+x);
    sort(b.begin(),b.end());

    __int128 sum=0,sum_sq=0;
    // 依然利用D(X)=E(X^2)-E(X)^2，通过累计前缀和与平方前缀和可以快速计算方差
    for(int i=0;i<k;i++)
    {
        sum+=b[i];
        sum_sq+=b[i]*b[i];
    }

    __int128 target=(__int128)T*k*k; // 将计算期望中的除法转化为乘法
    if(k*sum_sq-sum*sum<target) return true; // 如果运气好[0,k-1]即满足答案，否则继续

    // 必须要理解的是，虽然最终满足条件的数组必然是大小连续(经过排序)
    // 但不一定是全局意义上连续，更有可能是局部范围上连续
    // 遍历经过排序的局部数组b
    for(int i=k;i<x;i++)
    {
        sum+=b[i]-b[i-k];
        sum_sq+=b[i]*b[i]-b[i-k]*b[i-k]; // 平方差公式，注意乘法溢出
        if(k*sum_sq-sum*sum<target) return true;
    }
    return false;
}

int main()
{
    cin>>n>>k>>T;
    a.resize(n);
    for(int i=0;i<n;i++) cin>>a[i];

    // 二分范围，加快查询速度
    int l=1,r=n;
    int ans=-1;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(check(mid)) // 若1~mid存在答案，则二分左半范围
        {
            ans=mid;
            r=mid-1; // 记录答案，搜索1~mid-1是否存在符合要求的x
        }
        else l=mid+1; // 1~mid没有答案，二分右半范围

    }

    cout<<ans<<endl;
    return 0;
}