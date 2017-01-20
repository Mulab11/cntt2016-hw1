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

class FoxAndMountainEasy {
    public:
    string possible(int n, int h0, int hn, string history) {
		int det = 0, L, Min = 0;//det为这一段的实际变化量，Min为这一段变化的过程中变化量的最小值，L为这一段变化的长度
		L = history.length();
		for (int i = 0; i < L; ++i) {
			det += (history[i] == 'U') ? 1 : -1;
			Ckmin(Min, det);
		}
		Min += h0;//如果变化时出现负数，需要在之前补上一些+1s
		Ckmin(Min, 0);
		L -= Min;
		det -= Min;
		if (abs(hn - h0 - det) <= n - L && (n - L - abs(hn - h0 - det)) % 2 == 0) return "YES";//判断剩余的操作数是否能完成目标
        else return "NO";
    }
};
