#include <bits/stdc++.h>

using namespace std;

const int N = 60;

class TravelOnMars{
	public:
		int n,a[N][N];
		int minTimes(vector <int> range, int startCity, int endCity){
			memset(a,0x3f,sizeof(a));
			n = range.size();
			for (int i = 0;i < n;i++) a[i][i] = 0;
			for (int i = 0;i < n;i++)
				for (int j = 0;j < n;j++)
					if (abs(i-j) <= range[i] || n-abs(i-j) <= range[i])
						a[i][j] = 1;
			for (int k = 0;k < n;k++)
				for (int i = 0;i < n;i++) 
					for (int j = 0;j < n;j++)
						a[i][j] = min(a[i][j],a[i][k]+a[k][j]);
			return a[startCity][endCity];
		}
};
