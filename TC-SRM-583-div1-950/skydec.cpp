#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<map>
#include<string>
#define pb push_back
#include<vector>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
typedef double db;
const int N=145;
int a[N][N],n,m;
int b[N][N];
int lie[N];
long double g[2][1410];
double Main(){
    int sum=0;
    if(n>m){
        rep(i,1,n)rep(j,1,m)b[i][j]=a[i][j];
        rep(i,1,n)rep(j,1,m)a[j][i]=b[i][j];
        swap(n,m);
    }
    rep(i,1,n)rep(j,1,m)sum+=a[i][j];
    double ans=0;
    rep(sth,0,(1<<n)-1){
        memset(lie,0,sizeof lie);
        
        int base=-1;
        int pre=0;
        rep(i,1,n)rep(j,1,m)
        if(!(sth&(1<<(i-1))))lie[j]+=a[i][j];else pre+=a[i][j];
        rep(i,1,n)if(sth&(1<<(i-1)))base*=-1;
        
        memset(g,0,sizeof g);
        g[0][0]=1;
        rep(j,1,m)per(k,sum,lie[j]){
            int v=g[0][k-lie[j]];
            int u=g[1][k-lie[j]];
            g[1][k]+=v;g[0][k]+=u;
        }
        
        rep(k,0,sum-1)rep(ji,0,1)if(g[ji][k]>=0){
            double ret=0;
            ret=g[ji][k]*1.*sum/(1.*(sum-k));
            ret*=base;
            if((m-ji)&1)ret*=-1;
            ans+=ret;
        }
    }
    return ans;
}
class RandomPaintingOnABoard{
    public:
    double expectedSteps(vector<string> _a){
        n=_a.size();m=_a[0].size();
        rep(i,1,n)rep(j,1,m)a[i][j]=_a[i-1][j-1]-'0';
        return Main();
    }
}gt;