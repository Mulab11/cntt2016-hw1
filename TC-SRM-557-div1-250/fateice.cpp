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
class FoxAndMountainEasy
{
public:
	string possible(int n,int a,int b,string x)
	{
		int m=x.size(),c=a;
		int i,j=0,k=0;
		for(i=0;i<m;i++)    //计算和以及最低点 
		  if(x[i]=='U')
		    j++;
		  else
		    {
		     j--;
		     k=min(k,j);
			}
		a+=j;
		n-=m;
		if(abs(b-a)<=n && (n-abs(b-a))%2==0 && (n-abs(b-a))/2+max(b-a,0)+c+k>=0)
		  return "YES";
		else
		  return "NO";
    }
};
