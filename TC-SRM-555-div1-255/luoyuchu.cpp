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

int n;
int A[maxn];
int f[maxn];//f[i]表示[1,i]最少可以分成多少段

bool Check(int l, int r)//检查[l,r]这一段是否是5的幂
{
	LL S = 0;
	if (A[l] == 0) return 0;
	for (int i = l; i <= r; ++i) {
		S <<= 1;
		S |= A[i];
	}
	while (S % 5 == 0) S /= 5;
	return (S == 1);
}

void Solve()//Dp
{
	memset(f, 0x3f, sizeof(f));
	f[0] = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < i; ++j) {
			if (f[j] < 1e9 && Check(j + 1, i)) {
				Ckmin(f[i], f[j] + 1);
			}
		}
	}
}

class CuttingBitString {
    public:
    int getmin(string S) {
		n = S.length();
		for (int i = 0; i < n; ++i) A[i + 1] = S[i] - '0';
		Solve();//Dp
		if (f[n] > 1e9) f[n] = -1;//无解
		return f[n];//返回答案
    }
};
