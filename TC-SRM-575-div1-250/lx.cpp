#include <bits/stdc++.h>

using namespace std;
typedef long long LL;

class TheNumberGameDivOne
{
public :
	string find(LL n) {
		int x = 0;
		while (n % 2 == 0) { 
			n /= 2;
			++x;
		}
		bool ans = (x > 0) && (n > 1 || x % 2 == 0);
		return ans ? "John" : "Brus";
	}
};

int main()
{
#ifdef LX_JUDGE
	freopen("in.txt", "r", stdin);
#endif
	return 0;
}
