#include <bits/stdc++.h>
using namespace std;

vector<int> division(vector<int> &a,int b,int &r)
{
    vector<int> c;
    r=0;

    for(int i=a.size()-1;i>=0;i--)
    {
        r=r*10+a[i];
        c.push_back(r/b);
        r%=b;
    }
    reverse(c.begin(),c.end());
    // 翻转方便去0
    while(c.size()>1 && c.back()==0) c.pop_back();
    return c;
}

int main()
{
    string a;
    vector<int> A;
    int b;
    cin>>a>>b;
    for(int i=a.size()-1;i>=0;i--) A.push_back(a[i]-'0');
    int r=0;
    auto c=division(A,b,r);
    for(int i=c.size()-1;i>=0;i--) cout<<c[i];
    cout<<endl;
    cout<<r<<endl;
    return 0;
}