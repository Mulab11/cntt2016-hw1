#include <bits/stdc++.h>

using namespace std;

const int N = 60,inf = 0x3f3f3f3f;

class Egalitarianism{
	public:
		int a[N][N],n;
		int maxDifference(vector <string> rec, int d){
			n = rec.size();
			for (int i = 0;i < n;i++)
				for (int j = 0;j < n;j++)
					if (i != j)
					if (rec[i][j] == 'Y') a[i][j]  = 1;else a[i][j] = inf;
			for (int k = 0;k < n;k++)
				for (int i = 0;i < n;i++)
					for (int j = 0;j < n;j++)
						a[i][j] = min(a[i][j],a[i][k]+a[k][j]);
			int mx=0;
			for (int i = 0;i < n;i++)
				for (int j = 0;j < n;j++) 
					mx = max(mx,a[i][j]);
			if (mx >= inf) return -1;
			return mx*d;
		}
};
