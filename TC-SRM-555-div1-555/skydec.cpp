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
const int P=555555555;
const int N=1605;
inline void add(int &a,int b){
    a+=b;if(a>=P)a-=P;
}
int C[N][N];
int f[N][N];
class XorBoard{
    public:
    int count(int n,int m,int nc,int mc,int s){
        int ans=0;
        //预处理组合数
        rep(i,0,1600){
            C[i][0]=C[i][i]=1;
            rep(j,1,i-1){
                C[i][j]=(C[i-1][j-1]+C[i-1][j])%P;
            }
        }
        f[1][0]=1;
        //f[i][j]表示前i行，一共加了j次的方案数
        rep(i,1,1600)rep(j,0,1600){
            add(f[i+1][j],f[i][j]);
            add(f[i][j+1],f[i][j]);
        }
        //rep(i,1,1600)rep(j,1,1600)
        //add(f[i][j],f[i][j-1]);
        rep(i,0,n)if(i<=nc)rep(j,0,m)if(j<=mc){
            //如果翻了i行和j列，1的个数显然是i*m+j*n-2*i*j
            int ct=i*m+n*j-2*i*j;
            if(s!=ct)continue;
            
            //因为是恰好nc次和恰好mc次，所以剩下的次数一定要是偶数次，不然肯定会有多余的行被变
            if((nc-i)&1)continue;
            if((mc-j)&1)continue;
            //这样剩余的次数相当于是给某些行+2
            //根据之前预处理的f计算即可
            int ret=C[n][i]*1ll*f[n][(nc-i)/2]%P;
            ret=ret*1ll*C[m][j]%P;
            ret=ret*1ll*f[m][(mc-j)/2]%P;
            add(ans,ret);
        }
        return ans;
    }
}gt;




