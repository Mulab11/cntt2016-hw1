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
class SpellCards
{
	int n,f[60][60];
public:
	int maxDamage(vector<int> a,vector<int> b)
	{
		int i,j;
		n=a.size();
		//01背包 
		for(i=1;i<=n;i++)
		  for(j=1;j<=n;j++)
		    f[i][j]=max(f[i][j-1],max(f[i-1][j],j>=a[i-1]?(f[i-1][j-a[i-1]]+b[i-1]):0));
		return f[n][n];
    }
};
