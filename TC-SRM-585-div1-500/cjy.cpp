#include<bits/stdc++.h>
#define N 5000
using namespace std;
int P=1e9+7,f[N],v[N],i=2,j,g[N],S,u[N];
int C(int x,int y){return x<y?0:1ll*f[x]*v[y]%P*v[x-y]%P;} 
class LISNumber
{
	public:
		int count(vector<int> a,int K)
		{
			for(f[0]=v[0]=f[1]=v[1]=u[1]=1;i<N;i++)f[i]=1ll*f[i-1]*i%P,u[i]=1ll*(P-P/i)*u[P%i]%P,v[i]=1ll*v[i-1]*u[i]%P;
			for(i=1;i<=K;i++)//DP容斥			
			{
				g[i]=1;S=0;
				for(auto x : a)g[i]=1ll*g[i]*C(i,x)%P,S+=x;
				for(j=1;j<i;j++)g[i]=(g[i]+P-1ll*g[j]*C(S+i-j,i-j)%P)%P;
			}
			return g[K];
		}
};
