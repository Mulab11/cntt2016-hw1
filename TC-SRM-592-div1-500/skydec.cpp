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
const int P=1000000007;
inline int Pow(int a,int b){
    int c=1;
    for(;b;b>>=1,a=a*1ll*a%P)if(b&1)c=c*1ll*a%P;
    return c;
}
inline void add(int &a,int b){a+=b;if(a>=P)a-=P;}
inline void dec(int &a,int b){a-=b;if(a<0)a+=P;}
int n,k;
int f[2][N*N][N];
int Main(){
    int now=0;
    f[now][0][0]=1;
    rep(i,1,n){
        memset(f[now^1],0,sizeof f[now^1]);
        rep(j,0,n*n)rep(l,0,i-1)if(f[now][j][l]){
            int val=f[now][j][l];
            if(l){
                add(f[now^1][2*i+j][l-1],val*1ll*l*l%P);
                add(f[now^1][i+j][l],val*2ll*l%P);
            }
            add(f[now^1][j][l+1],val);
            add(f[now^1][j+i][l],val);
        }
        now^=1;
    }
    int ans=0;
    rep(i,k,n*n)add(ans,f[now][i][0]);
    rep(i,1,n)ans=ans*1ll*i%P;
    return ans;
}
class LittleElephantAndPermutationDiv1{
public:
    int getNumber(int n, int K){
        ::n=n;::k=K;
        return Main();
    }
};