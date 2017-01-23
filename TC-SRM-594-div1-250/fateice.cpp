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
class AstronomicalRecords
{
    int n,m,f[60][60],p;
public:
	int minimalPlanets(vector<int> a,vector<int> b)
	{
		int i,j,k,l,u;
		n=a.size();
		m=b.size();
		//枚举比例然后dp 
		for(i=0;i<n;i++)
		  for(j=0;j<m;j++)
		    {
             for(k=1;k<=n;k++)
               for(l=1;l<=m;l++)
                 if((L)a[k-1]*b[j]==(L)b[l-1]*a[i])
                   f[k][l]=f[k-1][l-1]+1;
                 else
                   f[k][l]=max(f[k-1][l],f[k][l-1]);
             p=max(p,f[n][m]);
            }
        return n+m-p;
    }
};
