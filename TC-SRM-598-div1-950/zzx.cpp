#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

int N;
vector<int> V[52];
bool S[52];

int tryN(int x)
{
	S[x] = true;

	int totnow = 0, diff = 0, sons = 0;
	for (vector<int>::iterator it = V[x].begin(); it != V[x].end(); ++it)
		if (!S[*it])
		{
			int aux = tryN(*it);
			totnow += aux;
			diff += (aux != 0);
			++sons;
		}

	return totnow + max(0, (sons - 1) - diff);
}

class TPS {
	public:
		int minimalBeacons(vector <string> linked) {
			N = linked.size();
			for (int i = 0; i < N; ++i)
				for (int j = 0; j < N; ++j)
					if (linked[i][j] == 'Y')
						V[i].push_back(j);

			if (N == 1) return 0;

			int result = 0x3f3f3f3f;
			for (int i = 0; i < N; ++i)
			{
				memset(S, 0, sizeof(S));
				int aux = tryN(i);
				result = min(result, 1 + aux);
			}

			return result;
		}
};
