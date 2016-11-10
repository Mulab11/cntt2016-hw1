#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

int d[1000010], p[1000010], /*c[1000010], prep[200010],*/ P;

// 彻底想复杂了！
// 保留原有代码作为纪念
// #include <map>
// map<int, int> mem_32[200010];

// int Sqrt(ll n)
// {
// 	int k = sqrtl(n);
// 	while((ll) k * k > n) --k;
// 	while((ll) (k + 1) * (k + 1) <= n) ++k;
// 	return k;
// }

// ll N;
// int S;
// inline int id(const ll& i)
// {
// 	return i <= S ? S + i : (N / i);
// }

// ll F(ll n, int i)
// {
// 	if(i < 0) return 1;
// 	if(n <= 1) return n;
// 	if(p[i + 1] > n) return c[n];
// 	if((ll) p[i] * p[i] > n)
// 	{
// 		// 大于根号的质数只会出现一次
// 		// 而 n / ... 的分段只有 sqrt 段
// 		int v = n / p[i], x = prep[id(n / (v + 1))];
// 		return F(n, x - 1) + (i - x + 1) * F(v, x - 1);
// 	}
// 	if(n > 2000000000)
// 	{
// 		map<int, ll>::iterator k = mem_64[id(n)].find(i);
// 		if(k != mem_64[id(n)].end()) return k->second;
// 		k = mem_64[id(n)].insert(make_pair(i, 0ll)).first;
// 		const int p = ::p[i];
// 		k->second += F(n, i - 1);
// 		for(n /= p; n; n /= p * p) k->second += F(n, i - 1);
// 		return k->second;
// 	}
// 	else
// 	{
// 		map<int, int>::iterator k = mem_32[id(n)].find(i);
// 		if(k != mem_32[id(n)].end()) return k->second;
// 		k = mem_32[id(n)].insert(make_pair(i, 0ll)).first;
// 		const int p = ::p[i];
// 		k->second += F(n, i - 1);
// 		for(n /= p; n; n /= p * p) k->second += F(n, i - 1);
// 		return k->second;
// 	}
// }

ll force(int i, ll N)
{
	// 居然爆搜就过了！！！
	if(i >= P || p[i] > N) return 1;
	// 后面只能取一个咯
	if((ll) p[i] * p[i] >= N)
		return upper_bound(p + i, p + P, N) - p - i + 1;
	const int p = ::p[i];
	ll ret = force(i + 1, N);
	for(N /= p; N; N /= (ll) p * p) ret += force(i + 1, N);
	return ret;
}

class HolyNumbers
{
	void init(int N)
	{
		// c[1] = 1;
		for(int i = 2; i <= N; ++i)
		{
			if(!d[i]) d[i] = p[P++] = i;
			int u = min(N / i, d[i]);
			//printf("%d d = %d\n", i, d[i]);
			for(int j = 0; j != P && p[j] <= u; ++j)
				d[i * p[j]] = p[j];
			// c[i] = 1;
			// for(int x = i; x != 1; )
			// {
			// 	int p = d[x];
			// 	bool k = 0;
			// 	while(d[x] == p) x /= p, k = !k;
			// 	if(!k) {c[i] = 0; break;}
			// }
			// c[i] += c[i - 1];
		}
	}
public:
	// ll count(ll N, int M)
	// {
	// 	::N = N;
	// 	S = Sqrt(N);
	// 	init(M);
	
	// 	for(ll l = 1, r, v; l < N; l = r)
	// 	{
	// 		v = N / l;
	// 		r = N / v + 1;
	// 		prep[id(v)] = upper_bound(p, p + P, v) - p;
	// 	}
	
	// 	return F(N, P - 1);
	// }
	ll count(ll N, int M)
	{
		init(M);
		return force(0, N);
	}
}	user;
