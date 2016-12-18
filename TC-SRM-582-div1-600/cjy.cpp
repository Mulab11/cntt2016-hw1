#include<bits/stdc++.h>
#define N 2000
using namespace std;
int f[N]={1,1},u[N]={1,1},v[N]={1,1},i=2,P=1e9+9,c[N],F[N][N],s[N],S[2*N][N],n,j;
string a,b;
class ColorfulBuilding
{
	public:
		int count(vector<string> A,vector<string> B,int l)
		{
			for(;i<N;i++)f[i]=1ll*f[i-1]*i%P,u[i]=1ll*(P-P/i)*u[P%i]%P,v[i]=1ll*v[i-1]*u[i]%P;
			for(i=0;i<A.size();i++)a+=A[i];
			for(i=0;i<B.size();i++)b+=B[i];
			for(n=a.size(),i=0;i<n;i++)c[i+1]=(a[i]-'A')*60+b[i]-'A';
			for(i=1;i<=n;i++)for(j=1;j<=i;j++)
			{
				F[i][j]=(j==1?(1ll*f[n-1]*v[n-i]+1ll*v[n-i]*S[c[i]][j])%P:(1ll*S[c[i]][j]-S[c[i]][j-1]+s[j-1]+P)*v[n-i]%P);
				if(i<n)F[i][j]=1ll*F[i][j]*f[n-i-1]%P;
				s[j]=(s[j]+F[i][j])%P;S[c[i]][j]=(S[c[i]][j]+F[i][j])%P;
			}
			return F[n][l];
		}
};
