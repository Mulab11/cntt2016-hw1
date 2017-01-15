#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long long LL;
const int N=305;
const int P=1000000009;
inline void add(int &a,int b){a+=b;if(a>=P)a-=P;}
inline void dec(int &a,int b){a-=b;if(a<0)a+=P;}
int a[N],n,M,L,A,B;
int sum[N];
int f[N][N][3];
int Main(){
    //sum记录水滴数量的前缀和
    rep(i,1,n)sum[i]=sum[i-1]+a[i];
    f[0][0][0]=1;
    //f[i][j][k]表示到了[1,i]，放了j个板子，当前状态是k
    //k的含义如下：
    //k=0:第i格没有板子
    //k=1:前面一堆板子的联通块没有有效长度为L的
    //k=2:前面一堆板子的联通块有有效长度为L的
    rep(i,0,n-1)rep(j,0,M){
        //第i+1格不放，直接把状态归0
        //当然，如果状态为1的话，说明这一段还不合法，不能归0
        add(f[i+1][j][0],f[i][j][0]);
        add(f[i+1][j][0],f[i][j][2]);
        for(int k=i+1;k<=i+L&&k<=n;k++)if(sum[k]-sum[i]>=A)if(sum[k]-sum[i]<=B){
            //枚举有效长度，check下水滴数量之和
            rep(v,0,2){
                int dv=v;
                //更新状态
                if(k-i==L)dv=2;
                else if(!dv)dv=1;
                add(f[k][j+1][dv],f[i][j][v]);
            }
        }
    }
    int ans=f[n][M][2];
    //注意，状态为0的也得累加到答案内
    add(ans,f[n][M][0]);
    return ans;
}
class TheExperiment{
public:
    int countPlacements(vector <string> v, int M, int L, int A, int B){
        //预处理
        rep(i,0,v.size()-1)rep(j,0,v[i].size()-1)a[++n]=v[i][j]-'0';
        ::M=M;::L=L;::A=A;::B=B;
        return Main();
    }
};





