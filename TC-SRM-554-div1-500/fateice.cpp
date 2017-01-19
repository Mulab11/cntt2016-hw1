#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
#define L long long
using namespace std;
class TheBrickTowerMediumDivOne
{
	int l,r,p[50];
	bool a[50];
	vector<int> y;
public:
	vector<int> find(vector<int> x)
	{
		int n=x.size();
		int i,j;
		r=n-1;
		while(l<=r)
		  {
		   //找一个编号最小的放在开头 
		   for(i=0;i<n;i++)
		     if(!a[i])
		       break;
		   p[l++]=i;
		   a[i]=1;
		   //把比它大的放在末尾 
		   while(l<=r)
		     {
			  for(i=0;i<n;i++)
			    if(!a[i])
			      break;
			  for(j=i+1;j<n;j++)
			    if(!a[j] && x[j]>=x[i])
			      i=j;
			  if(x[i]<=x[p[l-1]])
			    break;
			  p[r--]=i;
			  a[i]=1;
			 }
		  }
		for(i=0;i<n;i++)
		  y.push_back(p[i]);
		return y;
	}
};
