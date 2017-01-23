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
class IncrementAndDoubling
{
	int n,p,q;
public:
	int getMin(vector<int> x)
	{
		int i,j,k;
		n=x.size();
		for(i=0;i<n;i++)
		  {
		   for(j=0,k=-1;x[i];x[i]>>=1,k++)
		     j+=x[i]&1;
		   p+=j;
		   q=max(q,k);
		  }
		return p+q;
    }
};
