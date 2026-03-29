# include <bits/stdc++.h>
using namespace std;

const int N=1e5+10;
typedef pair<double,double> PDD;
vector<PDD> interval_merged;
const double pi=acos(-1);


struct interval
{
    double l,r;
    bool operator< (const interval & i)const
    {
        return l<i.l;
    }
}intervals[N];

interval failure(int x,int y,int r)
{
    double d= sqrt(x*x+y*y);
    double alpha=asin(r/d); // 需注意r>d的情况
    double theta=atan2(y,x);
    double angle1=theta-alpha;
    double angle2=theta+alpha;
    return {angle1,angle2}; //
}


void merge(int n)
{
    sort(intervals,intervals+n);
    double left=intervals[0].l;
    double right=intervals[0].r;
    for(int i=0;i<n;i++)
    {
        if(intervals[i].l<=right)
            right=max(right,intervals[i].r);
        else
        {
            interval_merged.push_back({left,right});
            left=intervals[i].l;
            right=intervals[i].r;
        }
    }
    interval_merged.push_back({left,right}); // 拼接剩余区间
}

double interval_length()
{
    double length=0;
    for(auto &i :interval_merged)
    {
        length+=(i.second-i.first);
    }
    return length;
}

int main()
{
    int n;
    cin>>n;

    for(int i=0;i<n;i++)
    {
        int x,y,r;

        cin>>x>>y>>r;
        if(r>=sqrt(x*x+y*y))
        {
            printf("0.000\n");
        }
        intervals[i]= failure(x,y,r);
    }

    merge(n);

    printf("%.3lf\n",1-interval_length()/(pi/2));

    return 0;
}