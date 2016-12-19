#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;

struct Edge{int x, y, v;} e[20000];

char input[20000];

int pre[5010], blo[5010], vis[5010], val[5010];

bool cmin(int &a, int b) {return a > b ? a = b, 1 : 0;}

class FoxTheLinguist
{
public:
	int minimalHours(int L, vector<string> inp)
	{
		string buff;
		for(int i = 0; i != (int) inp.size(); ++i) buff += inp[i];
		for(int i = 0; i != (int) buff.size(); ++i) input[i] = buff[i];
		char *iter = input, *end = iter + buff.size();
		int M = 0;
		for(; iter < end; ++iter)
		{
			int x = *iter++ - 'A';
			x = x * 10 + *iter++ - '0';
			++iter;
			++iter;
			int y = *iter++	- 'A';
			y = y * 10 + *iter++ - '0';
			++iter;
			int v = 0;
			v = v * 10 + *iter++ - '0';
			v = v * 10 + *iter++ - '0';
			v = v * 10 + *iter++ - '0';
			v = v * 10 + *iter++ - '0';
			if(x == y) continue;
			e[M++] = (Edge) {x, y, v};
		}
		int N = L * 10;
		for(int i = 0; i != L; ++i)
		{
			// 设起点为 A0，则 A0 向所有点连边
			if(i) e[M++] = (Edge) {0, i * 10, 0};
			for(int j = 1; j <= 9; ++j)
				// 如果可达高级的点，必然也可达低级的点
				e[M++] = (Edge) {i * 10 + j, i * 10 + j - 1, 0};
		}
		// 最小树形图
		const int inf = 1e9;
		int ans = 0;
		for(int root = 0; ; )
		{
			memset(val, 63, N << 2);
			val[root] = 0;
			for(int i = 0; i != M; ++i)
			{
				int x = e[i].x, y = e[i].y;
				if(x == y) continue;
				if(cmin(val[y], e[i].v)) pre[y] = x;
			}
			for(int i = 0; i != N; ++i) if(val[i] > inf) return -1;
			
			int B = 0;
			memset(blo, -1, N << 2);
			memset(vis, -1, N << 2);
			for(int i = 0; i != N; ++i)
			{
				ans += val[i];
				int p = i;
				while(vis[p] != i && blo[p] == -1 && p != root) vis[p] = i, p = pre[p];
				if(vis[p] == i)
				{
					for(int q = pre[p]; q != p; q = pre[q]) blo[q] = B;
					blo[p] = B++;
				}
			}
			if(!B) break;
			for(int i = 0; i != N; ++i) if(blo[i] == -1) blo[i] = B++;
			for(int i = 0; i != M; ++i)
			{
				int x = e[i].x, y = e[i].y;
				e[i].x = blo[x];
				e[i].y = blo[y];
				if(e[i].x != e[i].y)
					e[i].v -= val[y];
			}
			N = B;
			root = blo[root];
		}
		return ans;
	}
}	user;
