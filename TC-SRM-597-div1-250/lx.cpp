#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define bin(x) (1<<(x))
#define LX_JUDGE

using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

template<typename T> inline void upmax(T &x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T &x, T y) { x > y ? x = y : 0; }

class LittleElephantAndString {
private :
	int cnt[26], n;
public :
	//贪心
	int getNumber(string A, string B) {
		n = A.size();
		//首先 A、B 中每个字符出现次数应该相同
		rep (i, 0, n-1)  ++cnt[A[i] - 'A'];
		rep (i, 0, n-1)  --cnt[B[i] - 'A'];
		rep (i, 0, 25) if (cnt[i])  return -1;
		//每个字符最多操作一次，问题转化为最大化不用操作的字符个数
		//找到最长的 B 的后缀，使得它是 A 的子序列，这个过程可以用一个指针贪心
		int cur = n-1;
		down (i, n-1, 0) {
			while (cur >= 0 && A[cur] != B[i]) {
				--cur;
			}
			if (cur >= 0) {
				--cur;
			} else {
				return i + 1;
			}
		}
		return 0;
	}
};

