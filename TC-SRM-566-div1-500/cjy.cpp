#include<bits/stdc++.h>
using namespace std;
int n,P=1e9+7,k,i,j;
struct H{long long x[355];}S,x,e,f;
H C(H x,H y)
{
	H z=e;
	for(i=0;i<n;i++)for(j=0;j<n;j++)(z.x[(i+j)%n]+=x.x[i]*y.x[j])%=P;
	return z;
}
class PenguinEmperor
{
	public:
		int countJourneys(int N,long long m)
		{
			for(n=N,x.x[0]=1;k<n;k++)if(f=e,f.x[k]=f.x[n-k]=1,x=C(x,f),k==m%n)S=x;
			for(m/=n;m;x=C(x,x),m/=2)if(m&1)S=C(S,x);
			return S.x[0];
		}
};
