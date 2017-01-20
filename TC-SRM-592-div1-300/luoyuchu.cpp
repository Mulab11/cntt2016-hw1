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

int mp[267];

class LittleElephantAndBalls {
    public:
    int getNumber(string S) {
		int cnt[3] = {0}, Ans = 0;
		memset(mp, 0, sizeof(mp));
		mp['R'] = 0; mp['B'] = 1; mp['G'] = 2;
		for (int i = 0; i < (int)S.size(); ++i) {//当一种颜色数量大于等于2时，一定可以将其放在两边，使得贡献为2，而数量为1时，贡献为1，否则为0
			for (int j = 0; j < 3; ++j) {
				Ans += min(2, cnt[j]);
			}
			++cnt[mp[S[i]]];
		}
        return Ans;
    }
};
