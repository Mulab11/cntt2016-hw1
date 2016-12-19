#include <bits/stdc++.h>
using namespace std;

#ifdef assert
#undef assert
#define assert(x) ((x) ? (void) 1 : (fprintf(stderr, "Assertion \"%s\" failed on line %d.\n", #x, __LINE__), exit(6)))
#endif

int pos[55][55];
vector<int> e[2505];
int col[2505];

bool dfs(int i, int c)
{
	if(col[i] == c) return 0;
	if(col[i] + c == 0) return 1;
	col[i] = c;
	for(int k = e[i].size(); k--; )
		if(dfs(e[i][k], -c)) return 1;
	return 0;
}

class HexagonalBoard
{
public:
	int minColors(vector<string> map)
	{
		const int N = map.size();
		int P = 0;
		for(int i = 0; i != N; ++i)
			for(int j = 0; j != N; ++j)
				if(map[i][j] == 'X')
					pos[i + 1][j + 1] = ++P;
		if(!P) return 0;
		const int EX[] = {00, -1, -1, 00, +1, +1};
		const int EY[] = {-1, 00, +1, +1, 00, -1};
		for(int i = 1; i <= N; ++i)
			for(int j = 1; j <= N; ++j) if(pos[i][j])
				for(int k = 0; k != 6; ++k)
					if(pos[i + EX[k]][j + EY[k]])
						e[pos[i][j]].push_back(pos[i + EX[k]][j + EY[k]]);
		int max = 0;
		for(int i = 1; i <= P; ++i) if((int) e[i].size() > max) max = e[i].size();
		if(max == 0) return 1;
		for(int i = 1; i <= P; ++i) if(!col[i] && dfs(i, 1)) return 3;
		return 2;
	}
}	user;
