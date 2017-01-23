#include <bits/stdc++.h>

using namespace std;

int n = 0 ;  

class PiecewiseLinearFunction {
		public:
				int maximumSolutions(vector<int> tmp) {
						n = tmp.size();
						for(int i = 1; i < n; i++) if(tmp[i - 1] == tmp[i]) return -1;
						vector<int> a;
						for(int i = 0; i < n; i++) tmp[i] <<= 1;  
						for(int i = 0; i < n; i++) a.push_back(tmp[i]), a.push_back(tmp[i] + 1);
						int ans = 0, cnt = 0 ;
						for(int i = 0; i < a.size(); i++) {
								cnt = 0; 
								for(int j = 1; j < n; j++) 
										if (max(tmp[j - 1], tmp[j]) > a[i] && min(tmp[j - 1], tmp[j]) < a[i]) cnt ++ ; 
								for(int j = 0; j < n; j++) if (tmp[j] == a[i]) cnt ++ ;
								if (cnt > ans) ans = cnt ;  
						}
						return ans;
				}
} sol ;

int main() { 
		vector<int> g ; 
		g.push_back(1) ,g.push_back(4), g.push_back(-1), g.push_back(2) ; 
		printf("%d\n", sol.maximumSolutions(g)) ; 
}
