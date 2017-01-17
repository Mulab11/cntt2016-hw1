#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 60;

class SkiResorts{
	public:
		int n,e[N*N],a[N][N];
		ll ans,d[N*N];
		bool bo[N*N];
	    long long minCost(vector <string> road, vector <int> altitude) {
	    	n = road.size();
	    	memset(d,0x3f,sizeof(d));
	    	ans = d[0];
			int t = 1,w = 0;
			e[++w] = cal(0,0);
			for (int i = 0;i < n;i++)
				for (int j = 0;j < n;j++)
					a[i][j] = cal(i,j);
			d[0] = 0;
			/*
				一开始0要枚举所有可能的初始高度 
			*/
			for (int i = 0;i < n;i++)
				d[a[0][i]] = abs(altitude[i]- altitude[0]);
			while (t <= w){
				int u = e[t];
				bo[u] = 1;
				//cout << u << endl;
				for (int i = 0;i < n;i++)
					for (int j = 0;j < n;j++)
						if (road[u/n][i] == 'Y'){
							if (altitude[j] <= altitude[u%n]){
								if (d[a[i][j]] > d[u] + abs(altitude[j]-altitude[i])){
									d[a[i][j]] = d[u] + abs(altitude[j]-altitude[i]);
								}
							}
						}
				int v = -1;
				for (int i = 0;i < n;i++)
					for (int j = 0;j < n;j++)
						if (!bo[a[i][j]]){
							if (v == -1) v = a[i][j];
							else if (d[a[i][j]] < d[v]) v = a[i][j];
						}
				if (v != -1) e[++w] = v;		
				t++;
			}
			for (int i = 0;i < n;i++)
				ans = min(ans,d[a[n-1][i]]);
			if (ans >= 0x3f3f3f3f3f3f3f3f) ans = -1;
			return ans;
		}
		int cal(int x,int y){
			return x*n+y;
		}
};
