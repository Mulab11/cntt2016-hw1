#include <bits/stdc++.h>
using namespace std;

class TravelOnMars{
public:
	bool g[55][55]; int d[55], n;
	int minTimes(vector <int> range, int st, int ed){
		int i, j;
		n = range.size();
		for(i = 0; i < n; ++ i)
			for(j = i - range[i]; j <= i + range[i]; ++ j)
				g[i][((j % n) + n) % n] = true;
		queue <int> q;
		memset(d, 0, sizeof(d));
		d[st] = 1, q.push(st);
		while(!q.empty()){
			st = q.front(); q.pop();
			for(i = 0; i < n; ++ i)
				if(g[st][i] && !d[i]){
					d[i] = d[st] + 1;
					q.push(i);
				}
		} return d[ed] - 1;
	}
};
