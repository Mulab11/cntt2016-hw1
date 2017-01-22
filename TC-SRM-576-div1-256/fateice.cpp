#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
#define L long long
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;
class ArcadeManao
{
	int n,m;
	vector<string> s;
	bool x[60][60];
	inline void dfs(int i,int j,int k)
	{
		int l;
		x[i][j]=1;
		if(j && s[i][j-1]=='X' && !x[i][j-1])
		  dfs(i,j-1,k);
		if(j<m-1 && s[i][j+1]=='X' && !x[i][j+1])
		  dfs(i,j+1,k);
		for(l=i-k;l<=i+k;l++)
		  if(l>=0 && l<n && s[l][j]=='X' && !x[l][j])
		    dfs(l,j,k);
	}
public:
	int shortestLadder(vector<string> ss,int a,int b)
	{
		int i,j,k;
		s=ss;
		n=s.size();
		m=s[0].size();
		for(i=0;i<n;i++)
		  {
		   for(j=0;j<n;j++)
		     for(k=0;k<m;k++)
		       x[j][k]=0;
		   dfs(n-1,0,i);
		   if(x[a-1][b-1])
		     return i;
		  }
		return -1;
    }
};
