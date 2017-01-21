#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

class UnknownTree {
public:
	int getCount(vector<int> , vector<int> , vector<int> );
};
long long pmod = 1000000009;
int cc[100];
bool cmp(int a, int b) {
	return cc[a] < cc[b];
}
long long f(vector<int> p, int i) {
	if (p.size() == i)
		return 1;
	sort(p.begin(), p.end(), cmp);
	int v;
	long long ret, now, up;
	ret = 1;
	now = 1;
	up = 1;
	v = cc[p[i]];
	for (; i < p.size(); ++i) {
		if (v != cc[p[i]]) {
			v = cc[p[i]];
			now = up;
		}
		ret *= now;
		ret %= pmod;
		up++;
	}
	return ret;
}
long long gao1(vector<int> a, vector<int> b, vector<int> c) {
	int i;
	int ca, cb, cc;
	int n = a.size();
	vector<int> va, vb, vc;
	int x = abs(a[0] - b[0]);
	int y = abs(c[0] - b[0]);
	ca = cb = cc = 0;
	for (i = 0; i < n; ++i) {
		if (abs(a[i] - b[i]) != x)
			return 0;
		if (abs(c[i] - b[i]) != y)
			return 0;
		if (a[i] < b[i] && b[i] < c[i])
			va.push_back(i);
		else if (a[i] > b[i] && b[i] > c[i])
			vc.push_back(i);
		else if (a[i] > b[i] && c[i] > b[i])
			vb.push_back(i);
		else
			return 0;
	}
	return f(va, 0) * f(vb, 0) % pmod * f(vc, 0) % pmod;
}
long long gao2(vector<int> a, vector<int> b, vector<int> c) {
	int i, j;
	int n = a.size();
	int lab = abs(a[0] - b[0]);
	if (lab == 0)
		return 0;
	for (i = 0; i < n; ++i) {
		if (abs(a[i] - b[i]) != lab)
			return 0;
	}
	int lbc = b[0] + c[0];
	for (i = 0; i < n; ++i) {
		if (lbc > b[i] + c[i])
			lbc = b[i] + c[i];
	}
	int ed = 1;
	map<int, int> m;
	vector<int> v[55];
	vector<int> va;
	for (i = 0; i < n; ++i) {
		if (a[i] < b[i]) {
			if (c[i] - b[i] != lbc)
				return 0;
			va.push_back(i);
		} else {
			if (abs(c[i] - b[i]) > lbc)
				return 0;
			int p = m[c[i] - b[i]];
			if (p == 0) {
				p = ed++;
				m[c[i] - b[i]] = p;
			}
			v[p].push_back(i);
		}
	}
	long long ret = f(va, 0);
	for (i = 1; i < ed; ++i) {
		int rr = 0;
		for (j = 0; j < v[i].size(); ++j) {
			if (b[v[i][j]] + c[v[i][j]] == lbc)
				rr++;
		}
		if (abs(c[v[i][0]] - b[v[i][0]]) != lbc && rr != 1)
			return 0;
		if (abs(c[v[i][0]] - b[v[i][0]]) != lbc)
			ret *= f(v[i], 1);
		else
			ret *= f(v[i], 0);
		ret %= pmod;
	}
	return ret;
}
long long gao3(vector<int> a, vector<int> b, vector<int> c) {
	int i, j;
	int n = a.size();
	int lab = a[0] + b[0];
	for (i = 0; i < n; ++i) {
		if (lab > a[i] + b[i])
			lab = a[i] + b[i];
	}
	int lac = a[0] + c[0];
	for (i = 0; i < n; ++i) {
		if (lac > a[i] + c[i])
			lac = a[i] + c[i];
	}
	int lbc = b[0] + c[0];
	for (i = 0; i < n; ++i) {
		if (lbc > b[i] + c[i])
			lbc = b[i] + c[i];
	}
	int mid = -1;
	for (i = 0; i < n; ++i) {
		if (a[i] + b[i] == lab && a[i] + c[i] == lac && b[i] + c[i] == lbc) {
			if (mid != -1) {
				return 0;
			}
			mid = i;
		}
	}
	if (mid == -1)
		return 0;

	int an = 1, bn = 1, cn = 1;
	map<int, int> am, bm, cm;
	vector<int> av[55], bv[55], cv[55], vo;
	for (i = 0; i < n; ++i) {
		if (i == mid)
			continue;
		if (b[i] - a[i] == b[mid] - a[mid] && c[i] - a[i] == c[mid] - a[mid]) {
			vo.push_back(i);
		} else if (b[i] - a[i] > b[mid] - a[mid] && c[i] - a[i] > c[mid]
				- a[mid]) {
			int pos = b[i] - a[i] - b[mid];
			if (pos != c[i] - a[i] - c[mid])
				return 0;
			int p = am[pos];
			if (p == 0) {
				p = an++;
				am[pos] = p;
			}
			av[p].push_back(i);
		} else if (a[i] - b[i] > a[mid] - b[mid] && c[i] - b[i] > c[mid]
				- b[mid]) {
			int pos = a[i] - b[i] - a[mid];
			if (pos != c[i] - b[i] - c[mid])
				return 0;
			int p = bm[pos];
			if (p == 0) {
				p = bn++;
				bm[pos] = p;
			}
			bv[p].push_back(i);
		} else if (b[i] - c[i] > b[mid] - c[mid] && a[i] - c[i] > a[mid]
				- c[mid]) {
			int pos = b[i] - c[i] - b[mid];
			if (pos != a[i] - c[i] - a[mid])
				return 0;
			int p = cm[pos];
			if (p == 0) {
				p = cn++;
				cm[pos] = p;
			}
			cv[p].push_back(i);
		} else {
			return 0;
		}
	}
	long long ret = f(vo, 0);
	for (i = 1; i < an; ++i) {
		int rr = 0;
		for (j = 0; j < av[i].size(); ++j) {
			if (a[av[i][j]] + b[av[i][j]] == lab)
				rr++;
		}
		if (abs(a[av[i][0]] - b[av[i][0]]) != lab && rr != 1)
			return 0;
		if (abs(a[av[i][0]] - b[av[i][0]]) != lab)
			ret *= f(av[i], 1);
		else
			ret *= f(av[i], 0);
		ret %= pmod;
	}
	for (i = 1; i < bn; ++i) {
		int rr = 0;
		for (j = 0; j < bv[i].size(); ++j) {
			if (a[bv[i][j]] + b[bv[i][j]] == lab)
				rr++;
		}
		if (abs(a[bv[i][0]] - b[bv[i][0]]) != lab && rr != 1)
			return 0;
		if (abs(a[bv[i][0]] - b[bv[i][0]]) != lab)
			ret *= f(bv[i], 1);
		else
			ret *= f(bv[i], 0);
		ret %= pmod;
	}
	for (i = 1; i < cn; ++i) {
		int rr = 0;
		for (j = 0; j < cv[i].size(); ++j) {
			if (c[cv[i][j]] + b[cv[i][j]] == lbc)
				rr++;
		}
		if (abs(c[cv[i][0]] - b[cv[i][0]]) != lbc && rr != 1)
			return 0;
		if (abs(c[cv[i][0]] - b[cv[i][0]]) != lbc)
			ret *= f(cv[i], 1);
		else
			ret *= f(cv[i], 0);
		ret %= pmod;
	}
	return ret;
}
long long gao4(vector<int> a, vector<int> b, vector<int> c) {
	int i, j;
	int n = a.size();
	int lab = a[0] + b[0];
	for (i = 0; i < n; ++i) {
		if (lab > a[i] + b[i])
			lab = a[i] + b[i];
	}
	int lac = a[0] + c[0];
	for (i = 0; i < n; ++i) {
		if (lac > a[i] + c[i])
			lac = a[i] + c[i];
	}
	int lbc = b[0] + c[0];
	for (i = 0; i < n; ++i) {
		if (lbc > b[i] + c[i])
			lbc = b[i] + c[i];
	}
	if (lab + lbc != lac)
		return 0;
	int an = 1, cn = 1;
	map<int, int> am, cm;
	vector<int> av[55], bv, cv[55];
	for (i = 0; i < n; ++i) {
		if (c[i] - b[i] == lbc && a[i] - b[i] == lab)
			bv.push_back(i);
		else if (c[i] - b[i] == lbc) {
			if (abs(a[i] - b[i]) > lab)
				return 0;
			int pos = a[i] - b[i];
			int p = am[pos];
			if (p == 0) {
				p = an++;
				am[pos] = p;
			}
			av[p].push_back(i);
		} else if (a[i] - b[i] == lab) {
			if (abs(c[i] - b[i]) > lbc)
				return 0;
			int pos = c[i] - b[i];
			int p = cm[pos];
			if (p == 0) {
				p = cn++;
				cm[pos] = p;
			}
			cv[p].push_back(i);
		}
	}
	long long ret = f(bv, 0);
	for (i = 1; i < an; ++i) {
		int rr = 0;
		for (j = 0; j < av[i].size(); ++j) {
			if (a[av[i][j]] + b[av[i][j]] == lab)
				rr++;
		}
		if (abs(a[av[i][0]] - b[av[i][0]]) != lab && rr != 1)
			return 0;
		if (abs(a[av[i][0]] - b[av[i][0]]) != lab)
			ret *= f(av[i], 1);
		else
			ret *= f(av[i], 0);
		ret %= pmod;
	}
	for (i = 1; i < cn; ++i) {
		int rr = 0;
		for (j = 0; j < cv[i].size(); ++j) {
			if (c[cv[i][j]] + b[cv[i][j]] == lbc)
				rr++;
		}
		if (abs(c[cv[i][0]] - b[cv[i][0]]) != lbc && rr != 1)
			return 0;
		if (abs(c[cv[i][0]] - b[cv[i][0]]) != lbc)
			ret *= f(cv[i], 1);
		else
			ret *= f(cv[i], 0);
		ret %= pmod;
	}
	return ret;
}
int UnknownTree::getCount(vector<int> a, vector<int> b, vector<int> c) {
	long long ans = 0;
	int i;
	for (i = 0; i < a.size(); ++i)
		cc[i] = a[i];
	ans += gao1(a, b, c);
	ans += gao1(a, c, b);
	ans += gao1(b, a, c);
	ans += gao2(a, b, c);
	ans += gao2(b, a, c);
	ans += gao2(a, c, b);
	ans += gao2(c, a, b);
	ans += gao2(b, c, a);
	ans += gao2(c, b, a);
	ans += gao3(b, c, a);
	ans += gao4(a, b, c);
	ans += gao4(a, c, b);
	ans += gao4(b, a, c);
	return ans % pmod;
}
