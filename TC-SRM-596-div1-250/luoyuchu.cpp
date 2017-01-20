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

class IncrementAndDoubling {
    public:
    int getMin(vector<int> desiredArray) {
		int ans = 0;
		int tmp, Max = 0;
		for (int i = 0; i < (int)desiredArray.size(); ++i) {//对于每一位置来说，就是一个二进制x2与+1的过程
			tmp = desiredArray[i];
			ans += __builtin_popcount(tmp);
			for (int j = 0; tmp; ++j) {
				Ckmax(Max, j);
				tmp >>= 1;
			}
		}
        return ans + Max;
    }
};
