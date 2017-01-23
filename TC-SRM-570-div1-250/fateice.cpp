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
int dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};
class RobotHerb
{
	int n;
	long long p;
public:
	long long getdist(int m,vector<int> a)
	{
		int i,j,k,x=0,y=0;
		n=a.size();
		for(i=0,k=0;i<4;i++)  //每4n步都是相同的 
		  {
		   if(i==m%4)
		     p=abs(x)+abs(y);
		   for(j=0;j<n;j++)
		     {
			  x+=dx[k]*a[j];
			  y+=dy[k]*a[j];
			  k=(k+a[j])%4;
			 }
		  }
		return p+(L)m/4*(abs(x)+abs(y));
    }
};
