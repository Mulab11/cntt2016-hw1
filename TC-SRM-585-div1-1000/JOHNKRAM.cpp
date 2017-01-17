#include<bits/stdc++.h>
using namespace std;
#define ll long long
struct node
{
    int x,y;
    node(int _x=0,int _y=0)
    {
        x=_x;
        y=_y;
    }
    node operator+(const node& b)const
    {
        return node(x+b.x,y+b.y);
    }
    node operator-(const node& b)const
    {
        return node(x-b.x,y-b.y);
    }
    ll operator*(const node& b)const
    {
        return (ll)x*b.y-(ll)y*b.x;
    }
}a[300005],b[100];
int n,N,i,j,k,o,l[300005],r[300005];
ll s[300005],ans;
bool ask(node x,node y)
{
    for(int i=0;i<n;i++)if((y-x)*(b[i]-x)<0)return 0;
    return 1;
}
class EnclosingTriangle
{
    public:
        long long getNumber(int m, vector <int> x, vector <int> y)
        {
            n=x.size();
            for(i=0;i<n;i++)b[i]=node(x[i],y[i]);
            for(i=0;i<m;i++)a[N++]=node(i,0);
            for(i=0;i<m;i++)a[N++]=node(m,i);
            for(i=0;i<m;i++)a[N++]=node(m-i,m);
            for(i=0;i<m;i++)a[N++]=node(0,m-i);
            for(i=j=N-1;~i;i--)
            {
                for(;ask(a[j],a[i]);j=(j+N-1)%N);
                l[i]=(i-j+N-1)%N;
            }
            for(i=j=0;i<N;i++)
            {
                for(;ask(a[i],a[j]);j=(j+1)%N);
                r[i]=(j-i+N-1)%N;
            }
            for(i=0;i<N;i++)s[i+1]=s[i]+l[i];
            for(i=0;i<N;i++)
            {
                j=(i-l[i]+N)%N;
                k=(i+r[i])%N;
                if(l[i]+r[i]+l[j]<N)continue;
                if(j==k)ans-=3;
                o=(k+r[k])%N;
                if(j<=o)ans+=s[o+1]-s[j];
                else ans+=s[N]-s[j]+s[o+1];
                j=(j-k+N)%N;
                k=r[k];
                ans-=(ll)(j+k-2)*(k-j+1)>>1;
            }
            return ans/3;
        }
};
