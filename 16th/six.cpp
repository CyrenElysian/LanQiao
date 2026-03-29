# include <bits/stdc++.h>
using namespace std;

const int N=1e5+10;
int s[N];
bool very_good[N][N]; // 连续非递减子串

bool good_str(int begin,int end)
{
    if(begin==end || begin+1==end) return true;

    int chance=2;
    for(int i=begin,j=begin;j<=end;j++)
    {
        if(very_good[i][j]) continue;
        else if(s[j]==s[i] || s[j]==s[i]+1)
        {
            very_good[i][j]= true;
            continue;
        }
        else
        {
            very_good[i][j]= false;
            chance--;
            if(chance==0) return false;
            i=j;
        }
    }
    return true;
}

int main()
{
    string str;
    cin>>str;
    int n=str.size();
    for(int i=1;i<=n;i++)
    {
        s[i]=str[i-1]-'0';
        very_good[i][i]= true;
    }

    int ans=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=i;j<=n;j++)
        {
            if(good_str(i,j))
            {
                cout<<i<<j<<" ";
                ans++;
            }
        }
    }


    cout<<ans<<endl;
    return 0;
}