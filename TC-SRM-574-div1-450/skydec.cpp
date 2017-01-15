#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
const int N=21;
int n;bool vis[N];
int a[N],m;
LL f[1<<18][19];
int sum[N];
LL Main(){
    int S=0;
    rep(i,1,m)S|=(1<<(a[i]-1));
    f[S][a[m]]=1;
    //显然每次选的2个点的中间只要都没被选就一定满足
    //所以采用状压dp，记录哪些点被选了
    rep(V,0,(1<<n)-1){
        //求前缀和，方便求是否全部被选
        rep(i,1,n)sum[i]=sum[i-1]+((V&(1<<(i-1)))>0);
        rep(i,1,n)if(f[V][i]){
            rep(j,1,n)if(!(V&(1<<(j-1)))){
                int d1=min(i,j);
                int d2=max(i,j);
                //只要区间[d1+1,d2-1]和区间[d2+1,d1-1]没有被选的数就行
                if(sum[d2-1]-sum[d1]==0)continue;
                if(sum[n]-sum[d2]+sum[d1-1]==0)continue;
                f[V|(1<<(j-1))][j]+=f[V][i];
            }
        }
    }
    //返回答案
    LL ans=0;
    rep(i,1,n)if((abs(i-a[1])!=1)&&(abs(i-a[1])!=n-1)){
        ans+=f[(1<<n)-1][i];
    }
    return ans;
}
class PolygonTraversal{
public:
    LL count(int n, vector<int> points){
        //预处理
        ::n=n;
        ::m=points.size();
        rep(i,1,points.size())a[i]=points[i-1];
        return Main();
    }
}gt;



