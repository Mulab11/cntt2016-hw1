#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

class MagicMolecule
{
	public:
	int n,m,ans,val[55];
	int U[2555],V[2555];
	bool choose[55];
	
	void dfs(int p,int c)
	//We have checked first p pairs without a connection between them, and can remove at most c more vertices.
	{
		if(p>m)//We have check all pairs (u,v) without an edge.
		{
			int sum=0;
			for(int i=0;i<n;i++)
				if(choose[i])sum+=val[i];
			ans=max(ans,sum);//Update the answer
		}
		else
		{
			int u=U[p],v=V[p];
			if(!choose[u]||!choose[v])dfs(p+1,c);//there is a connection between u and v.
			else if(c>0)//We should remove either u and v.
			{
				choose[u]=0;
				dfs(p+1,c-1);//remove u
				choose[u]=1;
				choose[v]=0;
				dfs(p+1,c-1);//remove v
				choose[v]=1;
			}
		}
	}
	
	int maxMagicPower(vector<int> magicPower,vector<string> magicBond)
	{
		n=magicPower.size();
		for(int i=0;i<n;i++)
			val[i]=magicPower[i],choose[i]=1;
		for(int i=0;i<n;i++)
			for(int j=i+1;j<n;j++)
				if(magicBond[i][j]=='N')
					m++,U[m]=i,V[m]=j;
		//Let's consider the removed vertices, there are at most floor(n/3) vertices removed.
		//And for each pair (u,v) without an edge <u,v>, we must remove either u or v.
		//The number of dicision we should make is at most 16, so we can do a 2^16 enumeration.
		int s=0;
		while(s+s+s<n+n)s++;
		ans=-1;
		dfs(1,n-s);
		return ans;
	}
};

