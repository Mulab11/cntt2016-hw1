/*
令ok[x][y][x1][y1]表示两个点一开始在(x,y),(x1,y1)，存不存在一种方式使得最后一个到了边界，一个到了一个空白点。这个可以枚举最后到达的状态，
倒着来宽搜，具体就是：假如这一步能走回两个空白点，或者这一步一个点的反方向是墙，另一个点是空白点，相对应的转移到新状态，复杂度o(n^4)。
接下来，令w[x][y]表示与(x,y)不存在合法方式的点数。可以证明，假如(x,y)与(x1,y1)不存在方式，(x1,y1)与(x2,y2)不存在方式，
那么(x,y)与(x2,y2)也不存在方式。那么我们枚举最终选出来集合的大小，枚举选中的一个点，那么合法的方式就是
c(n-1,size - 1) - c(w[x][y],size - 1)，最后方案要除以size(因为每种方案都会计算size次)。
*/
#include <bits/stdc++.h>
#define fe first
#define se second

using namespace std;

typedef pair<short,short> pi;
typedef pair<pi,pi> pii;

const int xy[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
const int mo = int(1e9) + 9;

pii que[45 * 45 * 45 * 45];
bool wal[42][42][42][42];
int inset[45][45],c[1650][1650];

pi operator +(const pi &a,const pi &b) {return pi(a.fe + b.fe,a.se + b.se);}
pi operator -(const pi &a,const pi &b) {return pi(a.fe - b.fe,a.se - b.se);}

class CoinsGame
{
public:
	int n,m;
	vector<string> __b;
	vector<pi> bo;

	bool legal(pi a)
	{
		return a.fe >= 0 && a.fe < n && a.se >= 0 && a.se < m && __b[a.fe][a.se] != '#';
	}

	bool wall(pi a)
	{
		return a.fe >= 0 && a.fe < n && a.se >= 0 && a.se < m && __b[a.fe][a.se] == '#';
	}

	int pow(int a,int b)
	{
		int tmp = 1;
		for(;b;b >>= 1,a = a * 1ll * a % mo)
			if (b & 1) tmp = tmp * 1ll * a % mo;
		return tmp;
	}

	int ways(vector<string> board)
	{
		__b = board;
		bo.clear();
		n = board.size(),m = board[0].length();
		for(int i = 0;i < m;i ++) bo.push_back(pi(-1,i)),bo.push_back(pi(n,i));
		for(int i = 0;i < n;i ++) bo.push_back(pi(i,-1)),bo.push_back(pi(i,m));
		int maxen = 0;
		for(int x = 0;x < n;x ++)
			for(int y = 0;y < m;y ++)
				if (board[x][y] != '#')
					for(auto p = bo.begin();p != bo.end();p ++) //枚举最终两点的终止位置
					{
						int fi = 1,en = 1;
						que[fi] = pii(pi(x,y),pi(p->fe,p->se));//宽搜
						for(;fi <= en;fi ++)
						{
							maxen = max(maxen,en);
							pi u = que[fi].fe,v = que[fi].se; //枚举所有可能的走法
							for(int i = 0;i < 4;i ++)
							{
								pi nu = u + pi(xy[i][0],xy[i][1]);
								pi nv = v + pi(xy[i][0],xy[i][1]);
								if (legal(nu) && legal(nv))
								{
									bool &f = wal[nu.fe][nu.se][nv.fe][nv.se];
									if (!f) 
									{
										f = 1;
										wal[nv.fe][nv.se][nu.fe][nu.se] = 1;
										que[++ en] = pii(nu,nv);
									}
								}
								nu = u - pi(xy[i][0],xy[i][1]);
								if (wall(nu) && legal(nv) && legal(u))
								{	
									bool &f = wal[u.fe][u.se][nv.fe][nv.se];
									if (!f)
									{
										wal[nv.fe][nv.se][u.fe][u.se] = 1;
										f = 1;
										que[++ en] = pii(u,nv);
									}
								}
								nu = u + pi(xy[i][0],xy[i][1]);
								nv = v - pi(xy[i][0],xy[i][1]);
								if (wall(nv) && legal(nu) && legal(v))
								{
									bool &f = wal[nu.fe][nu.se][v.fe][v.se];
									if (!f)
									{
										wal[v.fe][v.se][nu.fe][nu.se] = 1;
										f = 1;
										que[++ en] = pii(nu,v);
									}
								}
							}
						}
					}
		int ans = 0,co = 0;
		for(int x = 0;x < n;x ++)
				for(int y = 0;y < m;y ++)
					if (__b[x][y] != '#')
					{
						++ co;
						int c = 0;
						for(int x1 = 0;x1 < n;x1 ++)
							for(int y1 = 0;y1 < m;y1 ++)
								if (!(x == x1 && y == y1) && __b[x1][y1] != '#' && !wal[x][y][x1][y1]) 
									inset[x][y] ++; //不能和x,y分辨出的点数
					}
		for(int i = 0;i <= n * m;i ++)
		{
			c[i][0] = 1;
			for(int j = 1;j <= i;j ++) c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mo;
		}
		for(int siz = 2;siz <= n * m;siz ++)
		{
			int cur = 0;
			for(int x = 0;x < n;x ++)
				for(int y = 0;y < m;y ++)
					if (__b[x][y] != '#')
						cur = (cur + c[co - 1][siz - 1] - c[inset[x][y]][siz - 1]) % mo; //总的减去不合法的
			ans = (ans + 1ll * (cur + mo) % mo * pow(siz,mo - 2)) % mo;
		}
		return ans;
	}
};
