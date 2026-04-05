// LCA（Lowest Common Ancestor）算法用于求树中两个节点的最近公共祖先，即离根节点最远的公共祖先
// 理解暂时不深刻，标记

#include <bits/stdc++.h>
using namespace std;

// 直接对每条路径遍历节点不可行，复杂度高，需要将
// 先介绍几个概念
// 倍增表：fa[x][i]表示从节点x向上2^i步的祖先节点
// 例如i=0表示父节点，i=1表示爷爷节点，i=2表示爷爷的爷爷节点，依次类推
// 这样记录复杂度从n降为log n

const int N=1e5+10;
int c[N][30],fa[N][30];
// c[x][i] 表示到达第i颗星球种类j的数量
// fax[x][i] 表示从节点x向上2^i步的祖先节点
int dep[N];
// dep[x]表示节点x的一个深度值，距离根节点的距离

vector<int> node[N]; // 邻接表

void dfs(int x,int f) // 节点x及其父节点f
{

    for(int i=1;i<=20;i++) c[x][i]+=c[f][i]; // 处理至多20种类别
    // 让当前节点x加上其父节点每个种类
    dep[x]=dep[f]+1; // 通过dfs获取每个节点的深度值

    fa[x][0]=f;
    // 1<=n<=1e5，这里取i最大为20(2^20>1e6)，可以保证关系的全覆盖
    for(int i=1;i<=20;i++) // 用前置信息获取父子关系
    {
        fa[x][i]=fa[fa[x][i-1]][i-1];
        // x向上2^i步的祖宗，等于其向上2^(i-1)步的祖宗，再往上2^(i-1)
    }
    for(auto j:node[x]) // 获取x的邻边，更新c[][] fa[][] dep[]
    {
        if(j==f) continue; // 由于是无向图，要避免反向遍历
        dfs(j,x);
    }
}

int lca(int s,int t) // 返回节点s和t的最近公共祖先
{
    if(dep[s]<dep[t]) swap(s,t); // 按深度顺序遍历，保证s的深度更深

    // // 1<=n<=1e5，这里取i最大为20(2^20>1e6)，可以保证关系的全覆盖
    for(int i=20;i>=0;i--)
    {
        // 将较深的节点s向上跳跃(把当前节点替换为它的祖先节点)，直到它与t相同
        // 之所以从大到小试探，是为了保证可以得到精确移动所需步数
        // eg：dep[t]=0,dep[s]=8，
        // 对于移动步数8 4 2 1，跳一步8即可实现dep[fa[s][i]]=dep[t]，实现深度相同
        // 而如果按照1,2,4,8的顺序，则会跳过头，无法实现深度相同
        if(dep[fa[s][i]]>=dep[t]) s=fa[s][i];
    }
    if(s==t) return s;
    for(int i=20;i>=0;i--)
    {
        if(fa[s][i]!=fa[t][i])
            // 若深度相同但节点不同，不断向上探寻同一深度的祖宗，直到相同，此时它们为兄弟节点
        {
            s=fa[s][i];
            t=fa[t][i];
        }
    }
    return fa[s][0];
}

int main()
{
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        c[i][x] = 1; // 第i颗星球x零食
    }
    // 建立邻接表
    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        node[u].push_back(v);
        node[v].push_back(u);
    }
    dfs(1, 0);
    while (q--) {
        int s, t, ans = 0;
        cin >> s >> t;
        int k = lca(s, t);
        for (int i = 1; i <= 20; i++)
        {
            int num = c[s][i] + c[t][i] - c[k][i] - c[fa[k][0]][i]; // 前缀和的方式理解
            // 起始节点到根节点能买到i种零食的个数 + 终点到根节点能买到i种零食的个数
            // 公共祖先到根节点能买到i种零食的个数- 公共祖先上一个节点到根节点能买到i种零食的个数
            if (num) ans++;
            // num 是颜色在路径上出现的总次数
        }
        cout << ans << endl;
    }
    return 0;
}