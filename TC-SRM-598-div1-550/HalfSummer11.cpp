#line 2 "FoxAndFencing.cpp"
#include<vector>
#include<list>
#include<map>
#include<set>
#include<deque>
#include<stack>
#include<bitset>
#include<algorithm>
#include<functional>
#include<numeric>
#include<utility>
#include<sstream>
#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<cstring>
#define cl(x) memset(x, 0, sizeof(x));
#define pii pair<int, int>
#define fr first
#define sc second
#define mp make_pair
#define pb push_back
#define oo 0x3f3f3f3f
#define maxn 
typedef long long ll;
using namespace std;
class FoxAndFencing {
	public:
		string WhoCanWin(int mov1, int mov2, int rng1, int rng2, int d) {
			if (d <= mov1 + rng1) return "Ciel"; // Ciel第一步就能赢
			if (d + mov1 <= mov2 + rng2) return  "Liss"; // Liss第一步就能赢
			if (mov1 == mov2) return "Draw"; // 否则，主动权掌握在跑得快的人手里。如果跑得一样快，就会一直僵持
			if (mov1 > mov2) { // Ciel跑得快。首先不会输
				if (2 * mov2 + rng2 < mov1 + rng1) return "Ciel"; // 赢的条件为，在某次Ciel移动后，两者的距离dis满足dis > mov2 + rng2 && mov2 + dis <= mov1 + rng1，仅当2 * mov2 + rng2 < mov1 + rng1时，这样的dis才有可能存在。
				return "Draw";
			}
			if (mov2 > mov1) { // Liss的情况同理 
				if (2 * mov1 + rng1 < mov2 + rng2) return "Liss";
				return "Draw";
			}
		}
};
