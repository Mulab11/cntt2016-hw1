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
class TeamContest
{
	int n,m,p;
public:
	int worstRank(vector<int> x)
	{
		int i,j;
		n=x.size();
		m=max(max(x[0],x[1]),x[2])+min(min(x[0],x[1]),x[2]);
		sort((&x[0])+3,(&x[0])+n);
		//贪心 
		for(i=3,j=n-1;i<j;i+=2,j--)
		  {
		   while(i<n && x[i]+x[j]<=m)
		     i++;
		   if(j-i>1)
		     p++;
		  }
		return p+1;
    }
};
