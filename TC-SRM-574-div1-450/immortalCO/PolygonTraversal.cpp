#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

#include <bitset>

int id[18][18];
ll f[1 << 18][18];
bitset<160> lim[18][18];

class PolygonTraversal
{
public:
	ll count(int N, vector<int> last)
	{
		// 猜一个结论：只要新建的边，存在一对点，使得某一端点在里面，另一端点在外面，则满足题意
		int S = 0;
		for(int i = 0; i != (int) last.size(); ++i)
			S |= 1 << --last[i];
		f[S][last.back()] = 1;
		int F = (1 << N) - 1, E = 0;
		for(int i = 0; i != N; ++i)
			for(int j = i + 1; j != N; ++j)
				id[i][j] = id[j][i] = E++;
		// 预处理相交的直线对
		for(int i = 0; i != N; ++i)
			for(int j = i + 1; j != N; ++j)
			{
				bitset<160> L;
				for(int a = 0; a != N; ++a) if(a != i && a != j)
					for(int b = a + 1; b != N; ++b) if(b != i && b != j)
						if((a < i && i < b) != (a < j && j < b))
							L.set(id[a][b]);
				lim[i][j] = lim[j][i] = L;
			}
		ll V, A = 0;
		for(; S != (1 << N); ++S)
		{
			bitset<160> E;
			for(int i = 0; i != N; ++i) if(S & 1 << i)
				for(int j = i + 1; j != N; ++j) if(S & 1 << j)
					E.set(id[i][j]);
			for(int i = 0; i != N; ++i) if(f[S][i])
			{
				V = f[S][i];
				if(S == F)
				{
					if((E & lim[i][last.front()]).count())
						A += V;
					continue;
				}
				for(int T = F - S, k; T; T -= 1 << k)
				{
					k = __builtin_ctz(T);
					if(!(E & lim[i][k]).count()) continue;
					f[S | 1 << k][k] += V;
				}
			}
		}
		return A;
	}
}	user;
