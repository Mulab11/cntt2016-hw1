#include<bits/stdc++.h>
#define vs vector<string>
#define read(s,a) for(auto X:s)for(auto Y:X)Y==' '?++m:a[m]=a[m]*10+Y-48;m++
using namespace std;
int x[500],y[500],i,j,k,n,m;
bitset<500> f[250][500];
class CheckerFreeness
{
	public:
		string isFree(vs X1,vs Y1,vs X2,vs Y2)
		{
			read(X1,x);n=m;read(X2,x);m=0;read(Y1,y);read(Y2,y);
			for(i=0;i<n;i++)for(j=i+1;j<m;j++)for(k=n;k<m;k++)if(j!=k+n&&1ll*(x[i]-x[k])*(y[j]-y[k])-1ll*(x[j]-x[k])*(y[i]-y[k])>0)f[i][j][k]=1;
			for(i=0;i<n;i++)for(j=i+1;j<n;j++)for(k=n;k<m;k++)if(((f[i][k]^f[j][k])&(f[i][j][k]?~f[i][j]:f[i][j])).any())return"NO";
			return"YES";
		}
};
