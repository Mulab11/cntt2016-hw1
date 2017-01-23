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
class Constellation
{
	int n;
	double p;
	vector<int> x,y;
	inline int cha(int i,int j,int k)
	{
		return (x[j]-x[i])*(y[k]-y[i])-(x[k]-x[i])*(y[j]-y[i]);
	}
public:
	double expectation(vector<int> xx,vector<int> yy,vector<int> w)
	{
		int i,j,k;
		double q;
		x=xx;
		y=yy;
		n=x.size();
		x.push_back(0);
		y.push_back(0);
		//分别计算每条边的贡献 
		for(i=0;i<n;i++)
		  for(j=0;j<n;j++)
		    if(i!=j)
		      {
			   q=w[i]*w[j]*1e-6;
			   for(k=0;k<n;k++)
			     if(k!=i && k!=j && (cha(i,j,k)<0 || cha(i,j,k)==0 && ((x[k]<x[i])^(x[k]<x[j]) || (y[k]<y[i])^(y[k]<y[j]))))
			       q*=1-w[k]*1e-3;
			   p+=q*cha(n,i,j);
			  }
		return p*0.5;
    }
};
