#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define x first
#define y second
#define LX_JUDGE

using namespace std;
typedef long long LL;

template<typename T> inline void upmax(T & x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T & x, T y) { x > y ? x = y : 0; }

template<typename T>
inline void read(T & x)
{
	char c;
	while ((c = getchar()) < '0' || c > '9');
	for (x = c - '0'; (c = getchar()) >= '0' && c <= '9'; x = x * 10 + c - '0');
}

const int inf = 0x3f3f3f3f;
const int N = 1e5 + 10;

class TheJediTest
{
public:
	int minimumSupervisors(vector<int> students, int K)
	{
		int ans = 0;
		int n = students.size();
		for (int i = 0; i < n; ++i)
		{
			ans += (students[i] + K - 1) / K;
			int tmp = (K - students[i] % K) % K;
			if (i + 1 < n)
			{
				int t = min(tmp, students[i + 1]);
				students[i + 1] -= t;
				tmp -= t;
			}
			if (i + 2 < n)
				students[i + 2] -= min(tmp, students[i + 2]);
		}
		return ans;
	}
};

int main()
{
#ifdef LX_JUDGE
	freopen("in.txt", "r", stdin);
#endif
	return 0;
}
