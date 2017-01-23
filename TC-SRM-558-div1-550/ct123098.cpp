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

const int MAXN = 300 + 100;

class Ear
{
	public:
	
	int n, m;
	int a[MAXN];
	int bx[MAXN], by[MAXN];
	int left[MAXN][MAXN], right[MAXN][MAXN];
	
	void read(vector<string> redX, vector<string> blueX, vector<string> blueY)
	{
		stringstream ss;
		int x = 0;
		
		ss.clear();
		for(int i = 0; i < redX.size(); i++) ss << redX[i];
		n = 0;
		while(ss >> x) a[++n] = x;
		
		ss.clear();
		for(int i = 0; i < blueX.size(); i++) ss << blueX[i];
		m = 0;
		while(ss >> x) bx[++m] = x;
		
		ss.clear();
		for(int i = 0; i < blueY.size(); i++) ss << blueY[i];
		m = 0;
		while(ss >> x) by[++m] = x;
	}
	
	int cross(int x, int p, int q)
	{
		int tmp = (bx[p] - a[x]) * (by[q]) - (bx[q] - a[x]) * (by[p]);
		if(tmp == 0) return 0;
		return tmp > 0 ? 1 : -1;
	}
	
	long long getCount(vector<string> redX, vector<string> blueX, vector<string> blueY)
	{
		read(redX, blueX, blueY);
		
		sort(a + 1, a + n + 1);
		
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++)
				left[i][j] = left[i - 1][j] + min(j, i - 1);
		for(int i = n; i >= 1; i--)
			for(int j = n; j >= 1; j--)
				right[i][j] = right[i + 1][j] + min(n - i, n - j + 1);
/*
		for(int i = 1; i <= n; i++)
		{
			for(int j = 0; j <= n; j++)
				cout << left[i][j] << ' ';
			cout << endl;
		}
*/		
		long long ans = 0;
		for(int i = 1; i <= m; i++)
			for(int j = 1; j <= m; j++)
				if(by[i] > by[j])
				{
					int li = 0, ri = n + 1, lj = 0, rj = n + 1;
					for(int k = 1; k <= n; k++)
						if(cross(k, i, j) == -1 && a[k] < bx[i]) li = k;
					for(int k = 1; k <= n; k++)
						if(a[k] < bx[j]) lj = k;
					for(int k = n; k >= 1; k--)
						if(cross(k, i, j) == 1 && a[k] > bx[i]) ri = k;
					for(int k = n; k >= 1; k--)
						if(a[k] > bx[j]) rj = k;
					ans += (long long)left[lj][li] * right[rj][ri];
				}
		
		return ans;
	}
};

