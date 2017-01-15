#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long long LL;
const int N=55;
int D[N],S,T,n;
int dis[N];
int q[N];
int Main(){
    memset(dis,-1,sizeof dis);
    dis[S]=0;q[q[0]=1]=S;
    rep(i,1,q[0]){
        int x=q[i];
        rep(j,1,n)if(min(n-abs(j-x),abs(j-x))<=D[x])if(dis[j]==-1){
            dis[j]=dis[x]+1;q[++q[0]]=j;
        }
    }
    return dis[T];
}
class TravelOnMars{
public:
    int minTimes(vector <int> range, int S, int T){
        n=range.size();
        rep(i,1,n)D[i]=range[i-1];
        ::S=S+1;::T=T+1;
        return Main();
    }
};