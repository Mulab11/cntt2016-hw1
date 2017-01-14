#include<cstdio>//By c_sunshine
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
const int maxn=100005;

class ColorfulWolves
{
	public:
	int n,d[55][55];
	int getmin(vector<string> c)
	{
		//It is clear that there won't be cycles in the color changing path,
		//so we can simply change this problem to a shortest-path problem.
		//Let d[i][j] be the minimum cost to alter color i to color j in one night,
		//and, obviously, d[i][j] will be the number of colors k satisfying k<j and colormap[i][k]='Y'
		//and be infinity when colormap[i][j]='N'.
		//The distance from 0 to n-1 on the graph constructed by d[][] will be the answer.
		n=c.size();memset(d,63,sizeof(d));
		//get d[i][j]
		for(int i=0;i<n;i++)
			for(int j=0,k=0;j<n;j++)
				if(c[i][j]=='Y')d[i][j]=k++;
		//Use Floyd to determine all pairs' shortest paths.
		for(int k=0;k<n;k++)
			for(int i=0;i<n;i++)
				for(int j=0;j<n;j++)
					d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
		//It is impossible if color 0 cannot reach color n-1.
		return d[0][n-1]<1<<25?d[0][n-1]:-1;
	}
};

