#include<bits/stdc++.h>
using namespace std;
const double PI=acos(-1.0);
struct node
{
    double r,i;
    node(double _r=0,double _i=0)
    {
        r=_r;
        i=_i;
    }
    node operator+(const node& y)const
    {
        return node(r+y.r,i+y.i);
    }
    node operator-(const node& y)const
    {
        return node(r-y.r,i-y.i);
    }
    node operator*(const node& y)const
    {
        return node(r*y.r-i*y.i,y.r*i+r*y.i);
    }
    node H()
    {
        double a=atan2(i,r)/2,d=sqrt(sqrt(i*i+r*r));
        return node(d*cos(a),d*sin(a));
    }
}w[55],a[55],b[55];
int n,m,i,j,k,l,d[55];
vector<int> ans,x;
void DFT(node *a)
{
    int i,j;
    node t[55];
    for(i=0;i<n;i++)t[i]=a[i];
    for(i=0;i<n;i++)for(a[i]=node(),j=0;j<n;j++)a[i]=a[i]+t[j]*w[i*j%n];
}
class SplittingFoxes2
{
    public:
        vector <int> getPattern(vector <int> amount)
        {
            n=amount.size();
            m=n+2>>1;
            for(i=0;i<n;i++)w[i]=node(cos(2*PI*i/n),sin(2*PI*i/n));
            for(i=0;i<n;i++)a[i].r=(double)amount[i]/n/n;
            DFT(a);
            for(i=0;i<n;i++)a[i]=a[i].H();
            for(i=0;i<n;i++)w[i].i=-w[i].i;
            for(i=0;i<1<<m;i++)
            {
                for(j=0;j<n;j++)if(i>>min(j,n-j)&1)b[j]=node()-a[j];
                else b[j]=a[j];
                DFT(b);
                for(j=0;j<n;j++)d[j]=max(0.0,b[j].r+0.45);
                for(j=1;j<n;j++)if(d[j]!=d[n-j])break;
                if(j<n)continue;
                for(j=0;j<n;j++)
                {
                    for(k=l=0;k<n;k++)l+=d[k]*d[(j-k+n)%n];
                    if(l!=amount[j])break;
                }
                if(j<n)continue;
                x.clear();
                for(j=0;j<n;j++)x.push_back(d[j]);
                if(ans.empty()||x<ans)ans=x;
            }
            if(ans.empty())ans.push_back(-1);
            return ans;
        }
};
