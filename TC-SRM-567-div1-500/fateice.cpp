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
class StringGame
{
	int n,x[60][60];
	bool a[60],b[60];
	vector<int> p;
	inline void dfs(int i,int j)
	{
		int k,l;
		if(j>26)
		  {
		   for(k=0;k<n;k++)
		     if(k!=i && !b[k])
		       return;
		   p.push_back(i);
		   return;
		  }
		for(k=0;k<26;k++)  //随意找一个该串最多的字母 
		  if(!a[k])
		    {
			 for(l=0;l<n;l++)
			   if(!b[l] && x[l][k]>x[i][k])
			     break;
			 if(l==n)
			   {
				for(l=0;l<n;l++)
				  if(x[l][k]<x[i][k])
				    b[l]=1;
				a[k]=1;
				dfs(i,j+1);
				return;
			   }
			}
	}
public:
	vector<int> getWinningStrings(vector<string> s)
	{
		int i,j;
		n=s.size();
		for(i=0;i<n;i++)
		  for(j=0;j<s[0].size();j++)
		    x[i][s[i][j]-'a']++;
		for(i=0;i<n;i++)
		  {
		   for(j=0;j<n || j<26;j++)
		     a[j]=b[j]=0;
		   dfs(i,1);  //搜索每个串是否可行 
		  }
		return p;
    }
};
