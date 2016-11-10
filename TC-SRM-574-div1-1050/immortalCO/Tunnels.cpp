#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

const int X[] = {1, -1, 0, 0};
const int Y[] = {0, 0, 1, -1};
char map[60][60];
int N, M, C, pid[60][60];

struct Block
{
	int u, d, l, r;
	bool ul, ur, dl, dr;
} blo, empty;

void dfs_0(int i, int j)
{
	if(map[i][j] != 1) return;
	map[i][j] = -1;
	pid[i][j] = C;
	
	blo.u = min(blo.u, i);
	blo.d = max(blo.d, i);
	blo.l = min(blo.l, j);
	blo.r = max(blo.r, j);
	
	
	for(int k = 0; k != 4; ++k)
		dfs_0(i + X[k], j + Y[k]);
}
void dfs_1(int i, int j)
{
	if(map[i][j] != -1) return;
	map[i][j] = 0;
	for(int k = 0; k != 4; ++k)
		dfs_1(i + X[k], j + Y[k]);
}

int pig(int i, int j)
{
	int s = -1, t = -1;
	for(; ; )
	{
		int c = 0, p = -1, q = -1;
		for(int k = 0; k != 4; ++k)
		{
			int x = i + X[k];
			int y = j + Y[k];
			if((x == s && y == t) || pid[x][y] != C) continue;
			++c, p = x, q = y;
		}
		if(!c) break;
		if(c > 1) return 0;
		s = i, i = p;
		t = j, j = q;
	}
	int r = 0;
	if(j == 1) r |= 1;
	if(j == M) r |= 2;
	if(!r) r = 4;
	return r;
}

struct Event
{
	int x, v;
	bool operator < (const Event& eve) const
	{
		return x < eve.x;
	}
} eve[210];

int f[2][55][55];

inline void cmax(int &a, int b) {if(a < b) a = b;}

class Tunnels
{
public:
	int minimumTunnels(vector<string> inp)
	{
		// 先 floodfill
		// 如果两个连通块共享一层，则不是同一个管道
		// 如果某个连通块的最后一层不贴着壁和底，则其必然是结尾
		// 如果不是结尾，那么可以和下面同一个贴着同一个壁、而且贴着壁这一层是最高的组合
		N = inp.size(), M = inp[0].size();
		bool Have = 0;
		for(int i = 1; i <= N; ++i)
			for(int j = 1; j <= M; ++j)
				Have |= (map[i][j] = (inp[i - 1][j - 1] == 'X'));
		
		// 特判 M=1 的情况
		if(M == 1) return Have;
		
		int cnt = 0, Eve = 0;
		for(int i = 1; i <= N; ++i)
			for(int j = 1; j <= M; ++j)
				if(map[i][j])
				{
					++C;
					blo = empty;
					blo.u = blo.d = i;
					blo.l = blo.r = j;
					dfs_0(i, j);
					dfs_1(i, j);
					int k = j;
					while(pid[i][k + 1] == C) ++k;
					int tmp;
					// 这里要特判长度为 2 的贴壁的方块
					if((i == 1 || j == 1) && (tmp = pig(i, j)))
					{
						if(j == 1 && i != 1) blo.ul = 1;
						if(i == 1 || blo.r - blo.l >= 1 || blo.d - blo.u > 1)
						{
							blo.dl |= (tmp & 1);
							blo.dr |= (tmp & 2);
						}
					}
					if((i == 1 || k == M) && (tmp = pig(i, k)))
					{
						if(k == M && i != 1) blo.ur = 1;
						if(i == 1 || blo.r - blo.l >= 1 || blo.d - blo.u > 1)
						{
							blo.dl |= (tmp & 1);
							blo.dr |= (tmp & 2);
						}
					}
					++cnt;
					if(blo.u == blo.d && blo.l == 1 && blo.r == M) // 一整行
						eve[Eve++] = (Event) {i, 0};
					else
					{
						// 结论：上面下面最多只有一个是可以接在外面的
						if(blo.ul) eve[Eve++] = (Event) {blo.u, -1};
						if(blo.ur) eve[Eve++] = (Event) {blo.u, -2};
						if(blo.dl) eve[Eve++] = (Event) {blo.d, 1};
						if(blo.dr) eve[Eve++] = (Event) {blo.d, 2};
					}
				}
		sort(eve, eve + Eve);
		bool d = 0;
		memset(f[d], -63, sizeof f[d]);
		f[d][0][0] = 0;
		// f(i, l, r) ：做到 i，左边有 l 个 d 要匹配，右边有 r 个 d 要匹配
		for(int i = 0, v; i != Eve; ++i)
		{
			d ^= 1;
			memcpy(f[d], f[!d], sizeof f[d]);
			int (*f)[55] = ::f[d], (*g)[55] = ::f[!d];
			switch(eve[i].v)
			{
				case 0: // 线
					for(int l = 0; l <= M; ++l) for(int r = 0; r <= M; ++r)
						if((v = g[l][r]) >= 0)
						{
							if(l) cmax(f[l - 1][r + 1], v + 1); // ul 被匹配，新增 dr
							if(r) cmax(f[l + 1][r - 1], v + 1); // ur 被匹配，新增 dl
							cmax(f[l][r + 1], v);
							cmax(f[l + 1][r], v);
						}
					break;
					
				case -1: // ul
					for(int l = 0; l <= M; ++l) for(int r = 0; r <= M; ++r)
						if((v = g[l][r]) >= 0 && l) cmax(f[l - 1][r], v + 1);
					break;
					
				case -2: // ur
					for(int l = 0; l <= M; ++l) for(int r = 0; r <= M; ++r)
						if((v = g[l][r]) >= 0 && r) cmax(f[l][r - 1], v + 1);
					break;
					
				case 1: // dl
					for(int l = 0; l <= M; ++l) for(int r = 0; r <= M; ++r)
						if((v = g[l][r]) >= 0) cmax(f[l + 1][r], v);
					break;
					
				case 2: // dr
					for(int l = 0; l <= M; ++l) for(int r = 0; r <= M; ++r)
						if((v = g[l][r]) >= 0) cmax(f[l][r + 1], v);
					break;
			}
		}
		int max = 0;
		for(int l = 0; l <= M; ++l) for(int r = 0; r <= M; ++r) cmax(max, f[d][l][r]);
		return cnt - max;
	}
}	user;
