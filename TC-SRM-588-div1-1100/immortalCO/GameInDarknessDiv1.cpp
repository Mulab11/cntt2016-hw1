#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

const int MaxN = 2510;
bool map[60][60];
int n, pid[60][60];
int e[MaxN][5];

int da[MaxN], db[MaxN], *d, dist[MaxN];
void cmax(int &a, int b) {a < b ? a = b : 0;}
int dfs(int p)
{
	int ret = d[p];
	for(int k = 1; k <= *e[p]; ++k)
	{
		if(d[e[p][k]] == -1)
		{
			d[e[p][k]] = d[p] + 1;
			cmax(ret, dfs(e[p][k]));
		}
	}
	return ret;
}

class GameInDarknessDiv1
{
public:
	string check(vector<string> input)
	{
		// 建树
		int R = input.size(), C = input[0].size();
		int A = -1, B = -1;
		for(int i = 1; i <= R; ++i)
			for(int j = 1; j <= C; ++j)
				if((map[i][j] = (input[i - 1][j - 1] != '#')))
				{
					pid[i][j] = ++n;
					if(input[i - 1][j - 1] == 'A') A = n;
					if(input[i - 1][j - 1] == 'B') B = n;
				}
		const int cx[] = {1, -1, 0, 0};
		const int cy[] = {0, 0, 1, -1};
		for(int i = 1; i <= R; ++i)
			for(int j = 1; j <= C; ++j) if(pid[i][j])
				for(int p = pid[i][j], k = 0; k != 4; ++k)
					if(pid[i + cx[k]][j + cy[k]])
						e[p][++*e[p]] = pid[i + cx[k]][j + cy[k]];
		memset((d = da) + 1, -1, n << 2); d[A] = 0; dfs(A);
		memset((d = db) + 1, -1, n << 2); d[B] = 0; dfs(B);
		// 只要有一个有超过 3 个分支深度超过 3，则 Bob 赢
		for(int i = 1; i <= n; ++i) if(da[i] > db[i] + 1)
		{
			memset((d = dist) + 1, -1, n << 2);
			d[i] = 0;	// 删除点 i，检查分支
			int count = 0;
			for(int k = 1; k <= *e[i]; ++k)
			{
				d[e[i][k]] = 1;
				count += (dfs(e[i][k]) >= 3);
			}
			if(count >= 3) return "Bob wins";
		}
		return "Alice wins";
	}
}   user;
