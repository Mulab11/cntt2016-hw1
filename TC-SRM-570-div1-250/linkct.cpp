#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

class RobotHerb{
public:
	LL getdist(int T, vector <int> a){
		int n = a.size(), i, d = 0;
		LL x = 0, y = 0, ax = 0, ay = 0;
		for(i = 0; i < 4 * n; ++ i){
			if(T % 4 == i / n && T % 4 == (i - 1) / n + 1)
				ax = x, ay = y;
			x += dx[d] * a[i % n];
			y += dy[d] * a[i % n];
			d = (d + a[i % n]) % 4;
			if(T % (4 * n) == i)
				ax = x, ay = y;
		} return abs(ax + T / 4LL * x) + abs(ay + T / 4LL * y);
	}
};
