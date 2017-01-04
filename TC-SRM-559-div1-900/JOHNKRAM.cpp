#include<bits/stdc++.h>
using namespace std;
#define pdd pair<double,double>
#define pb push_back
#define mp make_pair
#define f first
#define s second
const double PI=acos(-1.0);
int n;
vector<pdd > A;
struct node//点和线段 
{
    double x,y;
    node(double _x=0,double _y=0)
    {
        x=_x;
        y=_y;
    }
    node operator+(node b)
    {
        return node(x+b.x,y+b.y);
    }
    node operator-(node b)
    {
        return node(x-b.x,y-b.y);
    }
    double operator*(node b)//点积 
    {
        return x*b.x+y*b.y;
    }
    double dis()//模长的平方 
    {
        return (*this)*(*this);
    }
    double ang()//角度 
    {
        return atan2(y,x);
    }
};
struct circle//圆 
{
    node o;
    double r;
    circle(node _o=node(),double _r=0)
    {
        o=_o;
        r=_r;
    }
    node operator-(circle b)
    {
        return b.o-o;
    }
}a[55];
bool work(circle a,circle b,double &x,double &y)//求两圆交点关于第一个圆圆心的角度并判断两圆是否相交 
{
    double A=(b-a).ang(),B=(a.r*a.r+(b-a).dis()-b.r*b.r)/2/a.r/sqrt((b-a).dis());
    if(B<=-1||B>=1)return 0;
    B=acos(B);
    x=A-B;
    y=A+B;
    return 1;
}
void add(double l,double r)//插入一个角度区间 
{
    if(l<-PI)
    {
        A.pb(mp(l+2*PI,PI));
        l=-PI;
    }
    if(r>PI)
    {
        A.pb(mp(-PI,r-2*PI));
        r=PI;
    }
    A.pb(mp(l,r));
}
bool check(double x)//判断最优解是否>=x 
{
    A.clear();
    int i,m;
    double d0,d1,y,l,r;
    for(i=1;i<n;i++)
    {
        d0=(a[i].o-a[0].o).dis()-a[0].r*a[0].r;
        d1=x+a[i].r;
        if(d1*d1<d0)//直着走 
        {
            if(work(a[0],circle(a[i].o,d1),l,r))add(l,r);
        }
        else//从圆上绕 
        {
            work(a[0],circle(a[i].o,y=sqrt(d0)),l,r);
            y=(d1-y)/a[0].r;
            if(r+2*y>=l+2*PI)return 0;
            add(l-y,r+y);
        }
    }
    sort(A.begin(),A.end());
    for(m=A.size(),i=0,y=-PI;i<m;i++)//判断是否全覆盖 
    {
        if(A[i].f>y)return 1;
        y=max(y,A[i].s);
    }
    return y<PI;
}
class CircusTents
{
    public:
        double findMaximumDistance(vector <int> x, vector <int> y, vector <int> r)
        {
            n=x.size();
            int i;
            for(i=0;i<n;i++)a[i]=circle(node(x[i],y[i]),r[i]);//圆格式转换 
            double L,R,M;
            L=0;
            R=1000000;
            for(i=0;i<100;i++)if(check(M=(L+R)/2))L=M;//二分求解 
            else R=M;
            return L;
        }
};