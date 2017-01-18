#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<bitset>

#define ls (t<<1)
#define rs ((t<<1)+1)
#define mid ((l+r)>>1)
#define fi first
#define se second
#define mk make_pair
#define pb push_back

#define N 55
#define M 200005
#define seed 23333
#define Mo 1000000007

using namespace std;
int i,j,m,n,p,k,A[N][N],B[N][N],ans;
int f[N][N][2];
int sum(int sx,int ex,int y)
{
		return A[ex][y]-A[sx-1][y]+B[ex][y]-B[sx-1][y];
}
int all(int sx,int ex,int y)
{
		return A[ex][y]-A[sx-1][y];
}
void jia(int &x,int y)
{
		x+=y; if (x>=Mo) x-=Mo;
}
//处理形如
//BBB
//.BB
//..B 
void gaoA()
{
		memset(f,0,sizeof(f));
		if (sum(1,n,1)!=n) return;
		f[1][1][0]=1;
		for (i=2;i<=m;++i)
			for (j=1;j<=n+1;++j)
				for (k=j;k<=n+1;++k)
				{
						if (sum(k,n,i)!=n-k+1) continue;
						if (all(1,k-1,i)) continue;
						jia(f[i][k][1],f[i-1][j][1]);
						jia(f[i][k][j!=k&&k!=n+1],f[i-1][j][0]);
				}
		for (i=1;i<=n+1;++i) jia(ans,f[m][i][1]);
}
//处理形如
//B..
//BB.
//BBB 
void gaoB()
{
		memset(f,0,sizeof(f));
		f[0][n][0]=1;
		for (i=1;i<=m;++i)
			for (j=0;j<=n;++j)
				for (k=0;k<=j;++k)
				{
						if (sum(1,k,i)!=k) continue;
						if (all(k+1,n,i)) continue;
						jia(f[i][k][1],f[i-1][j][1]);
						jia(f[i][k][j!=k],f[i-1][j][0]);
				}
		for (i=0;i<=n;++i) jia(ans,f[m][i][0]),jia(ans,f[m][i][1]);
}
//处理形如
//B..
//BB.
//BBB 
void gaoC()
{
		memset(f,0,sizeof(f));
		f[0][1][0]=1;
		for (i=1;i<=m;++i)
			for (j=1;j<=n;++j)
				for (k=j;k<=n;++k)
				{
						if (sum(1,k,i)!=k) continue;
						if (all(k+1,n,i)) continue;
						jia(f[i][k][1],f[i-1][j][1]);
						jia(f[i][k][j!=k&&i!=1],f[i-1][j][0]);
				}
		for (i=0;i<=n;++i) jia(ans,f[m][i][1]);
}
void check(vector<string> v)
{
		n=v.size(); m=v[0].length();
		for (j=1;j<=m;++j) //预处理每列的前缀和 
		{
				for (i=1;i<=n;++i)
				 A[i][j]=(v[i-1][j-1]==v[0][0])+A[i-1][j],
				 B[i][j]=(v[i-1][j-1]=='?')+B[i-1][j];
		}
		gaoA(); 
		gaoB(); 
		gaoC();
}
class TwoConvexShapes{
	public:
		int countWays(vector <string> grid)
		{
				if (grid[0][0]!='?') check(grid); //枚举最左上角的点的颜色 
				else
				{ 
					grid[0][0]='B';
					check(grid);
					grid[0][0]='W';
					check(grid);
				}
				return ans;
		}
}FFT;

int main()
{
	 printf("%d\n",FFT.countWays(vector<string> {"?BB?","BBBB","?BB?"}));
}
