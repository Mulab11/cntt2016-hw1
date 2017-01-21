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
class EelAndRabbit
{
	int n,p;
public:
	int getmax(vector<int> a,vector<int> b)
	{
		int i,j,k,l;
		n=a.size();
		//枚举两次捕鱼的时间点 
		for(i=0;i<n;i++)
		  for(j=0;j<n;j++)
		    {
		     for(k=0,l=0;k<n;k++)
		       if(b[k]<=b[i] && b[i]<=a[k]+b[k] || b[k]<=b[j] && b[j]<=a[k]+b[k])
		         l++;
		     p=max(p,l);
			}
		return p;
    }
};
