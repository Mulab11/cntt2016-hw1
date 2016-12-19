#include<bits/stdc++.h>
using namespace std;
double p[55][55][55],P[55][55][55],f[55],F[55][55][55],u;int v[55][55][55],i,j,k,l,m,n;
double D(int x,int y,int z)
{
	if(v[x][y][z])return F[x][y][z];
	if(v[x][y][z]=1,!(u=P[x][y][z])||x+y+z==n)return 0;
	double a=P[x+1][y][z]/u,b=P[x][y+1][z]/u,c=P[x][y][z+1]/u;
	return F[x][y][z]=a*D(x+1,y,z)+b*D(x,y+1,z)+c*D(x,y,z+1)+max(max(a+c*3,b+a*3),c+b*3);
}
class RockPaperScissors
{
	public:
		double bestScore(vector<int> a,vector<int> b,vector<int> c)//概率相关dp
		{
			for(n=a.size(),i=f[0]=1;i<=n;i++)f[i]=f[i-1]*i;
			for(p[0][0][0]=1,i=1;i<=n;i++)for(j=0;j<=i;j++)for(k=0;j+k<=i;k++)
			{
				if(l=i-j-k,j)p[j][k][l]+=p[j-1][k][l]*a[i-1]/300;
				if(k)p[j][k][l]+=p[j][k-1][l]*b[i-1]/300;
				if(l)p[j][k][l]+=p[j][k][l-1]*c[i-1]/300;
			}
			for(i=0;i<=n;i++)for(j=0;i+j<=n;j++)for(k=0;i+j+k<=n;k++)for(l=i;l+j+k<=n;l++)for(m=j;m+l+k<=n;m++)
				P[i][j][k]+=p[l][m][n-l-m]*f[n-i-j-k]/f[l-i]/f[m-j]/f[n-l-m-k]*f[l]*f[m]*f[n-l-m]/f[n];
			return D(0,0,0);
		}
};
