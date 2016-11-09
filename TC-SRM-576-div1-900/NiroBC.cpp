#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#define NiroBC
const long long MOD = 1000000009;
char fragment[10][10];
int W, N, n, m, D, L, cnt[50], E;
long long pr[50], d[2000000];
void dfs(int k, long long s) // 这个dfs是用来分解质因数的
{
	if (k == D)
		d[++L] = s;
	else
		for (int i = 0; i <= cnt[k]; i++)
			dfs(k + 1, s), s *= pr[k];
}
void list(long long w) // 把w的各个正因数append到d数组中
{
	D = 0;
	for (long long i = 2; i * i <= w; i++)
		if (w % i == 0)
		{
			pr[D] = i, cnt[D] = 0;
			while (w % i == 0)
				w /= i, cnt[D]++;
			D++;
		}
	if (w > 1)
		pr[D] = w, cnt[D++] = 1;
	dfs(0, 1);
}
long long POWER(long long a, long long b)
{
	long long r = 1;
	for (; b; b >>= 1)
	{
		if (b & 1)
			r = r * a % MOD;
		a = a * a % MOD;
	}
	return r;
}
long long segPOWER(long long a, long long l, long long r) // \sum_{i=l}^{r}(a^i) 当然我是不会让a等于1的
{
	return (POWER(a, r + 1) - POWER(a, l) + MOD) * POWER(a - 1, MOD - 2) % MOD;
}
struct stupid
{
	int A;
	char B;
}
p[23333];
inline bool operator < (const stupid &a, const stupid &b)
{
	return a.A < b.A;
}
int MAIN()
{
	L = 0;
	for (int i = 1; i < m; i++)
		list(i);
	for (int j = 1; j < n; j++)
		for (int k = -m + 1; k < m; k++)
			list((long long)j * W + k); // 一个L是不理想的，当且仅当他是某个j*W+k的约数，我就把所有这样的L找出来，剩下的都是理想的
	std::sort(d + 1, d + L + 1);
	bool prin = 0;
	L = std::unique(d + 1, d + L + 1) - d - 1; // 从此之后所有不理想的L被存在了d[1..L]
    /* 程序中的那个L不是真的L啊，就是不理想的L的个数的意思！此L非彼L啊！ */
    /* 就当我词穷取不出名字了吧，我真的对单个大写字母的变量名情有独钟，别打我！ */
    /* 我知道拥有智慧的人是能够读懂我的代码的 */
	long long S = 0;
	if (d[1] > 1)
		S = (S + segPOWER(26, 1 - n * m, d[1] - 1 - n * m)) % MOD; // 当 L in [1,d[1])
	while (d[L] > W) // 1<=L<=W 那超出的也没啥个用场
		L--;
	for (int i = 1; i < L; i++)
		if (d[i + 1] - d[i] > 1)
			S = (S + segPOWER(26, d[i] + 1 - n * m, d[i + 1] - 1 - n * m)) % MOD; // 当 L in (d[i],d[i+1])
	if (d[L] < W)
		S = (S + segPOWER(26, d[L] + 1 - n * m, W - n * m)) % MOD; // 当 L in (d[L],W]
	for (int i = 1; i <= L; i++) // 当 L == d[i]，于是所有 L in [1,W] 的情况都统计完啦！
	{
		E = 0;
		for (int x = 0; x < n; x++)
			for (int y = 0; y < m; y++)
				p[E++] = (stupid) { (int)(((long long)x * W + y) % d[i]), fragment[x][y] };
        /* 上文 (stupid) { A, B } 代表 s的第A位 = B 的一个限制 */
		std::sort(p, p + E);
		bool kill = 0;
		int s = n * m;
		for (int j = 1; j < E; j++)
			if (p[j - 1].A == p[j].A)
			{
				if (p[j - 1].B != p[j].B)
					kill = 1; // 出现矛盾啦，死掉！
				s--; // 重叠了。那少算一个！
			}
		if (!kill)
			S = (S + POWER(26, d[i] - s)) % MOD;
	}
	return S;
}
class CharacterBoard
{
	public :
		int countGenerators(std::vector < std::string > fragment, int W, int i0, int j0)
		{
			n = fragment.size(), m = fragment[0].length();
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					::fragment[i][j] = fragment[i][j];
			::W = W;
            /* 辣鸡TC！为什么要把全局都要被调用的变量放在class的某个成员函数的参数表中呢！*/
            /* 还要麻烦我把他们复制出去，真麻烦！ */
            /* 我知道大家都不像我这样简单粗暴地做TC的，希望如此，世界和平 */
			return MAIN();
		}
};