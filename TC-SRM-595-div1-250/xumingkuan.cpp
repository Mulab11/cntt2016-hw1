#include <cstring>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <cctype>
#include <cassert>
using namespace std;

class LittleElephantAndIntervalsDiv1
{
private:
	int a[1010];//balls
	bool b[1010];//stages
public:
	long long getNumber(int M, vector<int> L, vector<int> R)
	{
		memset(a, -1, sizeof(a));
		for(int i = 0; i < L.size(); i++)
			for(int j = L[i]; j <= R[i]; j++)//paint
				a[j] = i;
		memset(b, false, sizeof(b));
		int ans = 0;
		for(int i = 1; i <= M; i++)
			if(a[i] >= 0 && !b[a[i]])
				b[a[i]] = true, ans++;
		return 1ll << ans;
	}
};

