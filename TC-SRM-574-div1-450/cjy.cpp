#include<bits/stdc++.h>
using namespace std;
long long f[1<<18][18],S;
int i,j,k,l,r,s[18];
class PolygonTraversal
{
	public:
		long long count(int n,vector<int> p)
		{
			for(auto x : p)i|=1<<x-1;
			for(f[i][p.back()-1]=1;i<1<<n;i++)
			{
				for(j=0;j<n;j++)if(s[j+1]=s[j],i>>j&1)s[j+1]++;
				for(j=0;j<n;j++)if(i>>j&1)for(k=0;k<n;k++)if(!(i>>k&1))if(s[r=max(j,k)]-s[l=min(j,k)+1]&&s[r]-s[l]<s[n]-1)f[i+(1<<k)][k]+=f[i][j];
			}
			for(j=0;j<n;j++)if(j!=p[0]%n&&j!=(p[0]+n-1)%n&&j!=(p[0]+n-2)%n)S+=f[i-1][j];
			return S;
		}
};
