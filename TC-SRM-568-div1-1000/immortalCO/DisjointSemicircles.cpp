#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

int N;
namespace Task1
{
	int M;
	int pair[60];
	bool e[30][30];
	
	struct Edge{int l, r;} edge[30];
	int col[30];
	
	bool color(int i, int c)
	{
		if(col[i] != -1) return col[i] == c;
		col[i] = c;
		for(int j = 0; j != M; ++j)
			if(e[i][j] && !color(j, !c)) return 0;
		return 1;
	}
	
	bool dfs(int i)
	{
		if(i == N)
		{
			for(int i = 0; i != M; ++i) memset(e[i], 0, M);
			int E = 0;
			for(int i = 0; i != N; ++i) if(i < pair[i]) edge[E++] = (Edge) {i, pair[i]};
			for(int i = 0; i != M; ++i) for(int j = i + 1; j != M; ++j) e[i][j] = e[j][i] = (edge[j].l <= edge[i].r && edge[i].r <= edge[j].r);
			memset(col, -1, M << 2);
			for(int i = 0; i != M; ++i) if(col[i] == -1 && !color(i, 0)) return 0;
			return 1;
		}
		if(pair[i] != -1) return dfs(i + 1);
		for(int j = i + 1; j != N; ++j) if(pair[j] == -1)
		{
			pair[i] = j; pair[j] = i;
			if(dfs(i + 1)) return 1;
			pair[i] = pair[j] = -1;
		}
		return 0;
	}
}
namespace Task2
{
	struct Edge{int l, r;} edge[30];
	char e[60][60];
	int col[60];
	
	bool color(int i, int c)
	{
		if(col[i] != -1) return col[i] == c;
		col[i] = c;
		for(int j = 0; j <= N; ++j)
			if(e[i][j] != -1 && !color(j, c ^ e[i][j])) return 0;
		return 1;
	}
}

class DisjointSemicircles
{
public:
	string getPossibility(vector<int> vec)
	{
		N = vec.size();
		// 如果空格很少，可以爆搜边然后二分图染色
		if(count(vec.begin(), vec.end(), -1) <= 10)
		{
			using namespace Task1;
			M = N >> 1;
			for(int i = 0; i != N; ++i) if(vec[i] != -1)
			{
				for(int j = i + 1; j != N; ++j) if(vec[i] == vec[j])
					Task1::pair[i] = j, Task1::pair[j] = i;
			}
			else Task1::pair[i] = -1;
			if(dfs(0)) return "POSSIBLE";
			return "IMPOSSIBLE";
		}
		// 否则怎么搞？
		// 比如我们可以枚举已有的区间在上面还是下面
		// 然后似乎可以用奇怪的 DP 去搞？
		using namespace Task2;
		int E = 0;
		for(int i = 0; i != N; ++i) if(vec[i] != -1)
			for(int j = i + 1; j != N; ++j) if(vec[i] == vec[j])
				edge[E++] = (Edge) {i, j};
		// 枚举！
		for(int S = 1 << (E - 1); S != (1 << E); ++S)
		{
#define get(i) ((S >> (i)) & 1)
			for(int i = 0; i != E; ++i) for(int j = i + 1; j != E; ++j)
				if(get(i) == get(j) && (edge[j].l <= edge[i].r && edge[i].r <= edge[j].r))
					goto skipped;
			for(int i = 0; i <= N; ++i) memset(e[i], -1, (N + 1));
			e[0][N] = e[N][0] = 0;
			for(int i = 0; i != E; ++i)
			{
				int l = edge[i].l, r = edge[i].r, t = get(i);
				e[l][l + 1] = e[l + 1][l] = t;
				e[r][r + 1] = e[r + 1][r] = t;
				e[l][r + 1] = e[r + 1][l] = !(t || (r - l + 1) % 2 == 0);
			}
			memset(col, -1, (N + 1) << 2);
			for(int i = 0; i <= N; ++i) if(col[i] == -1 && !color(i, 0)) goto skipped;
			return "POSSIBLE";
		skipped: ;
		}
		return "IMPOSSIBLE";
	}
}	user;
