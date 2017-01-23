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

const int MAXN = 50 + 5;

class KingdomAndDice
{
	public:
	
	int n, m;
	vector<int> sp, cnt;
	bool f[MAXN][MAXN * MAXN];
	
	double newFairness(vector<int> firstDie, vector<int> secondDie, int X)
	{
		n = firstDie.size();
		for(int i = 0; i < n; i++)
			sp.push_back(secondDie[i]);
		sp.push_back(0), sp.push_back(X + 1);
		sort(sp.begin(), sp.end());
		for(int i = 0; i < sp.size() - 1; i++)
			cnt.push_back(sp[i + 1] - sp[i] - 1);
		cnt.push_back(0);
		
		m = 0;
		int cur = 0;
		for(int i = 0; i < n; i++)
			if(firstDie[i] == 0)
				m++;
			else
			{
				int pos = upper_bound(sp.begin(), sp.end(), firstDie[i]) - sp.begin() - 1;
				cur += pos, cnt[pos] -= 1;
			}
		
/*
		cout << endl;
		for(int i = 0; i < sp.size(); i++)
			cout << sp[i] << ' ';
		cout << endl;
		for(int i = 0; i < cnt.size(); i++)
			cout << cnt[i] << ' ';
		cout << endl;
*/
		memset(f, false, sizeof(f));
		for(int i = 0; i <= m; i++)
			f[i][cur] = true;
		
		for(int i = 1; i <= n; i++)
		{
			vector<int> v(0);
			int tmp = min(m, cnt[i]);
			for(int j = 1; j < tmp; j <<= 1)
				v.push_back(j), tmp -= j;
			v.push_back(tmp);
			for(int j = 0; j < v.size(); j++)
				for(int x = m; x >= 0; x--)
					for(int y = n * n; y >= 0; y--)
						if(x - v[j] >= 0 && y - v[j] * i >= 0)
							f[x][y] = f[x][y] | f[x - v[j]][y - v[j] * i];
		}
		int ans = -1;
		for(int i = 0; i <= n * n; i++)
			if(f[m][i])
				if(abs(2 * i - n * n) < abs(2 * ans - n * n))
					ans = i;
		
		return (double)ans / n / n;
	}
};

