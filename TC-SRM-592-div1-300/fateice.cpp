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
#define inf 1000000000
using namespace std;
class LittleElephantAndBalls
{
	int n,x[3],p;
public:
	int getNumber(string a)
	{
		int i;
		n=a.size();
		//直接贪心 
		for(i=0;i<n;i++)
		  {
		   p+=min(x[0],2)+min(x[1],2)+min(x[2],2);
		   if(a[i]=='R')
		     x[0]++;
		   else if(a[i]=='G')
		     x[1]++;
		   else
		     x[2]++;
		  }
		return p;
    }
};
