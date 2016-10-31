#include<bits/stdc++.h>
using namespace std;
class StringWeight
{
	public:
		int getMinimum(vector<int> y)
		{
			int n=y.size(),f[55][30][30],i,j,k,l,m,r=1<<29;
			memset(f,9,sizeof(f));
			f[0][0][0]=0;
			for(i=0;i<n;i++)for(j=0;j<=26;j++)for(k=0;k<=j;k++)for(l=max(0,min(y[i],26)+k-j);j+l<=26;l++)for(m=0;m+k<=j+l;m++)
			{
				int g=f[i][j][k],x=min(j-k,m);
				g+=x*(x+1)/2;//情况3
				x=max(0,j-k-m);
				g+=x*y[i]+(!x)*max(0,y[i]-26);//情况1和情况4
				x=min(l,j+l-k-m);
				f[i+1][j+l][k+m]=min(f[i+1][j+l][k+m],g+x*(x-1)/2);//情况2
			}
			for(i=0;i<=26;i++)r=min(r,f[n][i][i]);
			return r;
		}
};
