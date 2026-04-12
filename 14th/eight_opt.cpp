#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 提供一个更高效的做法

int main()
{

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    // 前缀异或
    vector<int> pre(n + 1, 0);
    for (int i = 0; i < n; ++i) pre[i + 1] = pre[i] ^ a[i];

    ll ans = 0;
    // Ai <= 2^20，所以考虑 0~20 位足够
    for (int k = 0; k < 21; ++k)
    {
        ll cnt1 = 0, cnt0 = 0;
        // 计算范围[l,r]上的异或和公式为t=pre[r]^pre[l-1];
        // 如果我们知道pre[]数组第k位上分别有几个1和几个0
        // 那么我们就得求得对于所有异或结果t，在第k位上为1的情况为cnt_0*cne_1个
        // 然后我们按位求和，第k位上共有cnt_0*cne_1个1相加，和为cnt_0*cne_1*2^k(k=0,1,...)
        // 这样可以避免累计 每个 子数组的异或和
        for (int i = 0; i <= n; ++i)
        {
            // 统计pre[]数组第k位上0和1的个数
            if ((pre[i] >> k) & 1) ++cnt1;
            else ++cnt0;
        }
        ans += cnt0 * cnt1 * (1LL << k);
    }
    cout << ans << '\n';
    return 0;
}