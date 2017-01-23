#include <bits/stdc++.h>
using namespace std;

class TheJediTest{
public:
	int minimumSupervisors(vector <int> od, int k){
		int n = od.size(), i, ans = 0, dt;
		vector <int> nw(n);
		for(i = 0; i < n; ++ i){
			if(i == n - 1){
				if(od[i] + nw[i]) ans += (od[i] + nw[i] - 1) / k + 1;
				break;
			} dt = (od[i] + nw[i]) % k;
			if(od[i] >= dt){ //Always better to leave choice for the next level
				nw[i + 1] += dt;
				od[i] -= dt;
			}else{ //Use up all the space available otherwise
				dt = min(od[i + 1], k - dt);
				od[i + 1] -= dt;
				nw[i] += dt;
			} if(od[i] + nw[i]) ans += (od[i] + nw[i] - 1) / k + 1;
		} return ans;
	}
};
