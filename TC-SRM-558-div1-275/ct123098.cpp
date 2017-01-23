#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <ctime>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <typeinfo>

using namespace std;

const int MAXN = 100 + 10;
const int INF = 0x1f1f1f1f;

class Stamp
{
	public:
	
	int n;
	char col[MAXN];
	int f[MAXN];
	
	int getMinimumCost(string desiredColor, int stampCost, int pushCost)
	{
		n = desiredColor.size();
		for(int i = 1; i <= n; i++)
			col[i] = desiredColor[i - 1];
		int ans = INF;
		for(int L = 1; L <= n; L++)
		{
			memset(f, 31, sizeof(f));
			f[0] = 0;
			for(int i = 1; i <= n; i++)
			{
				int mx = 1, c = col[i];
				for(int j = i - 1; j >= 1; j--)
				{
					if(c == '*') c = col[j];
					if(c != '*' && col[j] != '*' && c != col[j]) break;
					mx++;
				}
//				cout << "  " << i << ' ' << mx << endl;
				for(int j = L; j <= mx; j++)
					f[i] = min(f[i], f[i - j] + (j + L - 1) / L);
			}
//			cout << L << ' ' << f[n] << endl;
			if(f[n] < INF)
				ans = min(ans, f[n] * pushCost + L * stampCost);
		}
		
		return ans;
	}
};

