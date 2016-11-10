#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
typedef long long ll;
typedef long double ld;

const int mod = 1e9 + 9;

// RHO 分解因数
namespace Math
{
#define RG register
#define IL inline
#define For(i, a, b) for(RG int i = a, ___u = b; i <= ___u; ++i)
#define Dor(i, a, b) for(RG int i = b, ___d = a; i >= ___d; --i)
#define Rep(i, a, b) for(RG int i = a, ___u = b; i != ___u; ++i)
	IL ll mul_mod(RG const ll& a, RG const ll& b, RG const ll &mod)
	{
		RG ll ret = (a * b - (ll) ((long double) a * b / mod) * mod) % mod;
		return ret < 0 ? ret + mod : ret;
	}
	IL ll power(RG ll a, RG ll b, RG ll mod)
	{
		RG ll c = 1;
		for(; b; b >>= 1)
		{
			if(b & 1) c = mul_mod(c, a, mod);
			if(b > 1) a = mul_mod(a, a, mod);
		}
		return c;
	}
	IL bool pig(RG ll n)
	{
		if(n == 2 || n == 3 || n == 5) return 1;
		if(n <= 6 || (n & 1) == 0) return 0;
		RG int s = __builtin_ctzll(n - 1);
		RG ll d = (n - 1) >> s;
		RG unsigned int A = 1 << 16 | 3, B = 33333331;
		RG unsigned long long C = 2341234123412341llu;
		RG ll a;
		for(RG int T = 4, i; T--; )
		{
			C = C * A + B;
			a = power(C % (n - 2) + 2, d, n);
			if(a == 1) continue;
			for(i = 0; i != s && a + 1 != n; ++i)
				a = mul_mod(a, a, n);
			if(i == s) return 0;
		}
		return 1;
	}
	
	ll p[10000];
	int c[10000];
	int tot;
	
	IL ll gcd(RG ll a, RG ll b)
	{
		for(RG ll t; b; )
			t = a, a = b, b = t % b;
		return a;
	}
	void factor(RG ll n)
	{
		if(n == 1) return;
		if(~n & 1) return (p[tot++] = 2, factor(n >> 1));
		if(pig(n)) return (void) (p[tot++] = n);
		
		RG int c;
		RG ll x, y, p;
		do
		{
			c = rand() % (n - 1) + 1;
			x = y = rand() % n;
			do
			{
				x = (mul_mod(x, x, n) + c) % n,
				y = (mul_mod(y, y, n) + c) % n,
				y = (mul_mod(y, y, n) + c) % n,
				p = gcd(n, x > y ? x - y : y - x);
			}
			while(p == 1);
		}
		while(p == n);
		while(n % p == 0) n /= p;
		return factor(p), factor(n);
	}
	ll fact[1000000];
	int Fact;
	void dfs(RG int i, RG const ll x)
	{
		fact[Fact++] = x;
		RG ll p, y;
		for(RG int c; i--; )
			for(p = Math::p[i], c = Math::c[i], y = x; c--; )
				dfs(i, y *= p);
		
	}
	
	IL void factor_list(RG ll n)
	{
		tot = 0;
		factor(n);
		sort(p, p + tot);
		tot = unique(p, p + tot) - p;
		Rep(i, 0, tot)
		{
			c[i] = 0;
			while(n % p[i] == 0) n /= p[i], ++c[i];
		}
		Fact = 0;
		dfs(tot, 1);
	}
}

ll pos[110];
char val[110];

int special[10000000];
const int inv25 = 440000004;
IL int power(RG int a, RG int b)
{
	RG int c = 1;
	for(; b; b >>= 1)
	{
		if(b & 1) c = (ll) c * a % mod;
		if(b > 1) a = (ll) a * a % mod;
	}
	return c;
}

#include <map>

class CharacterBoard
{
public:
	int countGenerators(vector<string> frac, int W, int movx, int movy)
	{
		srand(2341);
		const int N = frac.size(), M = frac[0].size();
		int tot = 0;
		for(int i = 0; i != N; ++i)
			for(int j = 0; j != M; ++j)
			{
				pos[tot] = (ll) (movx + i) * W + movy + j;
				val[tot] = frac[i][j];
				++tot;
			}
		// 本来可以枚举长度，现在不行了，只能强行判断是否合法
		// 暴力枚举所有不等的位置，如果 val[i] != val[j]，则存在方程 pos[i] != pos[j] (mod x)
		// -> x !| diff(pos[i], pos[j])
		// 所有的有冲突 w 和不同位置有重复出现的 w，必然是某一个 pos[i] - pos[j] 的约数
		// 暴力枚举一下
		int S = 0;
		for(int i = 0; i != tot; ++i)
			for(int j = i + 1; j != tot; ++j)
			{
				using Math::fact;
				using Math::Fact;
				Math::factor_list(pos[j] - pos[i]);
				for(int k = 0; k != Fact; ++k)
					if(fact[k] <= W)
						special[S++] = fact[k];
			}
		// 如果没有特殊点，答案可以直接计算
		int ans = (tot <= W) ? (ll) (power(26, W - tot + 1) - 1) * inv25 % mod : 0;
		sort(special, special + S);
		S = unique(special, special + S) - special;
		map<int, char>::iterator iter;
		for(int i = 0; i != S; ++i)
		{
			int x = special[i];
			if(x >= tot) (ans -= power(26, x - tot)) %= mod;
			map<int, char> limit;
			for(int k = 0; k != tot; ++k)
			{
				iter = limit.find(int(pos[k] % x));
				if(iter != limit.end())
				{
					if(iter->second != val[k]) goto skipped;
				}
				else limit.insert(make_pair(int(pos[k] % x), val[k]));
			}
			(ans += power(26, x - limit.size())) %= mod;
		skipped: continue;
		}
		return (ans + mod) % mod;
	}
}	user;
