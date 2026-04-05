// 暂存，未学习
#include <iostream>
using namespace std;

long long a[100005], b[100005], c[100005];
// a[x]: 数值x的出现次数
// b[x]: x的严格倍数的出现次数（不包括x本身）
// c[x]: x的严格因数的出现次数（不包括x本身）

int main() {
    int n, x, ub = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x;
        a[x]++;
        ub = max(ub, x);
    }
    // 预处理倍数和因数关系
    for (int i = 1; i <= ub; i++) {
        for (int j = i + i; j <= ub; j += i) {
            b[j] += a[i];   // j的严格因数个数
            c[i] += a[j];   // i的严格倍数个数
        }
    }
    long long ans1 = 0, ans2 = 0;
    // 枚举所有数值对 (i, j) 满足 i|j 且 i<j
    for (int i = 1; i <= ub; i++) {
        if (a[i] == 0) continue;
        for (int j = i + i; j <= ub; j += i) {
            // 这里累加各种情况，具体推导参见官方题解
            ans1 += a[i] * a[j];   // 所有有序对 (i,k) 满足数值 i|j 且 i≠j
            // 以下为各种重复情况的修正项
            ans2 += a[j] * a[i] * b[i] * 2;        // case 1
            ans2 += a[i] * a[j] * (c[i] - a[j]);   // case 2
            ans2 -= a[i] * a[i] * a[j];            // case 3-2
            ans2 += a[i] * a[j] * (a[i] - 1) / 2 * 10; // case 6
            ans2 += a[i] * a[j] * (a[j] - 1) / 2 * 10; // case 7
        }
        // 处理相同数值的情况
        ans1 += a[i] * (a[i] - 1);   // 相同数值不同下标的有序对 (i,k)
        ans2 += a[i] * b[i] * b[i];  // case 3-1
        ans2 += a[i] * (a[i] - 1);   // case 4
        ans2 += a[i] * (a[i] - 1) * (a[i] - 2) / 6 * 24; // case 5
    }
    // 最终答案 = ans1^2 - ans1 - ans2
    cout << ans1 * ans1 - ans1 - ans2 << '\n';
    return 0;
}