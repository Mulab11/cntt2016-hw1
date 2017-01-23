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
class PenguinSledding
{
	int m,x[60];
	long long p=1;
public:
	long long countDesigns(int n,vector<int> a,vector<int> b)
	{
		int i,j,k;
		m=a.size();
		for(i=0;i<m;i++)
		  if(a[i]>b[i])
		    swap(a[i],b[i]);
		//三角形 
		for(i=0;i<m;i++)
		  for(j=0;j<m;j++)
		    for(k=0;k<m;k++)
		      if(b[i]==a[j] && b[j]==b[k] && a[k]==a[i])
		        p++;
		for(i=0;i<m;i++)
		  x[a[i]]++,x[b[i]]++;
		//菊花 
		for(i=1;i<=n;i++)
		  p+=1ll<<x[i];
		p-=n+m;
		for(i=0;i<m;i++)
		  if(a[i]==b[i])
		    cout<<"!!\n";
		for(i=0;i<m;i++)
		  for(j=i+1;j<m;j++)
		    if(a[i]==a[j] && b[i]==b[j])
		      cout<<"!!\n";
		return p;
    }
};
