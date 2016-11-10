#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

int N, M, R, C, E, lim;
int f[1594323];
bool g[1594323];
// f：走到这一步的时候，我能取得的最大金币数
int pid[13][13], s[13];
int e_l[26], e_r[26], e_c[13], p3[14], cnt[3];

// 输出方程
void print_e()
{
	puts("Equation:");
	for(int i = 0; i != E; ++i)
	{
		printf("e[%d] : ", i);
		for(int j = 0; j != N; ++j)
			putchar("01"[(e_l[i] >> j) & 1]);
		printf(" = %d\n", e_r[i]);
	}
}

// 导出 S 到数组 s
void Export(int S)
{
	memset(s, 0, N << 2);
	for(int i = 0; S; ++i, S /= 3) s[i] = S % 3;
	memset(cnt, 0, sizeof cnt);
	for(int i = 0; i != N; ++i) ++cnt[s[i]];
}
// 判断是否合法
bool pig()
{
	// 先判断有没有太少、太多
	if(cnt[0] + cnt[1] < M || cnt[1] > M) return 0;
	// 现在判断方程是否有解
	static int L[26], R[26];
	memcpy(L, e_l, E << 2);
	memcpy(R, e_r, E << 2);
	bool v;
	int t, k;
	for(int i = 0; i != N; ++i) if(s[i])
	{
		v = (s[i] == 1);
		for(t = e_c[i]; t; t -= 1 << k)
		{
			k = __builtin_ctz(t);
			L[k] ^= 1 << i;
			R[k] ^= v;
			// 方程挂掉
			if(!L[k] && R[k]) return 0;
		}
	}
	return 1;
}

class MagicalHats
{
public:
	int findMaximumReward(vector<string> map, vector<int> value, int _lim)
	{
		// 对抗搜索
		// set 是一个三进制数，表示第 i 个帽子中 0. 未被打开 1. 被打开且有金币 2. 被打开且没金币
		// 必须有金币的充分条件是：1. 帽子数 <= 金币数 2. 这一位置不取会造成冲突
		N = 0, M = value.size(), R = map.size(), C = map[0].size(), lim = _lim;
		int N_R[13] = {}, N_C[13] = {};
		for(int i = 0; i != R; ++i)
			for(int j = 0; j != C; ++j)
				if(map[i][j] == 'H')
				{
					pid[i][j] = N++;
					++N_R[i];
					++N_C[j];
				}
		// 预处理异或方程组
		for(int i = 0; i != R; ++i) if(N_R[i])
		{
			e_r[E] = N_R[i] & 1;
			for(int j = 0; j != C; ++j)
				if(map[i][j] == 'H')
					e_l[E] |= 1 << pid[i][j];
			++E;
		}
		for(int j = 0; j != C; ++j) if(N_C[j])
		{
			e_r[E] = N_C[j] & 1;
			for(int i = 0; i != R; ++i)
				if(map[i][j] == 'H')
					e_l[E] |= 1 << pid[i][j];
			++E;
		}
		// 先消一波!
		for(int i = 0; i != E; ++i)
		{
			// 找到第一位的 1
			int tmp = 0;
			for(int j = i; j != E; ++j) tmp |= e_l[j];
			if(!tmp) break;
			// 找到第 i 行
			int p = __builtin_ctz(tmp);
			for(int j = i; ; ++j)
				if(e_l[j] & (1 << p))
				{
					swap(e_l[i], e_l[j]);
					swap(e_r[i], e_r[j]);
					break;
				}
			// 消元（暴力把上面也顺便消掉）
			int L = e_l[i], R = e_r[i];
			for(int j = 0; j != E; ++j)
				if(j != i && (e_l[j] & (1 << p)))
				{
					e_l[j] ^= L;
					e_r[j] ^= R;
				}
		}
		for(int i = 0; i != E; ++i)
		{
			// 判断一次无解
			if(!e_l[i] && e_r[i]) return -1;
			// 预处理包含每一位的方程
			for(int k = 0; k != N; ++k)
				if(e_l[i] & (1 << k)) e_c[k] |= 1 << i;
		}
		// 开始状压 DP!
		int S = 1;
		for(int i = 0; i != N; ++i) p3[i] = S, S *= 3;
		p3[N] = S;
		// 处理每个状态是否可以到达
		while(S--)
		{
			Export(S);
			if(cnt[1] + cnt[2] == N) g[S] = pig();
			else for(int i = 0; i != N; ++i)
				if(!s[i] && (g[S + p3[i] * 1] || g[S + p3[i] * 2]))
				{g[S] = 1; break;}
		}
		if(!g[0]) return -1;
		int tmp_1, tmp_2;
#define cmax(a, b) ((a) < (b) ? (a) = (b) : 0)
		S = p3[N];
		// DP
		while(S--)
		{
			Export(S);
			if(!g[S] || cnt[1] + cnt[2] > lim) f[S] = -1e9;
			else if(cnt[1] + cnt[2] == lim) f[S] = cnt[1];
			else
			{
				f[S] = -1e9;
				for(int i = 0; i != N; ++i) if(!s[i])
				{
					tmp_1 = f[S + p3[i] * 1];
					tmp_2 = f[S + p3[i] * 2];
					(tmp_2 < 0 || (tmp_1 >= 0 && tmp_1 < tmp_2))
					? cmax(f[S], tmp_1)
					: cmax(f[S], tmp_2);
				}
			}
		}
		if(f[0] < 0) return -1;
		int ans = 0;
		sort(value.begin(), value.end());
		for(int i = 0; i != f[0]; ++i) ans += value[i];
		return ans;
	}
}   user;
