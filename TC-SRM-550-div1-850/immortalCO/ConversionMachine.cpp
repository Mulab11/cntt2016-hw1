#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long ll;
const int mod = 1e9 + 7;

typedef int Vector[80];
typedef int Matrix[80][80];
int N = 1, pos[20][20];
Vector V;
Matrix M;

void mul(Vector V, Matrix M)
{
	static Vector T;
	memset(T, 0, N << 2);
	register int k, j, vk, *mk;
	for(k = 0; k != N; ++k) if((vk = V[k]))
		for(mk = M[k], j = 0; j != N; ++j)
			T[j] = (T[j] + (ll) vk * mk[j]) % mod;
	memcpy(V, T, N << 2);
}
void mul(Matrix A, Matrix B)
{
	static Matrix C;
	register int i, k, j, *ai, *bk, *ci, aik;
	for(i = 0; i != N; ++i) memset(C[i], 0, N << 2);
	for(i = 0; i != N; ++i)
		for(ai = A[i], ci = C[i], k = 0; k != N; ++k) if((aik = ai[k]))
			for(bk = B[k], j = 0; j != N; ++j) ci[j] = (ci[j] + (ll) aik * bk[j]) % mod;
	for(i = 0; i != N; ++i) memcpy(A[i], C[i], N << 2);
}

class ConversionMachine
{
public:
	int countAll(string s, string t, vector<int> input_cost, int _lim)
	{
		const int ring = input_cost[0] + input_cost[1] + input_cost[2];
		const int cost[3][3] =
		{
			{0, input_cost[0], input_cost[0] + input_cost[1]},
			{input_cost[1] + input_cost[2], 0, input_cost[1]},
			{input_cost[2], input_cost[2] + input_cost[0], 0}
		};
		const int pace[3][3] =
		{
			{0, 1, 2},
			{2, 0, 1},
			{1, 2, 0}
		};
		const int n = s.size();
		// 必须执行的费用和步骤
		int need = 0, c1 = 0, c2 = 0;
		long long lim = _lim; // 有可能减一下爆了！！！！！！！！！！
		for(int i = 0; i != n; ++i)
		{
			lim		-= cost[s[i] - 'a'][t[i] - 'a'];
			need	+= pace[s[i] - 'a'][t[i] - 'a'];
			if(pace[s[i] - 'a'][t[i] - 'a'] == 1) ++c1;
			if(pace[s[i] - 'a'][t[i] - 'a'] == 2) ++c2;
		}
		// 判断无解
		if(lim < 0) return 0;
		// 构造转移矩阵
		// 距离目标 1、 2 的位置个数分别为 a 和 b
		for(int a = 0; a <= n; ++a)
			for(int b = 0; a + b <= n; ++b)
				pos[a][b] = N++;
		for(int a = 0; a <= n; ++a)
			for(int b = 0; a + b <= n; ++b)
			{
				// 考虑此状态能转移给什么状态
				const int p = pos[a][b], c = n - a - b;
				if(a) M[p][pos[a - 1][b]]		 = a;
				if(b) M[p][pos[a + 1][b - 1]]	 = b;
				if(c) M[p][pos[a][b + 1]]		 = c;
			}
		//维护前缀和
		M[0][0] = 1;
		for(int i = 1; i != N; ++i) M[i][0] = M[i][1];
		V[pos[c1][c2]] = 1;
		if(!c1 && !c2) V[0] = 1;
		// 矩阵快速幂
		// m 为可以移动的步数
		int m = need + (lim / ring) * 3;
		for(; m; m >>= 1)
		{
			if(m & 1) mul(V, M);
			if(m > 1) mul(M, M);
		}
		return V[0];
	}
}	user;
