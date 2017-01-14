#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
typedef long long LL;

class PenguinSledding
{
	public:
	int g[55][55];
	LL countDesigns(int numCheckpoints,vector<int> checkpoint1,vector<int> checkpoint2)
	{
		int n=numCheckpoints;
		for(int i=0;i<checkpoint1.size();i++)
			g[checkpoint1[i]][checkpoint2[i]]=g[checkpoint2[i]][checkpoint1[i]]=1;
		//Only 3 kinds of graph satisfy the condition.
		//no edges
		//star network
		//triangle
		LL ans=1-checkpoint1.size();//a single edge will be counted twice.
		//triangle
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++)
				for(int k=j+1;k<=n;k++)
					if(g[i][j]&&g[j][k]&&g[k][i])
						ans++;
		//star network
		for(int k=1;k<=n;k++)
		{
			int cnt=0;
			for(int i=1;i<=n;i++)
				cnt+=g[k][i];
			ans+=(1LL<<cnt)-1;
		}
		return ans;
	}
};

