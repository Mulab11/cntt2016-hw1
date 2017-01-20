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

int n;

class FoxAndChess {
    public:
    string ableToMove(string begin, string target) {
		n = begin.size();
		int p1 = 0, p2 = 0;
		while (1) {//begin与target的每个字符的相对位置一定不会变，所以只要保证对应的字符可以移动到相应位置即可
			while (p1 < n && begin[p1] == '.') ++p1;
			while (p2 < n && target[p2] == '.') ++p2;
			if ((p1 < n) != (p2 < n)) return "Impossible";
            if (p1 >= n && p2 >= n) break;
			if (begin[p1] != target[p2]) return "Impossible";
			if (begin[p1] == 'L' && p1 < p2) return "Impossible";
			if (begin[p1] == 'R' && p1 > p2) return "Impossible";
			++p1, ++p2;
		}
        return "Possible";
    }
};
