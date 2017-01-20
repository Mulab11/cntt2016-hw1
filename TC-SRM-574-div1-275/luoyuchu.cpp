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

class TheNumberGame {
    public:
    string determineOutcome(int A, int B) {
		string a1, a2, b;
		while (B) {//将数字B转为字符串
			b += (char)(B % 10 + '0');
			B /= 10;
		}
		while (A) {//将数字A转为字符串
			a1 += (char)(A % 10 + '0');
			A /= 10;
		}
		a2 = a1;
		reverse(a2.begin(), a2.end());
		if (a1.find(b) != string::npos || a2.find(b) != string::npos) return "Manao wins";//如果B是A或A的反串的字串，则Manao获得胜利
        else return "Manao loses";
    }
};

