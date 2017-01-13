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

class Excavations
{
private:
	int n;
	long long f[55][2][2];//f(D)(i)[j][k][l]: depth D, first i buildings, j excavated, k = if there is a building of depth D(min depth in its kind), l = if kind[i] is found, number of j-tuples
	pair<int, int> a[55];//<kind, depth>; temporarily used for discretization of depth
	bool type[55];//found
public:
	long long count(vector<int> kind, vector<int> depth, vector<int> found, int K)
	{
		n = kind.size();
		for(int i = 0; i < n; i++)
			a[i] = make_pair(depth[i], i);
		sort(a, a + n);
		int maxdepth = 0;
		for(int i = 0; i < n; i++)//discretization
			depth[a[i].second] = (i && a[i].first == a[i - 1].first ? maxdepth : ++maxdepth);
		
		for(int i = 0; i < n; i++)
			a[i] = make_pair(kind[i], depth[i]);
		sort(a, a + n);//kind ascend, then depth ascend
		memset(type, false, sizeof(type));
		for(int i = 0; i < found.size(); i++)
			type[found[i]] = true;
		
		long long ans = 0;
		for(int D = 1; D <= maxdepth; D++)
		{
			memset(f, 0, sizeof(f));
			f[0][0][0] = 1;
			for(int i = 0; i < n; i++)
			{
				for(int j = min(i, K - 1); j >= 0; j--)
				{
					f[j + 1][a[i].second == D][a[i].second <= D] += f[j][0][0];
					f[j + 1][1][a[i].second <= D] += f[j][1][0];
					f[j + 1][0][1] += f[j][0][1];
					f[j + 1][1][1] += f[j][1][1];
				}
				if(i == n - 1 || a[i].first != a[i + 1].first)//different kind
				{
					bool now = type[a[i].first];
					for(int j = 0; j <= i + 1 && j <= K; j++)
						for(int k = 0; k <= 1; k++)
						{
							f[j][k][0] = f[j][k][now];
							f[j][k][1] = 0;
						}
				}
			}
			ans += f[K][1][0];
			//printf("%d %I64d\n", D, ans);
		}
		return ans;
	}
};

