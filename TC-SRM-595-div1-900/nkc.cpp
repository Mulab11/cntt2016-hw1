#include<iostream>
#include<cstdio>
#include<vector>
#define dd double
#define N 60
using namespace std;
int n;
dd ans,p[N];
struct Constellation
{
dd expectation(vector<int> x,vector<int> y,vector<int> a)
{
	n=x.size();
	for(int i=0;i<n;i++) p[i]=(dd)a[i]/1000;
	for(int i=0;i<n;i++)
	for(int j=0;j<n;j++)
	if(i!=j)
	{
		dd s=p[i]*p[j];
		for(int k=0;k<n;k++)
		if(k!=i&&k!=j)
		{
			int o=(x[j]-x[i])*(y[k]-y[i])-(y[j]-y[i])*(x[k]-x[i]);
			if(o<0||!o&&x[k]>=min(x[i],x[j])&&x[k]<=max(x[i],x[j])&&y[k]>=min(y[i],y[j])&&y[k]<=max(y[i],y[j])) s*=(1-p[k]);
		}
		ans+=s*(x[i]*y[j]-y[i]*x[j])/2;
	}
	return ans;
}
};