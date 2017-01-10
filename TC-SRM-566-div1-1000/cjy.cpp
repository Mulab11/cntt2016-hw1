#include<bits/stdc++.h>
#define J(x,y) x=(y+x)%P
#define N 255][255]
using namespace std;
int P=1e5+7,f[N[2],g[N,h[N,c[255],i,j,k,d,m,b[N,t,u;long long A[N,C[N;double e,X[255],Y[255];
class FencingPenguins//区间DP,叉积
{
	public:
		int countWays(int n,int r,vector<int> x,vector<int> y,string _)
		{
			for(m=_.size();i<m;i++)c[i]=_[i]<95?_[i]-65:_[i]-71;
			for(e=2*acos(-1)/n,i=0;i<n;i++)X[i]=r*cos(e*i),Y[i]=r*sin(e*i);
			for(k=0;k<m;k++)for(i=0;i<n;i++)for(j=0;j<n;j++)if((X[j]-X[i])*(y[k]-Y[i])-(x[k]-X[i])*(Y[j]-Y[i])>0)A[i][j]|=1ll<<k,C[i][j]|=1ll<<c[k];
			for(i=0;i<n;i++)for(f[i][i][0]=1,j=0;j<n;j++)b[i][j]=!(C[i][j]&C[j][i]);
			for(d=1;d<n;d++)for(i=0,j=d;j<n;i++,j++)
			{
				for(k=0;k<2;k++)for(u=i+1;u<=j;u++)if(b[i][u])if(t=f[u][j][k&&!(A[i][u]&A[u][j]&A[j][i])],!A[u][i])J(f[i][j][k],t);else if(i<u-2&&!(A[u][i]&A[i+1][u-1]))J(f[i][j][k],1ll*h[i+1][u-1]*t);
				for(k=i+1;k<=j;k++)if(b[i][k])if(t=f[i][k][1],!(A[j][i]&A[i][k]))J(g[i][j],t);else if(k<j-1&&!(A[j][i]&A[i][k]&A[k+1][j]))J(g[i][j],1ll*h[k+1][j]*t);
				for(k=i;k<=j;k++)if(!(A[j][i]&A[k][j]))J(h[i][j],g[k][j]);
			}
			return A[0][n-1]?0:h[0][n-1];
		}
};
