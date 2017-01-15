#include<cstdio>
#include<cstring>
#include<algorithm>
#include<string>
#define pb push_back
#include<set>
#include<map>
#include<vector>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
typedef double db;
int n;
const int N=110;
int tot;
int id[N][N];int root;
vector<int>hui[N],hw[N];
void build(string a){
    rep(i,1,n)rep(j,0,9)id[i][j]=++tot;
    root=++tot;
    for(int i=0;i<a.size();i+=12){
        int x=a[i]-'A'+1;
        int y=a[i+4]-'A'+1;
        int lx=a[i+1]-'0';
        int ly=a[i+5]-'0';
        int _w=0;
        rep(j,i+7,i+10)_w*=10,_w+=a[j]-'0';
        rep(j,lx,9){
            hui[id[y][ly]].pb(id[x][j]);
            hw[id[y][ly]].pb(_w);
        }
    }
    rep(i,1,n){
        hui[id[i][0]].pb(root);
        hw[id[i][0]].pb(0);
    }
}
int f[N][1<<10];
int q[N*15];bool inq[N];
int Main(string info){
    build(info);
    memset(f,63,sizeof f);
    rep(i,1,n)f[id[i][9]][1<<(i-1)]=0;
    rep(i,1,tot)f[i][0]=0;
    
    rep(T,0,(1<<n)-1){
        rep(i,1,tot){
            for(int S=T;S;S=(S-1)&T)
            f[i][T]=min(f[i][T],f[i][S]+f[i][S^T]);
        }
        memset(inq,0,sizeof inq);q[0]=0;
        rep(i,1,tot){
            q[++q[0]]=i;
            inq[i]=1;
        }
        rep(i,1,q[0]){
            int x=q[i];
            rep(i,0,hui[x].size()-1){
                int y=hui[x][i];
                int _w=hw[x][i];
                if(f[y][T]>f[x][T]+_w){
                    f[y][T]=f[x][T]+_w;
                    if(!inq[y]){
                        inq[y]=1;
                        q[++q[0]]=y;
                    }
                }
            }
            inq[x]=0;
        }
    }
    
    if(f[root][(1<<n)-1]>1e8)return -1;
    return f[root][(1<<n)-1];
}
class FoxTheLinguist{
    public:
    int minimalHours(int _n, vector<string> info){
        string str="";
        rep(i,0,info.size()-1)str=str+info[i];
        n=_n;
        return Main(str);
    }
};