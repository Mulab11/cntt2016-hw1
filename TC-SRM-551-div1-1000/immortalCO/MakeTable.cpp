#include <cstdio>
#include <cassert>
#include <cstring>
#include <algorithm>
typedef long long ll;
const int mod = 1e9 + 7;
// 打表
// 问题：树上有 A、B、C 三种点，求有多少种生成树满足：
// 1. 每个 B 都和至少一个 B 连边
// 2. 每个 C 只能和 A 连边
// 记录：f[A+B+C][A][B]
int f[50], g[50], v[50], s[50];
int pre[50][50][50], total;
const int P = 40;
char Encode[] = "!#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]^_`abcdefghijklmnopqrstuvwxyz{|}~";
int Decode[256];

int inv(int i) {return i <= 1 ? 1 : mod - (ll) (mod / i) * inv(mod % i) % mod;}
int power(int a, int b)
{
	if(!b) return 1;
	if(!a) return 0;
	int c = 1;
	for(; b; b >>= 1)
	{
		if(b & 1) c = (ll) c * a % mod;
		if(b > 1) a = (ll) a * a % mod;
	}
	return c;
}

void dfs(int D, int B)
{
	// 先计算方案
	{
		++total;
		// 计算系数
		int coef = f[B];
		for(int i = 1; i <= D; ++i) coef = (ll) coef * power(s[i], s[i] - 2) % mod;
		s[D + 1] = -1;
		int len = 0;
		for(int i = 1; i <= D; ++i)
		{
			++len;
			coef = (ll) coef * g[s[i]] % mod;
			// 除掉相同的元素
			if(s[i] != s[i + 1])
				coef = (ll) coef * g[len] % mod, len = 0;
		}
		fprintf(stderr, "[%7d] D = %3d B = %3d coef = %12d S = ", total, D, B, coef);for(int i=1;i<=D;++i) fprintf(stderr, "%d%c", s[i], " \n"[i == D]);if(!D)fprintf(stderr, "\n");

		for(int A = 0; A + B <= P; ++A)
			for(int C = 0; A + B + C <= P; ++C)
			{
				int *s = ::s + 1;
				int M = A + D + C;	
				// 将 B 转为连通块了
				// 初始化基尔霍夫矩阵，计算方案数
				static int G[50][50];
				for(int i = 0; i != M; ++i)
					memset(G[i], 0, M << 2);
				// A 可以向任何点任意连边
				for(int i = 0; i != A; ++i)
				{
					for(int j = i + 1; j != A; ++j)
						G[i][j] = G[j][i] = 1;
					for(int j = 0; j != D; ++j)
						G[i][A + j] = G[A + j][i] = s[j];
					for(int j = 0; j != C; ++j)
						G[i][A + D + j] = G[A + D + j][i] = 1;
				}
				// B 因为已经枚举了连通块所以不能再连边了
				// 处理邻接矩阵
				for(int i = 0; i != M; ++i)
				{
					int sum = 0;
					for(int j = 0; j != M; ++j) if(i != j && G[i][j])
						sum += G[i][j], G[i][j] = -G[i][j];
					G[i][i] = sum;
				}
				// 删掉第 0 行第 0 列
				int ans = coef;
				for(int i = 1; i != M; ++i)
				{
					if(!G[i][i]) goto zero;
					if(G[i][i] < 0) G[i][i] += mod;
					ans = (ll) ans * G[i][i] % mod;
					int d = inv(G[i][i]);
					for(int j = i + 1; j != M; ++j) if(G[j][i])
					{
						int t = (ll) d * G[j][i] % mod;
						for(int k = i; k != M; ++k) if(G[i][k])
							G[j][k] = (G[j][k] - (ll) t * G[i][k]) % mod;
					}
				}
				// 放进 f 里面去
				(pre[A + B + C][A][B] += ans) %= mod;
				zero: ;
			}
	}
	// 再继续枚举划分
	int &S = s[++D];
	for(S = s[D - 1]; S + B <= P; ++S) dfs(D, S + B);
}
char* format(int v)
{
	static char ans[10];
	int n = 0;
	if(!v) ans[n++] = Encode[0];
	else while(v) ans[n++] = Encode[v % 92], v /= 92;
	ans[n] = 0;
	return ans;
}

int main()
{
	for(int i = 0; i != 92; ++i)
		Decode[(int) Encode[i]] = i;
	f[0] = f[1] = g[0] = g[1] = v[0] = v[1] = 1;
	for(int i = 2; i <= P; ++i)
	{
		v[i] = mod - (ll) (mod / i) * v[mod % i] % mod;
		f[i] = (ll) f[i - 1] * i % mod;
		g[i] = (ll) g[i - 1] * v[i] % mod;
		assert(v[i] == inv(i));
		assert(v[i] == power(i, mod - 2));
		assert((ll) f[i] * g[i] % mod == 1);
	}
	s[0] = 2;
	dfs(0, 0);
	printf("char *pre = \"");
	for(int n = 1; n <= P; ++n)
		for(int A = 0; A <= n; ++A)
			for(int B = 0; A + B <= n; ++B)
				printf("%s ", format(pre[n][A][B]));
	putchar('"');
}