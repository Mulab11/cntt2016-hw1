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
class DrawingPointsDivOne
{
	int a[1010][1010];
public:
	int maxSteps(vector<int> x,vector<int> y)
	{
	    int n;
		int i,j,k,l;
		n=x.size();
		for(l=1;l<=150;l++)
		  {
		   for(i=0;i<n;i++)
		     for(j=2*x[i]-l;j<=2*x[i]+l;j+=2)
		       for(k=2*y[i]-l;k<=2*y[i]+l;k+=2)
		         a[j+500][k+500]=1;
		   for(i=1;i<=1000;i++)
		     for(j=1;j<=1000;j++)
		       a[i][j]=a[i-1][j]+a[i][j-1]+a[i][j]-a[i-1][j-1];
		   for(i=-150,k=0;i<=150;i++)
		     for(j=-150;j<=150;j++)
		       if(a[i+l+500][j+l+500]-a[i+l+500][j-l+499]-a[i-l+499][j+l+500]+a[i-l+499][j-l+499]==(l+1)*(l+1))
		         k++;
		   for(i=1;i<=1000;i++)
		     for(j=1;j<=1000;j++)
		       a[i][j]=0;
		   if(k>n)
		     return l-1;
		  }
		return -1;
    }
};
