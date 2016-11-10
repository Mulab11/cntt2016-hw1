#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7;

int val[110];
bool vis[110];
int N, map[60][60];

bool dfs(int i)
{
	vis[i] = 1;
	const int v = val[i];
	for(int j = 0; j != N; ++j)
	{
		int mp = (i < N ? map[i][j] : map[j][i - N]);
		int k = (i < N) ? j + N : j;
		if(mp == -1) continue;
		
		if(v > mp) return 0;
		else if(val[k] != -1)
		{if(val[k] + v != mp) return 0;}
		else
		{
			val[k] = mp - v;
			if(!dfs(k)) return 0;
		}
	}
	return 1;
}

class EqualSums
{
public:
	int count(vector<string> inp)
	{
		// 神题
		// 矩阵可以表示 M(i,j) = A(i) + B(j) 的形式
		N = inp.size();
		for(int i = 0; i != N; ++i)
			for(int j = 0; j != N; ++j)
				map[i][j] = (inp[i][j] == '-') ? -1 : inp[i][j] - '0';
		int A = 1, B = 1;
		for(int i = 0; i != N; ++i) if(!vis[i])
		{
			int a = 0, b = 0;
			for(int k = 0; k <= 9; ++k)
			{
				memset(val, -1, N << 3);
				val[i] = k;
				if(!dfs(i)) continue;
				++a;
				if(!std::count(val, val + N, 0)) ++b;
			}
			A = (ll) A * a % mod;
			B = (ll) B * b % mod;
		}
		return (A - B + mod) % mod;
	}
}	user;
