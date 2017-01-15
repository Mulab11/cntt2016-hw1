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
int n,d;
bool a[N][N];
int dis[N];
int q[N*N*N],inq[N];
int Main(){
    int ans=-1;
    rep(S,1,n){
        memset(dis,63,sizeof dis);
        memset(inq,0,sizeof inq);
        q[q[0]=1]=S;inq[S]=1;dis[S]=0;

        rep(i,1,q[0]){
            int x=q[i];
            rep(i,1,n)if(a[x][i])if(dis[x]+d<dis[i]){
                dis[i]=dis[x]+d;
                if(!inq[i]){
                    inq[i]=1;
                    q[++q[0]]=i;
                }   
            }
            inq[x]=0;
        }

        int ret=0;
        rep(i,1,n)ret=max(ret,dis[i]);
        if(ret<=n*2*d)ans=max(ans,ret);
    }
    return ans;
}
class Egalitarianism{
public:
    int maxDifference(vector<string> isFriend, int d){
        n=isFriend.size();
        ::d=d;
        rep(i,1,n)rep(j,1,n)a[i][j]=(isFriend[i-1][j-1]=='Y');
        return Main();
    }
};