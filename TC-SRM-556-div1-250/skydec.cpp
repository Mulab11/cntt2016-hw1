#include<stdio.h>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<ctime>
#include<set>
#include<map>
#include<string>
#include<vector>
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define SZ(x) ((int)((x).size()))
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
typedef double DB;
const DB pi=acos(-1.0);
const int N=55;
int w[N];
bool a[N][N];
int n;
pii q[N*1100];
bool vis[N][1100];
int t;
int Main(){
    int ans=0;
    //vis[i][j]表示是否有走到i，路径xor为j
    //考虑bfs
    q[t=1]=pii(1,w[1]);
    vis[1][w[1]]=1;
    rep(i,1,t){
        int x=q[i].fi;
        int v=q[i].se;
        //边搜边更新答案
        ans=max(ans,v);
        rep(j,1,n)if(a[x][j])if(!vis[j][v^w[j]]){
            //枚举出边，把新的方案入栈
            q[++t]=pii(j,v^w[j]);
            vis[j][v^w[j]]=1;
        }
    }
    return ans;
}
class XorTravelingSalesman{
    public:
    int maxProfit(vector<int> w,vector<string> roads){
        //预处理
        n=w.size();
        rep(i,1,n)::w[i]=w[i-1];
        rep(i,1,n)rep(j,1,n)
        a[i][j]=(roads[i-1][j-1]=='Y');
        return Main();
    }
};






