#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
const int N=1010000;
typedef long long LL;
bool is[N];
int org[N];
int t[N];
int f[N];
int sg[N];
int pre[N];
class TheDivisionGame{
public:
    LL countWinningIntervals(int L, int R){
        int S=100000;
        int n=R-L+1;
        rep(i,1,n)org[i]=L-1+i;
        //筛质因子，复杂度是RlogR-LlogL约等于(R-L)logR
        //显然答案只跟质因子的指数的和有关，只要记这个即可
        rep(i,2,S)if(!is[i]){
            for(int j=i;j<=S;j+=i)is[j]=1;
            for(int j=(L/i)*i;j<=R;j+=i)if(j>=L){
                while(org[j-L+1]%i==0){
                    org[j-L+1]/=i;
                    t[j-L+1]++;
                }
            }
        }
        //注意处理大质因子的情况
        rep(i,1,n)if(org[i]>1)t[i]++;

        //暴力计算sg值
        rep(i,1,30){
            rep(j,1,i){
                sg[f[i-j]]=i;
            }
            f[i]=0;
            while(sg[f[i]]==i)f[i]++;
        }
        int now=0;
        pre[0]++;
        //考虑补集转化，减去xor起来为0的
        //开个数组记xor值即可
        LL ans=n*1ll*(n+1)/2;
        rep(i,1,n){
            now^=f[t[i]];
            ans-=pre[now];
            pre[now]++;
        }
        return ans;
    }
};


