# include <bits/stdc++.h>
using namespace std;

const int mod =1000000007;

vector<int> nums;
unordered_map<int,int>freq;
typedef pair<int,int> PII;
vector<PII> scale;
typedef long long ll;

void search_scale(int total)
{
    for(int x:nums)
    {
        freq[x]++;
    }

    int target=total-2;
    for(auto &p:freq)
    {
        int n=p.first;
        if(target%n==0)
        {
            int m=target/n;
            if(freq.count(m))
            {
                if(n==m)
                {
                    if(freq[n]>=2) scale.push_back({n,m});
                }
                else scale.push_back({n,m});
            }
        }
    }
}

ll fast_ex(ll a,ll b)
{
    long long res=1;
    while(b)
    {
        if(b&1) res=res*a%mod;
        a=a*a%mod;
        b=b>>1;
    }
    return res;
}

vector<ll> fact,invfact; // 存储0~m*n-2的阶乘
void precompute(int n)
{
    fact.resize(n+1);
    invfact.resize(n+1);
    fact[0]=1;
    for(int i=1;i<=n;i++)
    {
        fact[i]=fact[i-1]*i%mod;
    }
    invfact[n]= fast_ex(fact[n],mod-2);
    for(int i=n-1;i>=0;i--)
    {
        invfact[i]=invfact[i+1]*(i+1)%mod;
    }
}



int main()
{
    int total;
    cin>>total;
    for(int i=1;i<=total;i++)
    {
        int num;
        cin>>num;
        nums.push_back(num);
    }
    
    search_scale(total);
    precompute(total-2);
    
    

    ll ans=0;
    for(auto &p:scale)
    {
        // 这里不建议拷贝一个全新的freq用于后续运算，可能会超时
        // 直接在运算后回溯频率是最简单的方法
        int n=p.first,m=p.second;
        freq[n]--;
        freq[m]--;

        ll ways=fact[total-2];
        for(auto &q:freq)
        {
            int cnt=q.second;
            if(cnt>0) ways=ways*invfact[cnt]%mod;
        }
        ans=(ans+ways)%mod;

        // 回溯
        freq[n]++;
        freq[m]++;
    }
    
    cout<<ans<<endl;

    return 0;
}