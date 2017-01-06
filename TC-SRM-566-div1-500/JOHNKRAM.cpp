#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define P 1000000007
int n,k,i,j,f[400][400],g[400],t[400];
ll m;
void mul(int *a,int *b,int *c)//循环卷积 
{
	for(i=0;i<n;i++)t[i]=0;
	for(i=0;i<n;i++)if(a[i])for(j=0;j<n;j++)if(b[j])t[(i+j)%n]=(t[(i+j)%n]+(ll)a[i]*b[j])%P;
	for(i=0;i<n;i++)c[i]=t[i];
}
class PenguinEmperor
{
    public:
        int countJourneys(int numCities, long long daysPassed)
        {
        	for(n=numCities,m=daysPassed,f[0][0]=g[0]=i=1;i<n;i++)for(j=0;j<n;j++)//求转移多项式 
            {
	        	f[i][j]=f[i-1][(j-i+n)%n]+f[i-1][(j+i)%n];
	        	if(i<<1==n)f[i][j]>>=1;
	        	if(f[i][j]>=P)f[i][j]-=P;
	        }
        	for(i=0;i<n;i++)f[n][i]=f[n-1][i];
        	for(k=m%n,m/=n;m;mul(f[n],f[n],f[n]),m>>=1)if(m&1)mul(g,f[n],g);//快速幂 
	        mul(g,f[k],g);//乘上余项计算答案 
        	return g[0];
        }
};