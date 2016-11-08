#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N=55;
int n,m,ans,f[N][N];
LL a[N],b[N];
class AstronomicalRecords
{
	public:
		
		int minimalPlanets(vector<int>A,vector<int>B)
		{
			n=A.size(); m=B.size(); ans=n+m;
			for (int i=0;i<n;i++)
				for (int j=0;j<m;j++)
				{
					for (int x=1;x<=n;x++) a[x]=(LL)A[x-1]*(LL)B[j];
					for (int x=1;x<=m;x++) b[x]=(LL)B[x-1]*(LL)A[i];
					for (int x=0;x<=n;x++)
						for (int y=0;y<=m;y++) f[x][y]=0;
					for (int x=1;x<=n;x++)
						for (int y=1;y<=m;y++)
						{
							f[x][y]=max(f[x-1][y],f[x][y-1]);
							if (a[x]==b[y]) f[x][y]=max(f[x][y],f[x-1][y-1]+1);
						}
					ans=min(ans,n+m-f[n][m]);
				}		
			return ans;
		}	
};