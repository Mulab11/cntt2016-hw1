#include<bits/stdc++.h>
using namespace std;
int P=1e9+7,N=150,n,i,j,k,t[3];
struct M{int x[150][150];}E,X,S;
M C(M x,M y)
{
	M z=E;
	for(i=0;i<N;i++)for(k=0;k<N;k++)if(x.x[i][k])for(j=0;j<N;j++)(z.x[i][j]+=1ll*x.x[i][k]*y.x[k][j]%P)%=P;
	return z;
}
class ConversionMachine
{
	public:
		int countAll(string s1,string s2,vector<int> a,int m)
		{
			for(n=s1.size();i<n;i++)for(j=s1[i]-97,k=s2[i]-97,t[(3+k-j)%3]++;j!=k;j=(j+1)%3)if(m-=a[j],m<0)return 0;
			for(m/=a[0]+a[1]+a[2],m=m*3+t[2]*2+t[1],X.x[149][149]=X.x[149][t[1]*12+t[2]]=1,i=0;i<=n;i++)for(j=0;i+j<=n;j++)if(X.x[i*12+j][i*12+j+11]+=j,X.x[i*12+j][i*12+j+1]+=n-i-j,i)X.x[i*12+j][i*12+j-12]+=i;
			for(S=X;m;m/=2,X=C(X,X))if(m&1)S=C(S,X);
			return S.x[149][0];
		}
};
