#line 2 "SparseFactorial.cpp"
#include<vector>
#include<list>
#include<map>
#include<set>
#include<deque>
#include<stack>
#include<bitset>
#include<algorithm>
#include<functional>
#include<numeric>
#include<utility>
#include<sstream>
#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<cstring>
#define clear(x) memset(x, 0, sizeof(x));
#define pii pair<int, int>
#define fr first
#define sc second
#define mp make_pair
#define pb push_back
#define son e[i].t
#define oo 0x3f3f3f3f
#define maxm 1000010
#define maxn 10
typedef long long ll;
using namespace std;
ll a[maxm], b[maxm];
int tmp[maxm];
void solve(ll P, ll p, ll r)
{
	memset(tmp, 0, sizeof(tmp));
	memset(a, 0x3f, sizeof(a));
	for (ll i = 0; i <= (r + 1) * p; ++ i)
		for (ll x = i * i % p; x < P; x += p){
			if (tmp[x] >= r) continue;
			ll t = P + x - i * i % P;
			while (t % p == 0){ ++ tmp[x]; t /= p;}
			if (tmp[x] >= r) a[x] = i * i + 1;
		}
}
ll calc(ll P, ll n, ll lim)
{
	return n / P + (n % P >= lim);
}
class SparseFactorial
{
	public:
		long long getCount(long long L, long long R, long long P)
		{
			ll tmp = P, ans = 0, p, pr, r;
			for (int i = 0; i < P; ++ i) b[i] = L;
			for (ll i = 2; i <= tmp; ++ i){
				if (tmp == 1) break;
				if (tmp % i == 0){
					p = i, pr = 1ll, r = 0;
					while (tmp % i == 0) ++ r, tmp /= i, pr *= i;
					solve(pr, p, r);
					for (int j = 0; j < P; ++ j) b[j] = max(b[j], a[j % pr]);
				}
			}
			for (int i = 0; i < P; ++ i){
				if (i > R || b[i] > R) continue;
				ans += calc(P, R, i) - calc(P, b[i] - 1, i);
			}
			return ans;
		}
};
