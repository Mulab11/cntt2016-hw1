#include<bits/stdc++.h>
using namespace std;
int n,m,s,i,j,x,y,f[55][55];
long long a[55],b[55];
class AstronomicalRecords
{
	public:
		int minimalPlanets(vector<int>A,vector<int>B)
		{
			n=A.size();m=B.size();
			for(i=0;i<n;i++)for(j=0;j<m;j++)
			{
				for(x=1;x<=n;x++)a[x]=1ll*A[x-1]*B[j];
				for(x=1;x<=m;x++)b[x]=1ll*B[x-1]*A[i];
				memset(f,0,sizeof(f));
				for(x=1;x<=n;x++)for(y=1;y<=m;y++)f[x][y]=max((a[x]==b[y])*(f[x-1][y-1]+1),max(f[x-1][y],f[x][y-1]));
				s=max(s,f[n][m]);
			}		
			return n+m-s;
		}	
};
