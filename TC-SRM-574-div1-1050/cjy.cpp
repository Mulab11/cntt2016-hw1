#include<bits/stdc++.h>
using namespace std;
vector<string> a;
int n,m,i,dx[4]={0,1,0,-1},dy[4]={1,0,-1,0},t,u[50],v[50],f[51][51][51],s,j,k,ej,ek,x;
int dfs(int x,int y,int A=-1,int B=-1)
{
	if(A<0)t=0;t++;
	int i=3,ex,ey;
	for(;~i;i--)if(ex=x+dx[i],ey=y+dy[i],(ex!=A||ey!=B)&&~ex&&~ey&&ex<n&&ey<m&&a[ex][ey]=='X')return dfs(ex,ey,x,y);
	return x;
}
void calc(int x,int y,int*z)
{
	for(i=0;i<n;i++)if(a[i][x]=='X')if(dfs(i,x)==i&&t==m)z[i]=-1;else
	if(i&&a[i-1][x]!='X'&&dfs(i,x)>=i&&(i==n-1||a[i+1][x]!='X'||a[i][y]!='X'))z[i]=2;else
	if(i+1<n&&a[i+1][x]!='X'&&dfs(i,x)<i&&(!i||a[i-1][x]!='X'||a[i][y]!='X')||!i&&!dfs(i,x))z[i]=i<2||t>2;
}
class Tunnels
{
	public:
		int minimumTunnels(vector<string> A)
		{
			if(a=A,n=a.size(),m=a[0].size(),m==1){for(i=0;i<n;i++)if(a[i][0]=='X')return 1;return 0;}
			for(calc(0,1,u),calc(m-1,m-2,v),i=0;i<m;i++)if(a[0][i]=='X'&&(!i||a[0][i-1]!='X'))s++;
			for(i=n-1;~i;i--)for(j=0;j<n;j++)for(k=0;k<n;k++)
			{
				if(ej=j,ek=k,x=0,u[i]==1)ej++;
				if(u[i]==2)ej?ej--:x++;
				if(v[i]==1)ek++;
				if(v[i]==2)ek?ek--:x++;
				f[i][j][k]=~u[i]?f[i+1][ej][ek]+x:min(f[i+1][j-(j&&i)][k+1]+(!j&&i),f[i+1][j+1][k-(k&&i)]+(!k&&i));
			}
			return f[0][0][0]+s;
		}
};
