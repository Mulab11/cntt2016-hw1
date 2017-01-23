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
class LittleElephantAndIntervalsDiv1
{
	int n,x[60];
public:
	long long getNumber(int m,vector<int> l,vector<int> r)
	{
		int i,j;
		n=l.size();
		//枚举每个位置最终被染色的操作 
		for(i=1;i<=m;i++)
		  for(j=n-1;j>=0;j--)
		    if(l[j]<=i && i<=r[j])
		      {
			   x[j]=1;
			   break;
			  }
		for(i=0,j=0;i<n;i++)
		  if(x[i])
		    j++;
		return 1ll<<j;
    }
};
