#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long long LL;
const int N=2600;
const int P=1000000007;
inline int Pow(int a,int b){
    int c=1;
    for(;b;b>>=1,a=a*1ll*a%P)if(b&1)c=c*1ll*a%P;
    return c;
}
inline void add(int &a,int b){a+=b;if(a>=P)a-=P;}
inline void dec(int &a,int b){a-=b;if(a<0)a+=P;}
int x[N],y[N],n;
int head[N],np[N*N],p[N*N],tot;
int f[2];
int q[N],vis[N];
void dfs(int x){
    //求联通块
    vis[x]=1;
    q[++q[0]]=x;
    for(int u=head[x];u;u=np[u])if(!vis[p[u]])dfs(p[u]);
}
int Main(){
    f[0]=1;
    rep(i,1,n)if(!vis[i]){
        q[0]=0;
        //搜出联通块
        dfs(i);
        //根据联通块个数的奇偶性背包
        //因为只关心是奇数还是偶数，所以在%2下做
        if(q[0]&1){
            int sum=(f[0]+f[1])%P;
            f[0]=f[1]=sum;
        }
        else{
            f[0]=f[0]*2%P;
            f[1]=f[1]*2%P;
        }
    }
    dec(f[0],1);
    return f[0];
}
class GooseInZooDivOne{
public:
    int count(vector <string> field, int dist){
        //预处理
        rep(i,0,field.size()-1)rep(j,0,field[0].size()-1)
        if(field[i][j]=='v'){
            ++n;x[n]=i;y[n]=j;
        }
        rep(i,1,n)rep(j,1,n)if(abs(x[i]-x[j])+abs(y[i]-y[j])<=dist){
            ++tot;p[tot]=j;np[tot]=head[i];head[i]=tot;
        }
        return Main();
    }
};


