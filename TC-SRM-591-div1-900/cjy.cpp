#include<bits/stdc++.h>
#define RE(x,y) (x+=1ll*y*f[i][j][a][b]%P)%=P
using namespace std;
int f[9][9][256][256],P=1e9+9,i,j,a,b,k,s;
int _A(int x,int y){if(x>>y&1)x-=1<<y;return x;}
int _D(int x,int y){if(y&&(x>>(y-1)&1))x|=1<<y;return x;}
class StringPath
{
	public:
	int countBoards(int n,int m,string A,string B)//状态压缩DP	
	{
		if (A[0]!=B[0]||A[n+m-2]!=B[n+m-2])return 0;
		f[0][0][1][1]=1;
		for(i=0;i<n;i++)for(j=0;j<m;j++)
		{
			for(a=0;a<1<<m;a++)for(b=0;b<1<<m;b++)if(j==m-1)
				if(A[i+1]==B[i+1])RE(f[i+1][0][_D(a,0)][_D(b,0)],1),RE(f[i+1][0][_A(a,0)][_A(b,0)],25);
				else RE(f[i+1][0][_D(a,0)][_A(b,0)],1),RE(f[i+1][0][_A(a,0)][_D(b,0)],1),RE(f[i+1][0][_A(a,0)][_A(b,0)],24);
			else
				if(A[i+j+1]==B[i+j+1])RE(f[i][j+1][_D(a,j+1)][_D(b,j+1)],1),RE(f[i][j+1][_A(a,j+1)][_A(b,j+1)],25);
				else RE(f[i][j+1][_D(a,j+1)][_A(b,j+1)],1),RE(f[i][j+1][_A(a,j+1)][_D(b,j+1)],1),RE(f[i][j+1][_A(a,j+1)][_A(b,j+1)],24);
		}
		for(a=1<<m-1;a<1<<m;a++)for(b=1<<m-1;b<1<<m;b++)s=(s+f[n-1][m-1][a][b])%P;
		return s;
	}
};
