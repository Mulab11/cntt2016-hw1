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

#define mp make_pair
#define pb push_back

const int maxn = 55;
const int mod = 1e9+9;

int n;
struct Data
{
	int a, b, c;
}d[maxn];//每个点
map<pair<int, int>, bool> Hash;//判断在一条链的情况时的重复情况

int Stat(vector<pair<int, int> > &A)//统计一条链上的方案数
{
	int sz, s = 1, last;
	A.pb(mp(-1, -1));
	sort(A.begin(), A.end());
	sz = A.size();
	for (int i = 1, j = 0; i < sz; ++i) {
		if (A[i - 1].first != A[i].first && A[i].second > 0) return 0;//对于每一个位置有且仅有一个伸出长度为0的
		if (A[i - 1].first == A[i].first && A[i].second == 0) return 0;
		if (A[i].first != A[i - 1].first) last = i, j = i;
		while (j < i - 1 && A[j + 1].second < A[i].second) ++j;
		if (A[i].second) {
			s = 1LL * s * (j - last + 1) % mod;//可以选择任何一个伸出长度
		}
	}
	return s;
}

int Work(int ab, int bc)//枚举链的两段长度O---ab----O----bc----O
{
	static vector<pair<int, int> > l;
	if (Hash.count(mp(ab, bc))) return 0;
	Hash[mp(ab, bc)] = 1;
	l.clear();
	l.pb(mp(0, 0));
	l.pb(mp(ab, 0));
	l.pb(mp(ab + bc, 0));
	for (int i = 1; i <= n; ++i) {
		if ((d[i].a + d[i].c - ab - bc) >= 0 && ((d[i].a + d[i].c - ab - bc) & 1) == 0) {
			l.pb(mp(d[i].a - (d[i].a + d[i].c - ab - bc) / 2, (d[i].a + d[i].c - ab - bc) / 2));
			if (d[i].b != l.back().second + abs(l.back().first - ab)) {
				return 0;
			}
		}
		else return 0;
	}
	return Stat(l);
}

int Chain()//考虑三个点形成一条链的情况
{
	int sum = 0;
	Hash.clear();
	for (int i = 1; i <= n; ++i) {
		if (d[i].a < d[i].b && d[i].b < d[i].c) (sum += Work(d[i].b - d[i].a, d[i].c - d[i].b)) %= mod;
		if (d[i].b < d[i].c) (sum += Work(d[i].a + d[i].b, d[i].c - d[i].b)) %= mod;
		if (d[i].b < d[i].a && d[i].b < d[i].c) (sum += Work(d[i].a - d[i].b, d[i].c - d[i].b)) %= mod;
		if (d[i].b < d[i].a) (sum += Work(d[i].a - d[i].b, d[i].c + d[i].b)) %= mod;
		if (d[i].c < d[i].b && d[i].b < d[i].a) (sum += Work(d[i].a - d[i].b, d[i].b - d[i].c)) %= mod;
	}
	return sum;
}

int Centre(int a, int b, int c)//考虑对于三个点通过中间一个点链接的情况
{
	static vector<pair<int, int>> A, B, C, D;
	int s = 1, mo;
	A.clear(); B.clear(); C.clear(); D.clear();
	A.pb(mp(0, 0)); B.pb(mp(0, 0));	C.pb(mp(0, 0));
	for (int i = 1; i <= n; ++i) {
		mo = (d[i].a + d[i].b - (a + b));
		if ((mo & 1) || mo < 0) return 0;
		else mo /= 2;
		if (d[i].a - mo < a) {//在A链上
			A.pb(mp(d[i].a - mo, mo));
			if (d[i].c != c + mo + abs(d[i].a - mo - a)) return 0;
		}
		else if (d[i].b - mo < b) {//在B链上
			B.pb(mp(d[i].b - mo, mo));
			if (d[i].c != c + mo + abs(d[i].b - mo - b)) return 0;
		}
		else if (c + mo == d[i].c) {//在中间点上
			D.pb(mp(0, mo));
		}
		else {//在C链上
			if (d[i].c + mo - c < 0 || (d[i].c + mo - c) % 2 != 0) {
				return 0;
			}
			C.pb(mp(d[i].c - (d[i].c + mo - c) / 2, (d[i].c + mo - c) / 2));
		}
	}
	s = 1LL * s * Stat(A) % mod;
	s = 1LL * s * Stat(B) % mod;
	s = 1LL * s * Stat(C) % mod;
	s = 1LL * s * Stat(D) % mod;
	return s;
}

class UnknownTree {
    public:
    int getCount(vector<int> dA, vector<int> dB, vector<int> dC) {
		int Ans = 0;
		n = dA.size();
		for (int i = 1; i <= n; ++i) {
			d[i].a = dA[i - 1];
			d[i].b = dB[i - 1];
			d[i].c = dC[i - 1];
		}
		(Ans += Chain()) %= mod;//枚举A,B,C三个点在中间，三种情况
		for (int i = 1; i <= n; ++i) swap(d[i].a, d[i].b);
		(Ans += Chain()) % mod;
		for (int i = 1; i <= n; ++i) swap(d[i].c, d[i].b);
		(Ans += Chain()) %= mod;
		for (int i = 1; i <= n; ++i) (Ans += Centre(d[i].a, d[i].b, d[i].c)) %= mod;//枚举哪一个点在中间链接三个点
        return Ans;
    }
};
