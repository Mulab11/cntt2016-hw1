#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;

struct Block {int x, l, r;} blo[2510];
int Blo, T, m;
bool v[2510];

int diff(int a, int b) {return a > b ? a - b : b - a;}
void dfs(int i)
{
	if(v[i]) return;
	v[i] = 1;
	for(int k = 0; k != Blo; ++k)
		if(k != i && diff(blo[i].x, blo[k].x) <= m
		   && blo[i].l <= blo[k].r && blo[k].l <= blo[i].r)
			dfs(k);
}

class ArcadeManao
{
public:
	int shortestLadder(vector<string> inp, int X, int Y)
	{
		const int N = inp.size(), M = inp[0].size();
		if(X == N) return 0;
		--X, --Y;
		for(int i = N; i--; )
			for(int l = 0, r = 0; l != M; l = r)
			{
				if(inp[i][l] == '.') {++r; continue;}
				while(r != M && inp[i][r] == 'X') ++r;
				if(i == X && l <= Y && Y < r) T = Blo;
				blo[Blo++] = (Block) {i, l, r - 1};
			}
		int l = 1, r = N;
		while(l != r)
		{
			m = (l + r) >> 1;
			memset(v, 0, Blo);
			dfs(0);
			v[T] ? r = m : l = m + 1;
		}
		return l;
	}
}	user;
