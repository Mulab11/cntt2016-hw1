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

class TheNumberGameDivOne {
    public:
    string find(long long n) {
		int cnt = (n == ((-n) & n));
		if (cnt == 1) {//如果是2的幂需要特殊判断
			int pos = (int)(log2(n) + 0.5);
			if (pos == 0 || (pos & 1)) {
				return "Brus";
			}
			else {
				return "John";
			}
		}
		else {//否则奇偶性决定胜负
			if (n & 1) return "Brus";
			else return "John";
		}
    }
};

