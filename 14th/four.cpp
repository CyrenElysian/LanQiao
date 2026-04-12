#include <bits/stdc++.h>
using namespace std;

// 遍历所有区间
const int N=5e3+10;
bool dp[N][N]; // dp[i][j]表示将区间[i,j]反转与原字符串比较的结果
               // true表示复合要求

int main()
{
    string s;
    cin>>s;
    long long ans=0;
    int n=s.size();
    for(int len=1;len<n;len++)
    {
        for(int l=0;l+len<n;l++)
        {
            int r=l+len;
            if(len==1)
            {
                if(s[l]>s[r]) dp[l][r]= true;
            }
            else
            {
                if(s[l]==s[r]) dp[l][r]=dp[l+1][r-1];
                else
                {
                    dp[l][r]=(s[l]>s[r] ? 1:0);
                }
            }
            if(dp[l][r]) ans++;
        }
    }
    cout<<ans;
}