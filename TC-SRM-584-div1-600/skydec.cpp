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
int n,k;
bool hav[N];
vector<int> gt[N];
int tmp[N],M;
LL f[2][N][N][N];
//f[][has k][down][up]
LL g[N][N];
LL Main(){
    rep(i,1,50)rep(j,0,gt[i].size()-1)tmp[++M]=gt[i][j];
    sort(tmp+1,tmp+1+M);
    M=unique(tmp+1,tmp+1+M)-tmp-1;
    rep(i,1,50)rep(j,0,gt[i].size()-1)gt[i][j]=lower_bound(tmp+1,tmp+1+M,gt[i][j])-tmp;

    int now=0;
    f[now][0][0][M]=1;
    rep(col,1,50)if(gt[col].size()){
        memset(f[now^1],0,sizeof f[now^1]);
        memset(g,0,sizeof g);
        g[0][M]=1;
        rep(i,0,gt[col].size()-1){
            int d=gt[col][i];
            per(j,k,0)rep(dj,0,M)
            g[j+1][min(dj,d)]+=g[j][dj];
        }
        if(!hav[col]){
            rep(i,0,k)rep(j,0,M)rep(l,0,M)if(f[now][i][j][l]){
                rep(t,1,gt[col].size())rep(d,0,M)if(g[t][d])if(t+i<=k)
                f[now^1][i+t][j][min(l,d-1)]+=g[t][d]*f[now][i][j][l];
                f[now^1][i][j][l]+=f[now][i][j][l];
            }
        }
        else{
            rep(i,0,k)rep(j,0,M)rep(l,0,M)if(f[now][i][j][l]){
                rep(t,1,gt[col].size())rep(d,0,M)if(g[t][d])if(t+i<=k)
                f[now^1][i+t][max(j,d)][l]+=g[t][d]*f[now][i][j][l];
            }
        }
        now^=1;
    }
    LL ans=0;
    rep(l,0,M)rep(r,l,M)ans+=f[now][k][l][r];
    return ans;
}
class Excavations{
public:
    LL count(vector<int> kind,vector<int> depth,vector<int> found,int K){
        n=kind.size();
        rep(i,1,n){
            gt[kind[i-1]].push_back(depth[i-1]);
        }
        rep(i,0,found.size()-1)hav[found[i]]=1;
        ::k=K;
        return Main();
    }
};