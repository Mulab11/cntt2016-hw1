//============================================================================
// Author       : Sun YaoFeng
//============================================================================

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

#define oo 200

class OldBridges {
public:
	int cap[60][60], cap__[60][60], n;
	int s, t, an, bn;
	int max_flow;
	int trace[60];
	int f[60][60];
	
	bool find_path() {	//BFS
		queue<int> q;
		memset(trace, -1, sizeof(trace));
		q.push(s);
		trace[s] = s;
		
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			
			for (int v = 0; v < n; v++)
				if (trace[v] == -1 && cap[u][v] > f[u][v]) {
					trace[v] = u;
					q.push(v);
					if (v == t) return true;
				}
		}
		
		return false;
	}
	
	void increase_flow() {	//Updata
		int u = t;
		int delta = oo;
		
		while (u != s) {
			delta = min(delta, cap[trace[u]][u] - f[trace[u]][u]);
			u = trace[u];
		}
		
		u = t;
		while (u != s) {
			f[trace[u]][u] += delta;
			f[u][trace[u]] -= delta;
			u = trace[u];
		}	
		
		max_flow += delta;
	}
	
	int flow(int s1, int s2, int t1, int t2) {
		memset(cap, 0, sizeof(cap));
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				cap[i][j] = cap__[i][j];	//build graph
				
		s = n; 
		t = n + 1;

		n = n + 2; 		//for convenience
		
		cap[s][s1] = 2 * an;
		cap[s][s2] = 2 * bn;
		cap[t1][t] = 2 * an;
		cap[t2][t] = 2 * bn;
	
		memset(f, 0, sizeof(f));
		max_flow = 0;
		while (find_path()) increase_flow();
		
		//n should keep the original value of it
		n = n - 2;
		return max_flow;
	}
	
	string isPossible(vector <string> bridges, int a1, int a2, int an_, int b1, int b2, int bn_) {
		n = bridges.size();
		
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				cap__[i][j] = bridges[i][j] == 'X' ? 0: bridges[i][j] == 'O' ? 2 : oo;
				
		an = an_;
		bn = bn_;

		return (flow(a1, b1, a2, b2) >= 2 * (an + bn)) && (flow(a1, b2, a2, b1) >= 2 * (an + bn))? "Yes" : "No";
	}
};