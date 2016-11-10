#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

pair<double, int> p[60], q[60];
#include <set>

class PointyWizardHats
{
public:
	int getNumHats(vector<int> a, vector<int> b, vector<int> c, vector<int> d)
	{
		// 二维偏序的贪心
		int n = a.size(), m = c.size();
		for(int i = 0; i != n; ++i) p[i] = make_pair((double) a[i] / b[i], b[i]); sort(p, p + n);
		for(int j = 0; j != m; ++j) q[j] = make_pair((double) c[j] / d[j], d[j]); sort(q, q + m);
		// 用平衡树维护第一个比某个数大的数
		multiset<int> T;
		multiset<int>::iterator k;
		int j = 0, ans = 0;
		for(int i = 0; i != n; ++i)
		{
			for(; j != m && q[j].first < p[i].first; ++j)
				T.insert(q[j].second);
			k = T.upper_bound(p[i].second);
			if(k != T.end()) ++ans, T.erase(k);
		}
		return ans;
	}
}	user;
