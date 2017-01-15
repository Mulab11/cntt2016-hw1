#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long long LL;
const int N=2505*2505;
int Sqrt[N];
int x[20005],y[20005],dis[20005];
int m=0;
class FindPolygons{
public:
    double minimumPolygon(int L){
        if(L==2)return -1;
        if(L&1)return -1;

        memset(Sqrt,-1,sizeof Sqrt);

        for(int i=0;i*i<N;i++)Sqrt[i*i]=i;

        int ans=1e9;

        rep(i,0,L)rep(j,0,L)if(i||j){
            int dj=i*i+j*j;
            if(dj>=N)continue;
            if(Sqrt[dj]==-1)continue;
            if(2*Sqrt[dj]<L){
                ++m;x[m]=i;y[m]=j;dis[m]=Sqrt[dj];
            }
        }
        rep(i,1,m)rep(j,i+1,m){
            int d2=(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);
            if(d2>=N)continue;
            if(Sqrt[d2]==-1)continue;
            d2=Sqrt[d2];
            if(d2+dis[i]+dis[j]==L){
                ans=min(ans,max(dis[i],max(dis[j],d2))-min(dis[i],min(dis[j],d2)));
            }
        }
        if(ans>L)return (L/2)&1;
        else return ans;
    }
};