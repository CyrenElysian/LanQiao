#include <bits/stdc++.h>
using namespace std;

int chess[6][6];
int ans=0;

void check()
{
    int a = 0;
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 5; j++)
        {
            if (chess[i][j] == 0) a++; // 0为白棋
        }
    }
    if (a != 13) return;

    int sum = 0;
    for (int i = 1; i <= 5; i++) // 行
    {
        sum=0;
        sum += chess[i][1] + chess[i][2] + chess[i][3] + chess[i][4] + chess[i][5];
        if(sum%5==0) return;
    }

    for (int i = 1; i <= 5; i++) // 列
    {
        sum=0;
        sum += chess[1][i] + chess[2][i] + chess[3][i] + chess[4][i] + chess[5][i];
        if(sum%5==0) return;
    }

    // 斜线
    sum=0;
    sum+=chess[1][1]+chess[2][2]+chess[3][3]+chess[4][4]+chess[5][5];
    if(sum%5==0) return;
    sum=0;
    sum+=chess[5][1]+chess[4][2]+chess[3][3]+chess[2][4]+chess[1][5];
    if(sum%5==0) return;

    ans++;
}

void dfs(int num) // num 0~24
{
    if(num==25)
    {
        check();
        return;
    }

    int row=num/5+1;
    int column=num%5+1;

    chess[row][column]=0;
    dfs(num+1);
    chess[row][column]=1;
    dfs(num+1);
}

int main()
{
    memset(chess,-1,sizeof chess);
    dfs(0);
    cout<<ans<<endl;
    return 0;
}