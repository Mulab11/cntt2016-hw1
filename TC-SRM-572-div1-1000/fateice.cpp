#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define inf 1000000000
using namespace std;
class NextAndPrev
{
	int m,x[55],y[55],ans=inf;
public:
	int getMinimum(int L,int R,string a,string b)
	{
		int i,j,k,u,v;
		if(a==b)  //特判
		  return 0;
		memset(x,-1,sizeof x);
		for(i=0;i<a.size();i++)
		  {
		   j=a[i]-'a';
		   k=b[i]-'a';
		   if(x[j]!=-1 && x[j]!=k)
		     return -1;
		   x[j]=k;
		   y[k]=1;
		  }
		//特判
		for(i=0;i<26;i++)
		  if(!y[i])
		    break;
		if(i==26)
		  return -1;
		vector<pair<int,int> >f;
		for(i=0;i<26;i++)
		  if(x[i]!=-1)
		    f.push_back(make_pair(i,x[i]));
		m=f.size();
		for(v=0;v<m;v++)
		  {
		   for(i=0;i<m-1;i++)
		     if(f[i].second>f[i+1].second)
			   break;
		   if(i<m-1)
		     {
		      f[0].first+=26;
		      rotate(f.begin(),f.begin()+1,f.end());
		      continue;
			 }
		   for(k=-1;k<=2;k++)
			 {
			  for(i=0;i<m;i++)
			    f[i].second+=k*26;
			  u=0;
			  for(i=0;i<m;i=j)
			    {
				 j=i;
			     int l=f[i].first,r=f[i].first;
			     while(j<m && f[j].second==f[i].second)
				   r=f[j++].first;
			     if(l<f[i].second)
				   u+=L*(f[i].second-l);
			     if(f[i].second<r)
				   u+=R*(r-f[i].second);
				}
			  ans=min(ans,u);
			  for(i=0;i<m;i++)
				f[i].second-=k*26;
			 }
		   f[0].first+=26;
		   rotate(f.begin(),f.begin()+1,f.end());
		  }
		return ans==inf?-1:ans;
	}
};
