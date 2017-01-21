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
class FoxAndHandle
{
	int n,a[1000],b[1000],c[1000];
	string t={};
public:
	string lexSmallestName(string s)
	{
		int i,j,k,l;
		n=s.size();
		for(i=0;i<n;i++)
		  a[s[i]]++,b[s[i]]++;
		for(i=0;i<n;i++)
		  for(j='a';j<='z';j++)  //贪心 
		    if(c[j]<a[j]/2)
		      {
			   k=i;
			   while(s[i]!=j)
			     b[s[i++]]--;
			   for(l='a';l<='z';l++)
			     if(b[l]+c[l]<a[l]/2)
			       break;
			   if(l<='z')
			     {
				  while(i>k)
				    b[s[--i]]++;
				 }
			   else
			     {
			      c[j]++;
			      b[s[i]]--;
				  t.push_back(j);
				  break;
				 }
			  }
		return t;
    }
};
