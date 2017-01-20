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

const int maxn = 13;
const int maxm = 145;
const int maxs = 5e3+115;

int n;
int f[maxs][maxm];

class KeyDungeonDiv1 {
    public:
    int maxKeys(vector<int> doorR, vector<int> doorG, vector<int> roomR, vector<int> roomG, vector<int> roomW, vector<int> keys) {
		n = doorR.size();
		int N = (1 << n);
		int tmp, nd[2], Ans = 0;
		vector<int> s, now;
		memset(f, -0x3f, sizeof(f));
		f[0][keys[0]] = keys[2];
		for (int i = 0; i < N; ++i) {//Dp:f[i][j]表示已经开过的门的集合为i，现在手上的红色钥匙数量为j的手上的最大的白色钥匙数量是多少
			tmp = i;
			s = keys;
			nd[0] = nd[1] = 0;
			for (int j = 0; j < n; ++j) {
				if (tmp & 1) {
					s[0] += roomR[j];
					s[1] += roomG[j];
					s[2] += roomW[j];
					nd[0] += doorR[j];
					nd[1] += doorG[j];
				}
				tmp >>= 1;
			}
			for (int j = 0; j <= s[0]; ++j) {
				if (f[i][j] < 0) continue;
				now = s;
				now[2] -= max(nd[0] - (now[0] - j), 0);
				now[0] = j;
				now[1] -= nd[1];
				now[1] += (now[2] - f[i][j]);
				now[2] = f[i][j];//由于需要与得到的钥匙固定，所以可以计算出有多少绿色钥匙
				Ckmax(Ans, now[0] + now[1] + now[2]);
				for (int k = 0; k < n; ++k) {
					if ((i >> k) & 1) continue;
					if (max(0, doorR[k] - now[0]) + max(0, doorG[k] - now[1]) <= now[2]) {//枚举下一个开的门，贪心优先使用有颜色的钥匙开门转移
						Ckmax(f[i | (1 << k)][max(0, now[0] - doorR[k]) + roomR[k]], now[2] - max(0, doorR[k] - now[0]) - max(0, doorG[k] - now[1]) + roomW[k]);
					}
				}
			}
		}
        return Ans;
    }
};
