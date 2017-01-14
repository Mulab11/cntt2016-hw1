#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
const int M=1000000007;
class GooseInZooDivOne
{
	public:
	int n,m,dist;
	vector<string> field;
	vector<int> g;
	int v[55][55];
	int f[2555][2];
	inline int ABS(const int &xx){return xx<0?-xx:xx;}
	
	int dfs(int x,int y)//Depth first search to get a connective subgraph
	{
		int res=1;
		v[x][y]=1;
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				if(field[i][j]=='v'&&!v[i][j]&&ABS(i-x)+ABS(j-y)<=dist)
					res+=dfs(i,j);
		return res;
	}
	
	int count(vector<string> field,int dist)
	{
		this->field=field;
		this->dist=dist;
		n=field.size();
		m=field[0].size();
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				if(field[i][j]=='v'&&!v[i][j])
					g.push_back(dfs(i,j));
		//f[i][j]: The ways to pick a set from first i connective graphs satisfying the number of geese is even/odd.
		f[0][0]=1;
		for(int i=0;i<g.size();i++)
			for(int j=0;j<2;j++)
				(f[i+1][j^(g[i]&1)]+=f[i][j])%=M,//pick the current subgraph
				(f[i+1][j]+=f[i][j])%=M;//do not pick
		return (f[g.size()][0]+M-1)%M;
	}
};

