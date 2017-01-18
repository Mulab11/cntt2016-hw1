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

#define N 105
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k;
struct Node{
	int a,b,c,d;
};
map<Node,int>mp;
inline bool operator <(Node a,Node b)
{
		if (a.a!=b.a) return a.a<b.a;
		if (a.b!=b.b) return a.b<b.b;
		if (a.c!=b.c) return a.c<b.c;
		return a.d<b.d;
}
struct poi{
	int x,y;
}Point[N];
int dfs(int sx,int ex,int sy,int ey)
{
		if (mp.find((Node){sx,ex,sy,ey})!=mp.end()) return mp[(Node){sx,ex,sy,ey}];
		int sum=(int)1e9,f=0,i,j;
		int R[N];
		memset(R,0,sizeof(R));
		for (i=0;i<n;++i)
			if (Point[i].x<sx||Point[i].x>ex||Point[i].y<sy||Point[i].y>ey)
			  	R[i]=1;
		for (i=0;i<n;++i) //枚举下一个能够使得选取的位置变化的点,并将最新不会改变边界的点的贡献全都计算一下 
			if (R[i])
			{
					f=1;
					poi a=Point[i];
					int su=max(abs(a.x-sx),max(abs(a.x-ex),max(abs(a.y-sy),abs(a.y-ey))));
					int nsx=min(sx,a.x),nex=max(ex,a.x),
						nsy=min(sy,a.y),ney=max(ey,a.y);
					for (j=0;j<n;++j)
						if (i!=j&&R[j]&&nsx<=Point[j].x&&Point[j].x<=nex&&
								  		nsy<=Point[j].y&&Point[j].y<=ney)
					{
						poi a=Point[j];
						su+=max(abs(a.x-nsx),max(abs(a.x-nex),max(abs(a.y-nsy),abs(a.y-ney))));
					}
					sum=min(sum,su+dfs(nsx,nex,nsy,ney)); //扩展边界 
			}
		if (!f) sum=0;
		return mp[(Node){sx,ex,sy,ey}]=sum; 
}
class EllysChessboard{
	public:
	int minCost(vector <string> board)
	{
		int nn=board.size();
		m=board[0].length();
		for (i=0;i<nn;++i)
			for (j=0;j<m;++j)
				if (board[i][j]=='#')
					Point[n++]=(poi){i+j,i-j};
		int ans=(int)1e9,f=0;
		for (i=0;i<n;++i) //我们记录当前最小包含已经选取的所有点构成的矩阵 
		ans=min(ans,dfs(Point[i].x,Point[i].x,Point[i].y,Point[i].y)),f=1;
		return ans*f; 
	}
}MRT;

int main()
{
	 cout<<MRT.minCost({".#......",
 "........",
 "..#..#.#",
 "...#..#.",
 "........",
 "...#...#",
 "...#...#",
 "........"});
}

