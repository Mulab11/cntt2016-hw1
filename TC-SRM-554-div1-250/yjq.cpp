#include <algorithm>
using namespace std;
class TheBrickTowerEasyDivOne {
		public:
				int find(int n, int a, int m, int b) {
						if(n < m) swap(n, m);
						if(a == b) return min(n, m + 1) + m;
						return min(n, m + 1) + min(n + 1, m) + min(n, m);
				}
};
