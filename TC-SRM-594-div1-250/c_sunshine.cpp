#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
typedef long long LL;
class AstronomicalRecords
{
	public:
	int n,m,f[55][55];
	LL a[55],b[55];
	int minimalPlanets(vector<int> A,vector<int> B)
	{
		n=A.size(),m=B.size();
		int ans=n+m;
		//Pick all possible ratio
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
			{
				for(int k=1;k<=n;k++)
					a[k]=(LL)A[k-1]*B[j];
				for(int k=1;k<=m;k++)
					b[k]=(LL)B[k-1]*A[i];
				//Use dynamic programming to solve longest common subsequence
				memset(f,0,sizeof(f));
				for(int x=1;x<=n;x++)
					for(int y=1;y<=m;y++)
						if(a[x]==b[y])
							f[x][y]=f[x-1][y-1]+1;
						else
							f[x][y]=max(f[x-1][y],f[x][y-1]);
				//Use n+m-LCS to update the answer 
				ans=min(ans,n+m-f[n][m]);
			}
		return ans;
	}
};

