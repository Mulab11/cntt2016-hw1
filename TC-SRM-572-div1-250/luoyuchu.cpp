#include <bits/stdc++.h>

#define dig(...) fprintf(stderr, __VA_ARGS__)

using namespace std;

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

class NewArenaPassword {
    public:
    int minChange(string op, int K) {
		int n = op.length();
		int Ans = 0;
		int cnt[257] = {0};
		if (K * 2 <= n) {//如果K*2<=n则答案为对应的两个串不同字符的个数
			for (int i = 0, j = n - K; i < K; ++i, ++j) {
				Ans += (op[i] != op[j]);
			}
		}
		else {//否则可以看作时以n-k为循环节的串，对于每个位置，保留出现次数最多的字符即可
			int xl = n - K;
			int Max;
			for (int i = 0; i < xl; ++i) {
				memset(cnt, 0, sizeof(cnt));
				for (int j = i; j < n; j += xl) {
					++cnt[op[j]];
					++Ans;
				}
				Max = 0;
				for (int j = 'a'; j <= 'z'; ++j) {
					Ckmax(Max, cnt[j]);
				}
				Ans -= Max;
			}
		}
        return Ans;
    }
};
