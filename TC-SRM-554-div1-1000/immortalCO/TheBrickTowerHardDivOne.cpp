#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;

const int mod = 1234567891;
int C, K, S[8], pid[4][4][4][4], self_same[20];

#define SE(a, b) (S[a] == S[b])

typedef unsigned Matrix[121][121];
typedef unsigned Vector[121];
Vector V;
Matrix M;

int total;

// 0 | 1  4 | 5
// - + -  - + -
// 2 | 3  6 | 7
void add(unsigned &a, unsigned b) {(a += b) >= mod ? a -= mod : 0;}

void dfs_init4(int i, int U)
{
	if(U > C) return;
	if(i == 4)
	{
		// 计算初始系数，用排列数计算
		const int same = SE(0, 1) + SE(0, 2) + SE(1, 3) + SE(2, 3);
		if(same <= K)
		{
			int coef = 1;
			for(int i = 0; i != U; ++i)
				coef = (ll) coef * (C - i) % mod;
			V[total * (K + 1) + same] = coef;
			self_same[pid[S[0]][S[1]][S[2]][S[3]] = total++] = same;
		}
		else pid[S[0]][S[1]][S[2]][S[3]] = -1;
		return;
	}
	int &k = S[i];
	for(k = 0; k != U; ++k) dfs_init4(i + 1, U);
	dfs_init4(i + 1, U + 1);
}

int convert_4()
{
	int T[4], *S = ::S + 4, K = 0;
	for(int i = 0; i != 4; ++i)
	{
		for(int j = 0; j != i; ++j)
			if(S[i] == S[j])
			{
				T[i] = T[j];
				goto next_step;
			}
		T[i] = K++;
	next_step: continue;
	}
	return pid[T[0]][T[1]][T[2]][T[3]];
}

int __from_state_U;

void dfs_init8(int i, int U)
{
	if(U > C) return;
	if(i == 4 && pid[S[0]][S[1]][S[2]][S[3]] == -1) return;
	if(i == 4) __from_state_U = U;
	if(i == 8)
	{
		// 判断是否合法，并确定来去状态
		const int from = pid[S[0]][S[1]][S[2]][S[3]], to = convert_4();
		if(to == -1) return;
		const int new_same = self_same[to] + SE(0, 4) + SE(1, 5) + SE(2, 6) + SE(3, 7);
		// 这个转移废弃了！
		if(self_same[from] + new_same > K) return;
		// 计算转移系数，只考虑多出来的数字
		int coef = 1;
		for(int i = __from_state_U; i != U; ++i)
			coef = (ll) coef * (C - i) % mod;
		// 枚举状态进行转移
		for(int p = self_same[from], q = p + new_same; q <= K; ++p, ++q)
			add(M[from * (K + 1) + p][to * (K + 1) + q], coef);
		return;
	}
	int &k = S[i];
	for(k = 0; k != U; ++k) dfs_init8(i + 1, U);
	dfs_init8(i + 1, U + 1);
}

int E;
void mul(Matrix A, Matrix B)
{
	static Matrix C;
	for(int i = 0; i != E; ++i) memset(C[i], 0, E << 2);
	unsigned *Ai, Aik, *Bk, *Ci;
	for(int i = 0, j, k; i != E; ++i)
	{
		Ai = A[i], Ci = C[i];
		for(k = 0; k != E; ++k) if((Aik = Ai[k]))
		{
			Bk = B[k];
			for(j = 0; j != E; ++j)
				add(Ci[j], (ll) Aik * Bk[j] % mod);
		}
	}
	for(int i = 0; i != E; ++i) memcpy(A[i], C[i], E << 2);
}
void mul(Vector A, Matrix B)
{
	static Vector C;
	memset(C, 0, E << 2);
	unsigned Ak, *Bk;
	for(int j, k = 0; k != E; ++k) if((Ak = A[k]))
	{
		Bk = B[k];
		for(j = 0; j != E; ++j) add(C[j], (ll) Ak * Bk[j] % mod);
	}
	memcpy(A, C, E << 2);
}

class TheBrickTowerHardDivOne
{
public:
	int find(int _C, int _K, ll m)
	{
		C = _C, K = _K;
		// 我们状压最上面这一层的颜色划分
		// 先 DFS 预处理转移
		dfs_init4(0, 0);
		dfs_init8(0, 0);
		// P 是前缀和位置
		const int P = total * (K + 1);
		M[P][P] = 1;
		// 预处理一发
		for(int i = 0; i != P; ++i)
		{
			add(V[P], V[i]);
			for(int j = 0; j != P; ++j)
				add(M[i][P], M[i][j]);
		}
		E = P + 1;
		for(--m; m; m >>= 1)
		{
			if(m & 1) mul(V, M);
			if(m > 1) mul(M, M);
		}
		return V[P];
	}
}	user;
