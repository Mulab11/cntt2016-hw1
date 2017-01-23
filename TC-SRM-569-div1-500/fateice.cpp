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
class TheJediTest
{
	int n,y[60],p;
public:
	int minimumSupervisors(vector<int> x,int m)
	{
		int i;
		n=x.size();
		x.push_back(0);
		//贪心 
		for(i=0;i<n;i++)
		  {
		   p+=x[i]/m;
		   x[i]%=m;
		   if(x[i+1]>=m-x[i]-y[i])
		     {
			  p++;
			  x[i+1]-=m-x[i]-y[i];
			 }
		   else if(y[i])
		     {
		      p++;
		      x[i+1]=0;
			 }
		   else
		     y[i+1]=x[i];
		  }
		if(y[n])
		  p++;
		return p;
    }
};
