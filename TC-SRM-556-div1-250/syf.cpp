//============================================================================
// Author       : Sun YaoFeng
//============================================================================

#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

class XorTravelingSalesman {
public:	
	int maxProfit(vector <int> cityValues, vector <string> roads) {
		//f[u][p] == false means we have not visited the state (u, p).
		bool f[60][2000];
		
		queue < pair <int, int>  > Q;
		while (!Q.empty()) Q.pop();
		int res = 0;
		int n = cityValues.size();
		
		memset (f, false, sizeof(f));
		
		Q.push(make_pair(0, cityValues[0]));
		f[0][cityValues[0]] = true;
		res = cityValues[0];
		
		//SPFA
		
		while (!Q.empty()) {
			pair <int, int> u = Q.front();
			Q.pop();
			
			for (int i = 0; i < n; i++)
				if (i != u.first && (roads[i][u.first] == 'Y' || roads[u.first][i] == 'Y')) {	//trans
					pair<int, int> v;
					v.first = i;
					v.second = u.second ^ cityValues[i];
					if (!f[v.first][v.second]) {
						f[v.first][v.second] = true;
						res = max (res, v.second);
						Q.push(v);
					}
				}
		}
		
		return res;
	}
};