#include<bits/stdc++.h>
using namespace std;
int a[300][300],b[300][300],f[300][300],i,j,k;
class DrawingPointsDivOne//枚举
{
	public:
		int maxSteps(vector<int> x,vector<int> y)
		{
			for(i=0;i<x.size();i++)a[x[i]+75][y[i]+75]=b[x[i]+75][y[i]+75]=1;
			for(k=1;k<150;k++)
			{
				for(i=299;i;i--)for(j=299;j;j--)a[i][j]|=a[i-1][j-1]|a[i-1][j]|a[i][j-1];
				for(i=298;i;i--)for(j=298;j;j--)if((f[i][j]=a[i][j]*(min(f[i+1][j],min(f[i][j+1],f[i+1][j+1]))+1))>k&&!b[i][j])return k-1;
			}
			return -1;
		}
};
