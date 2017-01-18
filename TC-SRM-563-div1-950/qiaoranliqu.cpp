#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<bitset>
#include<cmath>
#include<string>

#define ls (t<<1)
#define rs ((t<<1)+1)
#define mid ((l+r)>>1)
#define fi first
#define se second
#define mk make_pair
#define pb push_back

#define N 2000005
#define M 45
#define seed 23333
#define Mo 1000000009

using namespace std;
int i,j,m,n,p,k,ID[M][M][M][M],ans,tot,l;
char c[M][M];
int power(int x,int y)
{
		int sum=1;
		for (;y;y>>=1)
		{
			 if (y&1) sum=1ll*sum*x%Mo;
			 x=1ll*x*x%Mo; 
		}
		return sum;
}
const int x[4]={0,0,-1,1};
const int y[4]={-1,1,0,0};
int vis[M][M],e[M][M];
struct Point{int x,y;}Q[M*M];
int check(int x,int y)
{
	if (x<0||y<0||x>=n||y>=m||vis[x][y]||c[x][y]=='#') return 0;
	return 1;
}
int good(int x,int y)
{
	if (x<0||y<0||x>=n||y>=m) return 0;
	return 1;
}
int bfs() //第一种情况是所有的点都永远无法移出边界,即在封闭的联通块内 
{
		int l=1,r=0;
		for (i=0;i<m;++i) Q[++r]=(Point){-1,i};
		for (i=0;i<n;++i) Q[++r]=(Point){i,-1};
		for (i=0;i<n;++i) Q[++r]=(Point){i,m};
		for (i=0;i<m;++i) Q[++r]=(Point){n,i};
		for (l=1;l<=r;++l)
		{
				int ax=Q[l].x,ay=Q[l].y;
				for (i=0;i<4;++i)
					if (check(ax+x[i],ay+y[i]))
					{
						vis[ax+x[i]][ay+y[i]]=1;
						Q[++r]=(Point){ax+x[i],ay+y[i]};
					}
		}
		int cnt=0;
		for (i=0;i<n;++i)
			for (j=0;j<m;++j)
				if (c[i][j]=='.'&&!vis[i][j]) ++cnt;
		return power(2,cnt)-1;
}
bool v[M][M][M][M];
int r;
struct Node{
		int sx,sy,ex,ey;
}Que[N];
void Push(int a,int b,int c,int d)
{
		if (a<0||b<0||c<0||d<0||a>=n||b>=m||c>=n||d>=m) return;
		if (a>c) swap(a,c),swap(b,d);
		if (a==c&&b>d) swap(a,c),swap(b,d);
		if (!v[a][b][c][d])
		{
				v[a][b][c][d]=1;
				Que[++r]=(Node){a,b,c,d};
		}
}
int work() //否则,考虑从一个恰好有一个棋子掉出去的状态开始还原,能够还原到的状态都是合法点对 
{
	int l=1; r=0;
	for (i=0;i<n;++i)
		for (j=0;j<m;++j)
			if (c[i][j]=='.')
			{
					for (k=0;k<n;++k) 
						Que[++r]=(Node){i,j,k,-1},Que[++r]=(Node){k,-1,i,j},
						Que[++r]=(Node){i,j,k,m},Que[++r]=(Node){k,m,i,j};
					for (k=0;k<m;++k)
						Que[++r]=(Node){i,j,-1,k},Que[++r]=(Node){-1,k,i,j},
						Que[++r]=(Node){i,j,n,k},Que[++r]=(Node){n,k,i,j};
					
			}
	memcpy(e,vis,sizeof(e));
	memset(vis,0,sizeof(vis));
	for (;l<=r;++l)
	{
			int sx=Que[l].sx,sy=Que[l].sy,ex=Que[l].ex,ey=Que[l].ey;
			for (i=0;i<4;++i) //枚举还原的方向 
			{
					if (check(sx-x[i],sy-y[i])&&check(ex-x[i],ey-y[i])) 
					Push(sx-x[i],sy-y[i],ex-x[i],ey-y[i]);
					if (check(sx-x[i],sy-y[i])&&good(ex+x[i],ey+y[i])&&c[ex+x[i]][ey+y[i]]=='#')
					Push(sx-x[i],sy-y[i],ex,ey);
					if (good(sx+x[i],sy+y[i])&&c[sx+x[i]][sy+y[i]]=='#'&&check(ex-x[i],ey-y[i]))
					Push(sx,sy,ex-x[i],ey-y[i]);
					if (good(ex+x[i],ey+y[i])&&good(sx+x[i],sy+y[i])&&c[sx+x[i]][sy+y[i]]=='#'&&c[ex+x[i]][ey+y[i]]=='#')
					Push(sx,sy,ex,ey); 
			}
	}
	memcpy(vis,e,sizeof(e));
	int ans=0;
	for (i=0;i<n;++i)
		for (j=0;j<m;++j)
			if (vis[i][j]==1) //对于与(i,j)一定状态相同的(k,l)和(k',l'),他们的状态也必定相同. 
			{
				int cnt=0;
				for (k=0;k<n;++k)
					for (l=0;l<m;++l)
						if (vis[k][l]==1&&!v[i][j][k][l]&&!v[k][l][i][j]) 
							cnt++,vis[k][l]=0;
				ans=(ans+power(2,cnt)-1)%Mo;
			}
	return ans;
}
class CoinsGame{
	public:
		int ways(vector <string> board)
		{ 
			int cnt=0;
			n=board.size(); m=board[0].length();
			for (i=0;i<n;++i) 
				for (j=0;j<m;++j) 
				{
					c[i][j]=board[i][j];
					if (c[i][j]=='.') ++cnt; 
				}
			ans=power(2,cnt)-1; //考虑利用容斥,转化为计算一定会同时移出的个数. 
			ans=(ans-bfs()+Mo)%Mo;  
			ans=(ans-work()+Mo)%Mo;
			return ans;
		}
}ETT;

int main()
{
	 cout<<ETT.ways({"........",
 "........",
 "........",
 "........",
 "........",
 "........",
 "........",
 "........"});
}

