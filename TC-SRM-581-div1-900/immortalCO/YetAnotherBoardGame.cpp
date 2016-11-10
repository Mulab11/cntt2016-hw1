#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

int N, M, A = 1e9, C;
bool bak[15][15], map[15][15];
bool type[15];

void modify(int t, int x, int y)
{
	++C;
	if(t) map[x][y] ^= 1;
	map[x - 1][y] ^= 1;
	map[x][y - 1] ^= 1;
	map[x + 1][y] ^= 1;
	map[x][y + 1] ^= 1;
}

void solve(int mod)
{
	mod <<= 1;
	memcpy(map, bak, sizeof map);
	C = 0;
	for(int j = 1; j <= M; ++j) if(mod & 1 << j)
		modify(type[j], 1, j);
	for(int i = 2; i <= N; ++i)
	{
		int used = 0;
		for(int j = 1; j <= M; ++j)
		{
			if(!map[i - 1][j]) continue;
			modify(type[j], i, j);
			used |= 1 << type[j];
		}
		if(used == 3) return;
	}
	for(int j = 1; j <= M; ++j) if(map[N][j]) return;
	if(C < A) A = C;
}

void dfs(int i)
{
	if(i > M)
	{
		// 现在我们要枚举第一行用的是什么修改、哪些位置用了修改
		int A = 0, B = 0;
		for(int i = 1; i <= M; ++i)
			(type[i] ? A : B) |= 1 << (i - 1);
		// 肯定是某一修改的子集咯
		solve(0);
		for(int S = A; S; S = (S - 1) & A) solve(S);
		for(int S = B; S; S = (S - 1) & B) solve(S);
		return;
	}
	type[i] = 0; dfs(i + 1);
	type[i] = 1; dfs(i + 1);
}

class YetAnotherBoardGame
{
public:
	int minimumMoves(vector<string> inp)
	{
		N = inp.size();
		M = inp[0].size();
		for(int i = 1; i <= N; ++i)
			for(int j = 1; j <= M; ++j)
				bak[i][j] = (inp[i - 1][j - 1] == 'W');
		// 枚举每一列执行的是什么操作
		dfs(1);
		return A == 1e9 ? -1 : A;
	}
}	user;
