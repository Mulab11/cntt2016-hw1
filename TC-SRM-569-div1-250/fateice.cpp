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
class TheDevice
{
	int n,m,p;
public:
	int minimumAdditional(vector<string> s)
	{
		int i,j,k,l;
		n=s.size();
		m=s[0].size();
		for(i=0;i<m;i++)
		  {
		   for(j=0,k=l=0;j<n;j++)
		     if(s[j][i]=='0')
		       k++;
		     else
		       l++;
		   p=max(p,max(1-k,0)+max(2-l,0));
		  }
		return p;
    }
};
