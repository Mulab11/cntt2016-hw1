#include<bits/stdc++.h>
using namespace std;
struct node
{
    int x,y;
    node(int _x=0,int _y=0)
    {
        x=_x;
        y=_y;
    }
    node operator-(const node& b)const
    {
        return node(x-b.x,y-b.y);
    }
    int operator*(const node& b)const
    {
        return x*b.y-y*b.x;
    }
}a[55];
int n,i,j,k;
double l,ans;
class Constellation
{
    public:
        double expectation(vector <int> x, vector <int> y, vector <int> prob)
        {
            n=x.size();
            for(i=0;i<n;i++)
            {
                a[i].x=x[i];
                a[i].y=y[i];
            }
            for(i=0;i<n;i++)for(j=0;j<n;j++)if(i!=j)
            {
                for(k=0,l=1;k<n;k++)if(k!=i&&k!=j&&((a[j]-a[i])*(a[k]-a[i])>0||!((a[j]-a[i])*(a[k]-a[i]))&&x[k]>=min(x[i],x[j])&&x[k]<=max(x[i],x[j])&&y[k]>=min(y[i],y[j])&&y[k]<=max(y[i],y[j])))l*=1-prob[k]*1e-3;
                ans+=l*(a[j]*a[i])*1e-6*prob[i]*prob[j];
            }
            return ans/2;
        }
};
