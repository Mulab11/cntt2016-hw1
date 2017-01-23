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
class MagicMolecule
{
	int n,a[60][60],p=-1;
	vector<int> x;
	bool w[60];
	inline void dfs(int i,int j,int k,int l)
	{
		if(l*3<2*n)
		  return;
		if(i==n)
		  p=max(p,k);
		else if(j==n)
		  dfs(i+1,0,k,l);
		else if(a[i][j] || w[i] || w[j] || i==j)
		  dfs(i,j+1,k,l);
		else
		  {
		   //枚举哪个点不选 
		   w[i]=1;
		   dfs(i,j+1,k-x[i],l-1);
		   w[i]=0;
		   w[j]=1;
		   dfs(i,j+1,k-x[j],l-1);
		   w[j]=0;
		  }
	}
public:
	int maxMagicPower(vector<int> xx,vector<string> s)
	{
		int i,j;
		x=xx;
		n=x.size();
		for(i=0;i<n;i++)
		  for(j=0;j<n;j++)
		    a[i][j]=(s[i][j]=='Y');
		for(i=0,j=0;i<n;i++)
		  j+=x[i];
		dfs(0,0,j,n);
		return p;
    }
};
