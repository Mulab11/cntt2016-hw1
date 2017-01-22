#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
#include<map>
#define L long long
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;
class EllysRoomAssignmentsDiv1
{
	int n,m,x[3000];
	double p;
	string s;
public:
	double getAverage(vector<string> t)
	{
		int i;
		for(i=0;i<t.size();i++)
		  s+=t[i];
		for(i=0;i<s.size();i+=5)
		  x[++n]=(s[i]-'0')*1000+(s[i+1]-'0')*100+(s[i+2]-'0')*10+(s[i+3]-'0');
		for(i=2;i<=n;i++)
		  if(x[1]<x[i])
		    m++;
		sort(x+1,x+n+1);
		for(i=1;i<=n/2;i++)
		  swap(x[i],x[n+1-i]);
		for(i=1;i<=n;i++)
		  x[i]+=x[i-1];
		int r=(n-1)/20+1;
		//分自己是不是最后一部分人讨论 
		if(m<n/r*r)
		  {
		   p=double(x[m/r*r]+x[n/r*r]-x[m/r*r+r])/r+x[m+1]-x[m];
		   return (1-double(n%r)/r)*p/(n/r)+double(n%r)/r*(p+double(x[n]-x[n/r*r])/(n%r+1e-9))/(n/r+1);
		  }
		else
		  return (double(x[n/r*r])/r+x[m+1]-x[m])/(n/r+1);
    }
};
