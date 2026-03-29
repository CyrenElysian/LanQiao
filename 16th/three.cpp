# include <bits/stdc++.h>
using namespace std;

const int N=1e3+10;
int a[N],b[N],c[N]; // 记录数字
int one[N],two[N],three[N]; // 记录抽奖情况

void initial(int n)
{

    for(int i=1;i<=n;i++) cin>>a[i];
    a[0]=a[n];
    for(int i=1;i<=n;i++) cin>>b[i];
    b[0]=b[n];
    for(int i=1;i<=n;i++) cin>>c[i];
    c[0]=c[n];
}

int prize(int x,int y,int z)
{
    if (x==y && y==z) return 200;
    if (x+1==y && y+1==z) return 200;
    if (x==y || x==z || y==z) return 100;
    int maxval=max({x,y,z});
    int minval=min({x,y,z});
    int midval=(x+y+z)/3;
    if(maxval==minval+2 && midval==minval+1) return 100;
    return 0;
}

int main()
{
    int n;
    cin>>n;
    initial(n);

    int m;
    cin>>m;
    int cnt=1;
    int idx1=1,idx2=1,idx3=1;
    while(cnt<=m)
    {
        int x1, x2, x3;
        cin >> x1 >> x2 >> x3;
        idx1=(idx1+x1)%n;
        one[cnt]=a[idx1];
        idx2=(idx2+x2)%n;
        two[cnt]=b[idx2];
        idx3=(idx3+x3)%n;
        three[cnt]=c[idx3];
        cnt++;
    }

    int sum=0;
    for(int i=1;i<=m;i++)
    {
        sum+= prize(one[i],two[i],three[i]);
    }
    cout<<sum<<endl;

    return 0;
}

