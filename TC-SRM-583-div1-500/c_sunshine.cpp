#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
const int inf=100005;

class TurnOnLamps
{
	public:
	int n;
	string S,I;
	vector<int> adj[55];
	
	int f[55][2];
	
	void dfs(int x)
	{
		//f[x][t]: the minimum number of ends in x's subtree to turn all lamps on, and f[x][t] = t (mod 2)
		f[x][0]=0;f[x][1]=inf;
		int g[2];
		for(int y,i=0;i<adj[x].size();i++)//Bery simple tree-knapsack
		{
			y=adj[x][i];
			dfs(y);
			g[0]=min(f[x][0]+f[y][0],f[x][1]+f[y][1]);
			g[1]=min(f[x][0]+f[y][1],f[x][1]+f[y][0]);
			f[x][0]=g[0];
			f[x][1]=g[1];
		}
		f[x][0]=min(f[x][0],f[x][1]+1);
		f[x][1]=min(f[x][1],f[x][0]+1);
		if(I[x]=='1')//check if it satisfies the rule
		{
			if(S[x]=='1')f[x][1]=inf;
			else f[x][0]=inf;
		}
	}
	
	int minimize(vector<int> roads,string initState,string isImportant)
	{
		n=roads.size()+1;
		for(int i=0;i<n-1;i++)
			adj[roads[i]].push_back(i+1);
		S="1"+initState;
		I="1"+isImportant;
		for(int i=0;i<n;i++)
			f[i][0]=f[i][1]=inf;
		//We do not care about how the paths go,
		//but the odevity of the number of the path ends in the subtree 
		dfs(0);
		return f[0][0]/2;
	}
};

