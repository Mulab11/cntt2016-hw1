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

class KnightCircuit2 {
    public:
    int maxSize(int w, int h) {
		if (w > h) swap(w, h);//我们令h总是小的那一维的长度
		if (w == 1) return 1;//如果w=1，则无法移动
		else if (w == 2) {//如果w=2，则只能上下地跳
			return (h - 1) / 2 + 1;
		}
		else if (w == 3 && h == 3) return 8;//当w=3,h=3时，中间的格子无法移动，其余8个可以互达
		else return w * h;//否则所有格子都可以到达
    }
};


