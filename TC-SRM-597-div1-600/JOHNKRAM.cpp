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
    node operator-(const node& b)const
    {
        return node(x-b.x,y-b.y);
    }
    ll operator*(const node& b)const
    {
        return (ll)x*b.y-(ll)y*b.x;
    }
    bool operator<(const node& b)const
    {
        if(x==b.x)return y<b.y;
        return x<b.x;
    }
}a[55],b[200005];
map<node,int> m;
int n,i,j,k,N=100000,M;
double l[200005],r[200005],d;
class ConvexPolygonGame
{
    public:
        string winner(vector <int> X, vector <int> Y)
        {
            n=X.size();
            for(i=0;i<n;i++)m[a[i]=node(X[i],Y[i])]=1;
            a[n]=a[0];
            X.push_back(X[0]);
            Y.push_back(Y[0]);
            for(i=0;i<=N<<1;i++)
            {
                l[i]=1e15;
                r[i]=-1e15;
            }
            for(i=0;i<n;i++)if(X[i]==X[i+1])
            {
                l[X[i]+N]=min(l[X[i]+N],(double)min(Y[i],Y[i+1]));
                r[X[i]+N]=max(r[X[i]+N],(double)max(Y[i],Y[i+1]));
            }
            else for(j=min(X[i],X[i+1]),k=max(X[i],X[i+1]);j<=k;j++)
            {
                d=(double)((a[i]-node(j,0))*(a[i+1]-node(j,0)))/(X[i]-X[i+1]);
                l[j+N]=min(l[j+N],d);
                r[j+N]=max(r[j+N],d);
            }
            for(i=0;i<=N<<1;i++)for(j=ceil(l[i]);j<=r[i];j++)if(!m[node(i-N,j)])
            {
                b[M++]=node(i-N,j);
                if(M>200001)return "Masha";
            }
            for(i=2;i<M;i++)if((b[i]-b[0])*(b[i]-b[1]))return "Masha";
            return "Petya";
        }
};
