/*
	Implementation.
	Let's fix a 'core' of the final spread, and greedily swap the chocolate with the same color nearby to the core.
*/

#include <bits/stdc++.h>
using namespace std;

class ColorfulChocolates {
	public:
	int maximumSpread(string chocolates, int maxSwaps) {
		int len = chocolates.length();
		int ret = 0;
		for (int i = 0; i < len; ++i){
			int l = i, r = i, swp = maxSwaps;
			int li = i - 1, ri = i + 1, ld = 23333, rd = 23333;
			while (1){
				while (li >= 0 && chocolates[li] != chocolates[i]) --li;
				ld = li >= 0 ? l - li - 1 : 23333;
				while (ri < len && chocolates[ri] != chocolates[i]) ++ri;
				rd = ri < len ? ri - r - 1 : 23333;
				if (min(ld, rd) > swp) break;
				if (ld < rd)
					swp -= ld, --li, --l;
				else
					swp -= rd, ++ri, ++r;
			}
			if (ret < r - l + 1) ret = r - l + 1;
		}
		return ret;
	}
};

/*
	'You are my gravity, gravity, gravity,
	Kimi to yukeru mirai
	Ima, hirogatteku'
		- Gravity
*/
