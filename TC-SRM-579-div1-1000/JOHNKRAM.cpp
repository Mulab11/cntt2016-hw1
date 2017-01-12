#include<bits/stdc++.h>
using namespace std;
double p[55][55][55],P[55][55][55],f[55],F[55][55][55];
bool v[55][55][55];
int n,a[100],b[100],c[100],A,B,C,i,j,k,l,m;
double dfs(int x,int y,int z)
{
	if(!P[x][y][z]||x+y+z==n)return 0;
	if(v[x][y][z])return F[x][y][z];
	v[x][y][z]=1;
	double p1=P[x+1][y][z]/P[x][y][z],p2=P[x][y+1][z]/P[x][y][z],p3=P[x][y][z+1]/P[x][y][z];
	return F[x][y][z]=dfs(x+1,y,z)*p1+dfs(x,y+1,z)*p2+dfs(x,y,z+1)*p3+max(max(p1+p3*3,p1*3+p2),p2*3+p3);
}
class RockPaperScissors
{
    public:
        double bestScore(vector <int> rockProb, vector <int> paperProb, vector <int> scissorsProb)
        {
	        n=rockProb.size();
        	for(i=1;i<=n;i++)
	        {
	            a[i]=rockProb[i-1];
	            b[i]=paperProb[i-1];
	            c[i]=scissorsProb[i-1];
	        }
	        p[0][0][0]=1;
        	for(i=1;i<=n;i++)for(j=0;j<=i;j++)for(k=0;j+k<=i;k++)
	        {
		        l=i-j-k;
	        	if(j)p[j][k][l]+=p[j-1][k][l]*a[i]/300;
	        	if(k)p[j][k][l]+=p[j][k-1][l]*b[i]/300;
	        	if(l)p[j][k][l]+=p[j][k][l-1]*c[i]/300;
	        }
        	for(i=f[0]=1;i<=n;i++)f[i]=f[i-1]*i;
        	for(i=0;i<=n;i++)for(j=0;i+j<=n;j++)for(k=0;i+j+k<=n;k++)for(l=i;l<=n;l++)for(m=j;k+l+m<=n;m++)P[i][j][k]+=p[l][m][n-l-m]*f[n-i-j-k]/f[l-i]/f[m-j]/f[n-l-m-k]*f[l]*f[m]*f[n-l-m]/f[n];
	        return dfs(0,0,0);
        }
};
