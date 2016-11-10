#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
typedef long long ll;
typedef long double ld;

const int mod = 1e9 + 7;
int N, M, L;
bool S;
char map[55][55];

int diff(int a, int b) {return a > b ? a - b : b - a;}
void dfs(int x, int y)
{
	S ^= 1;
	map[x][y] = 0;
	for(int p = x - L; p <= x + L; ++p)
		for(int q = y - L; q <= y + L; ++q)
			if(p >= 0 && p <= N && q >= 0 && q <= M
			   && map[p][q] == 'v' && diff(x, p) + diff(y, q) <= L)
				dfs(p, q);
}

class GooseInZooDivOne
{
public:
	int count(vector<string> inp, int dist)
	{
		N = inp.size(), M = inp.front().size(), L = dist;
		for(int i = 0; i != N; ++i)
			for(int j = 0; j != M; ++j)
				map[i][j] = inp[i][j];
		int f[2][2][2];
		memset(f, 0, sizeof f);
		f[0][0][0] = 1;
		bool d = 0;
		for(int i = 0; i != N; ++i)
			for(int j = 0; j != M; ++j)
				if(map[i][j] == 'v')
				{
					S = 0;
					dfs(i, j);
					memset(f[d ^= 1], 0, sizeof f[0]);
					for(int a = 0; a != 2; ++a)
						for(int b = 0; b != 2; ++b)
						{
							(f[d][a ^ S][1] += f[!d][a][b]) %= mod;
							(f[d][a][b] += f[!d][a][b]) %= mod;
						}
				}
		return f[d][0][1];
	}
}	user;
