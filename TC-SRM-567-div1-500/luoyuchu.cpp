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

const int maxn = 55;

class StringGame {
    public:
	int n, m;
	int A[maxn][maxn];
	int cnt[maxn][maxn];
	bool used[maxn];
	bitset<maxn> more[maxn], less[maxn], del;
	bool Check(int p)
	{
		for (int i = 0; i < 26; ++i) {
			more[i].reset();//more[i]为字符'i'在p串中出现的次数比那些串出现的次数严格大
			less[i].reset();//less[i]为字符'i'在p串中出现的次数比那些串出现的次数严格小
			for (int j = 0; j < n; ++j) {//求出more和less
				if (j != p) {
					if (cnt[j][i] > cnt[p][i]) {
						less[i][j] = 1;
					}
					if (cnt[j][i] < cnt[p][i]) {
						more[i][j] = 1;
					}
				}
			}
		}
		//贪心从前往后放置p串字符，可以证明相同字符肯定放在一起
		memset(used, 0, sizeof(used));//used[i]表示字符'i'是否已经用过
		del.reset();//del表示在此时，p串已经比哪些串字典序严格小了(del[j]=0表示已经比j串严格小)
		for (int i = 0; i < n; ++i) {
			if (i != p) {
				del[i] = 1;
			}
		}
		for (int ti = 0; ti < 26; ++ti) {
			for (int i = 0; i < 26; ++i) {
				if (used[i] == 0) {
					if ((less[i] & del).any() == 0) {//如果放这一种字符不会使得p串字典序严格大于别人，则贪心放这一种字符
						used[i] = 1;
						del = del & (more[i].flip());//更性比哪些串字典序严格小
					}
				}
			}
		}
		if (del.any()) return 0;//如果不能比所有串都小则失败
		else return 1;
	}
    vector<int> getWinningStrings(vector<string> S) {
		vector<int> Ans;
		n = S.size();
		m = S[0].length();
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				A[i][j] = S[i][j] - 'a';
				++cnt[i][A[i][j]];//统计每一个串的不同字符的个数
			}
		}
		for (int i = 0; i < n; ++i) {
			if (Check(i)) {//检查如果先手选择i这个串，能否有必胜策略
				Ans.push_back(i);
			}
		}
        return Ans;
    }
};

