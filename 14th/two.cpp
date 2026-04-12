#include<bits/stdc++.h>
using namespace std;

// dp[i][j] 回答i题获得j分(j=0,1,...10)
// dp[i][j]=dp[i-1][j-1] i>=1,j>=1
// dp[i][0]=dp[i-1][1]+...+dp[i-1][9]
// 初始化dp[0][0]=1;

long long dp[40][20];
long long ans=0;
int main()
{
    dp[0][0]=1;
    // for(int i=1;i<=9;i++) dp[i][i]=1; 动态规划中要避免递推过程重复计算
    for(int i=1;i<=30;i++)
    {
        // 答对
        for(int j=1;j<=9;j++)
        {
            dp[i][j]+=dp[i-1][j-1];
        }

        // 答错
        for(int j=0;j<=9;j++)
        {
            dp[i][0]+=dp[i-1][j];
        }
    }
    for(int i=7;i<=30;i++)
    {
        ans+=dp[i][7];
    }
    cout<<ans<<endl;
}