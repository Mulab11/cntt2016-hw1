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
class NewArenaPassword
{
	int n,x[60][60]={},p=0;
public:
	int minChange(string s,int m)
	{
		int i,j,k;
		n=s.size();
		if(m==n)
		  return 0;
		if(m<=n/2)
		  {
		   for(i=0;i<m;i++)
		     x[i][s[i]-'a']++;
		   for(i=n-m;i<n;i++)
		     x[i-n+m][s[i]-'a']++;
		  }
		else
		  {
		   m=n-m;
		   for(i=0;i<n;i++)
		     x[i%m][s[i]-'a']++;
		  }
		//相同位上贪心 
		for(i=0;i<m;i++)
		  {
		   for(j=0,k=0;j<26;j++)
		     p+=x[i][j],k=max(k,x[i][j]);
		   p-=k;
		  }
		return p;
    }
};
