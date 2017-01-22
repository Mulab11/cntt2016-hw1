/*
	Brute force.
	No comment.
*/
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> PI;
queue<PI> Q;
bool vis[64][1025];
void push(int p, int x){
	if (!vis[p][x]){
		Q.push(PI(p, x));
		vis[p][x] = 1;
	}
}
class XorTravelingSalesman {
	public:
	int maxProfit(vector <int> cityValues, vector <string> roads) {
		int n = cityValues.size(), ret = 0;
		memset(vis, 0, sizeof vis);
		push(0, cityValues[0]);
		while (!Q.empty()){
			int p = Q.front().first, x = Q.front().second; Q.pop();
			if (x > ret) ret = x;
			for (int i = 0; i < n; ++i)
				if (roads[p][i] == 'Y')
					push(i, x ^ cityValues[i]);
		}
		return ret;
	}
};


/*
	I can't believe in you
	I'd see you another day another way
	Nobody's standing near
	There are something you can't see or feel, baby
		- Re:make
*/

