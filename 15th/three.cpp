#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int base=131;
const int mod=1e9+7;

unordered_set<ll> path_hash;
// 将字符串变为一个base进制数字，实现不同的字符串映射到不同的数字

vector<int> c;
vector<vector<int>> group1; // 邻接表，存储路径
void dfs1(int u,int parent,ll cur_hash) // 遍历树1，计算各节点的哈希值
{
    cur_hash=(cur_hash*base+c[u])%mod; // 哈希公式
    path_hash.insert(cur_hash); // 将树1的哈希值存储进一个集合中
    // 搜索相邻节点
    for(int v:group1[u])
    {
        if(v!=parent) // 因为是无向图，这里要避免反向遍历计算错误哈希值
        {
            dfs1(v,u,cur_hash);
        }
    }
}

int ans;
vector<int> d;
vector<vector<int>> group2;
void dfs2(int u,int parent,ll cur_hash,int depth) // 遍历树2，计算各节点的哈希值
                                             // depth是当前节点距离根节点的距离+1
{
    cur_hash=(cur_hash*base+d[u])%mod;
    if(path_hash.count(cur_hash)) ans=max(ans,depth);
    // 如果树2的哈希值在集合中，说明对于树1和树2，存在一条根节点到u的相同路径，更新答案
    // 搜索相邻节点
    for(int v:group2[u])
    {
        if(v!=parent) dfs2(v,u,cur_hash,depth+1);
    }
}


int n,m;
void initial()
{
    cin>>n>>m;
    c.resize(n+1);
    for(int i=1;i<=n;i++) cin>>c[i];
    d.resize(m+1);
    for(int i=1;i<=m;i++) cin>>d[i];
    group1.resize(n+1);
    for(int i=1;i<=n-1;i++) // n个结点,n-1条边
    {
        int u,v;
        cin>>u>>v;
        group1[u].push_back(v);
        group1[v].push_back(u);
    }
    group2.resize(m+1);
    for(int i=1;i<=m-1;i++)
    {
        int u,v;
        cin>>u>>v;
        group2[u].push_back(v);
        group2[v].push_back(u);
    }
}

int main()
{
    initial();
    dfs1(1,0,0); // 初始哈希值为0
    dfs2(1,0,0,1);
    cout<<ans<<endl;
    return 0;
}