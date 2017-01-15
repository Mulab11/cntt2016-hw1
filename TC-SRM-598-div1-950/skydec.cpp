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
bool a[N][N];
int f[N];
int n;
void dfs(int x,int fa){
    bool hav=0;
    rep(i,1,n)if(a[i][x])if(i^fa){hav=1;dfs(i,x);}

    if(!hav)f[x]=0;

    rep(i,1,n)if(a[i][x])if(fa^i){
        int s=f[i];
        rep(j,1,n)if(i^j)if(j^fa)if(a[j][x])s+=max(1,f[j]);
        f[x]=min(f[x],s);
    }
}
int calc(int S){
    memset(f,63,sizeof f);
    dfs(S,0);
    return f[S]+1;
}
int Main(){
    if(n==1)return 0;
    int ans=1e9;
    rep(i,1,n)ans=min(ans,calc(i));
    return ans;
}
class TPS{
public:
    int minimalBeacons(vector <string> linked){
        n=linked.size();
        rep(i,1,n)rep(j,1,n)a[i][j]=(linked[i-1][j-1]=='Y');
        return Main();
    }
};