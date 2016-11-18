#include<bits/stdc++.h>
using namespace std;
#define P 1000000007
#define ll long long
int Pow(int a,int b)
{
    int s=1;
    for(;b;b>>=1,a=(ll)a*a%P)if(b&1)s=(ll)s*a%P;
    return s;
}
int n,m,i,j,k,l,o,c[1300][55],f[55][1300],ans;
int F(int N,int M)//判断有没有超过范围，没有就返回N个点M条边的连通图个数 
{
    if(N<1||M<N-1||M>min(N*(N-1)/2,m))return 0;
    return f[N][M];
}
int C(int N,int M)//判断有没有超过范围，没有就返回N!/M!/(N-M)! 
{
    if(M<0||M>N)return 0;
    return c[N][M];
}
class KingdomAndCities
{
    public:
        int howMany(int N, int M, int K)
        {
            n=N;
            m=K;
            if(m<n-1||m>n*(n-1)/2||M&&m<M+1||n==M)return 0;//特判 
            for(i=c[0][0]=1;i<=max(n,n*(n-1)/2);i++)for(j=c[i][0]=1;j<=min(i,max(n,m));j++)//计算组合数 
            {
                c[i][j]=c[i-1][j]+c[i-1][j-1];
                if(c[i][j]>=P)c[i][j]-=P;
            }
            for(i=1;i<=n;i++)for(j=i-1;j<=min(i*(i-1)/2,m);j++)for(f[i][j]=c[i*(i-1)/2][j],k=1;k<i;k++)for(l=k-1;l<=min(k*(k-1)/2,j);l++)f[i][j]=(f[i][j]-(ll)F(k,l)*C((i-k)*(i-k-1)/2,j-l)%P*C(i-1,k-1)%P+P)%P;//计算连通图个数 
            if(!M)return f[n][m];//M=0
            if(M==1)//M=1
            {
                for(ans=(ll)F(n-1,m-2)*(n-1)*(n-2)/2%P,i=1;i<=n-2;ans=(ans+(ll)C(n-2,i-1)*i*(n-i-1)%P*k)%P,i++)for(j=i-1,k=0;j<=min(i*(i-1)/2,m-2);j++)k=(k+(ll)F(i,j)*F(n-1-i,m-2-j))%P;//枚举删掉1号点之后2号点所在连通块的大小 
                return ans;
            }
            //M=2
            for(ans=(ll)F(n-2,m-3)*(n-2)*(n-2)%P,i=1;i<=n-3;ans=(ans+(ll)C(n-3,i-1)*k%P*i*(n-i-2)*2)%P,i++)for(j=i-1,k=0;j<=min(i*(i-1)/2,m-3);j++)k=(k+(ll)F(i,j)*F(n-2-i,m-3-j))%P;//1、2之间连了边 
            //1、2之间没有连边 
            for(ans=(ans+(ll)F(n-2,m-4)*(n-2)*(n-2)*(n-3)*(n-3)/4)%P,i=1;i<=n-3;ans=(ans+(ll)C(n-3,i-1)*k%P*((n-2)*(n-2)*(n-3)*(n-3)/4-(i*(i-1)/2+(n-i-2)*(n-i-3)/2)*(i*(i-1)/2+(n-i-2)*(n-i-3)/2)))%P,i++)for(j=i-1,k=0;j<=min(i*(i-1)/2,m-4);j++)k=(k+(ll)F(i,j)*F(n-2-i,m-4-j))%P;
            for(i=1;i<=n-3;i++)for(j=1;j<=n-3-i;ans=(ans+(ll)(n-2)*i*j*(n-2-i-j)*C(n-3,i+j)%P*C(i+j,i)%P*o)%P,j++)for(o=0,k=i-1;k<=min(i*(i-1)/2,m-4);k++)for(l=j-1;l<=min(j*(j-1)/2,m-4-k);l++)o=(o+(ll)F(i,k)*F(j,l)%P*F(n-2-i-j,m-4-k-l))%P;
            return ans;
        }
};
