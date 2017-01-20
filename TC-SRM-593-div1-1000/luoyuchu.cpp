#include <bits/stdc++.h>
using namespace std;

#define dig(...) fprintf(stderr, __VA_ARGS__)

template <class TAT>
void Ckmin(TAT &a, const TAT &b)
{
	if (a > b) a = b;
}
template <class TAT>

void Ckmax(TAT &a, const TAT &b)
{
	if (a < b) a = b;
}

typedef long long LL;

using namespace std;

const int maxn = 2e6+115;
const int mod = 1e9+7;

int n;
char S[maxn];
bool ext[maxn];
int f[maxn];

void Init(int wlen, int w0, int wmul, int wadd, int olen, int o0, int omul, int oadd)//随机生成字符串
{
	fill(S + 1, S + 1 + n, '?');				// Concatenation of N '?'
	LL x = w0;
	for(int i=0;i<wlen;i++){
		S[x + 1] = 'w';				// Rewrite the x-th (0-based) character of s
		x = (x * wmul + wadd) % n;
	}

	x = o0;
	for(int i=0;i<olen;i++){
		S[x + 1] = 'o';				// Rewrite the x-th (0-based) character of s
		x = (x * omul + oadd) % n;
	}
}

int Solve()
{
	int nt = 0;
	int wlast = -1, ob, nb, NowSum = 0, p, np;
	static int sta[2][maxn], st[2];
	if (n & 1) return 0;
	memset(f, 0, sizeof(f));//dp:f[i]表示前i*2个字符的的合法字串的案数
	for (int i = 0; i * 2 <= n; ++i) ext[i] = 1;
	st[0] = st[1] = 0; f[0] = 1;
	for (int i = 1; i * 2 <= n; ++i) {
		if (wlast == -1) ob = 0;//最近一个'w'将其可取的区间是一个后缀
		else ob = max(0, wlast - (i - 1));
		if (S[i * 2 - 1] == 'w') wlast = i * 2 - 1;
		if (S[i * 2] == 'w') wlast = i * 2;
		if (S[i * 2 - 1] == 'o') sta[nt][++st[nt]] = i * 2 - 1;//每一个在这个位置之前的'o'将会使得一段区间不可取
		if (wlast == -1) nb = 0;
		else nb = max(0, wlast - i);
		(NowSum += f[i - 1] * ext[i - 1]) %= mod;
		while (ob < nb) {//更新这个后缀和
			NowSum = (NowSum - ext[ob] * f[ob] + mod) % mod;
			++ob;
		}
		while (ob > nb) {
			NowSum = (NowSum + ext[ob - 1] * f[ob - 1]) % mod;
			--ob;
		}
		st[nt ^ 1] = 0;
		for (int j = 1; j <= st[nt]; ++j) {//由于每个f[i]最多被删掉一次，所以暴力删除
			p = sta[nt][j];
			np = max(0, p - i);
			if (ext[np] == 1) {
				if (np >= nb) {
					NowSum = (NowSum - f[np] + mod) % mod;
				}
				ext[np] = 0;
				sta[nt ^ 1][++st[nt ^ 1]] = p;
			}
		}
		f[i] = NowSum;
		nt ^= 1;
		if (S[i * 2] == 'o') sta[nt][++st[nt]] = i * 2;
	}
	return f[n / 2];//返回答案
}

class WolfDelaymasterHard {
public:
    int countWords(int N, int wlen, int w0, int wmul, int wadd, int olen, int o0, int omul, int oadd) {
		n = N;
		Init(wlen, w0, wmul, wadd, olen, o0, omul, oadd);
		return Solve();
    }
};
