#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
const int MAXN = 55;

class Suminator{
public:
	struct stackValue{
		LL k, b;
		void var(int x, int y){k = x, b = y;}
	}s[MAXN];
	int n, top, target; vector <int> prog;
	bool simulate(){ //Run the program with -1 being 0
		static LL s[MAXN]; int i;
		for(i = top = 0; i < n; ++ i){
			if(!prog[i]){
				if(top < 2) continue;
				s[top - 1] += s[top];
				-- top;
			}else s[++ top] = prog[i];
		} if(!top) s[top = 1] = 0;
		return s[top] == target;
	}
	int findMissing(vector <int> p, int tg){
		int i;
		prog = p; n = prog.size(); target = tg;
		for(i = 0; i < n; ++ i)
			if(prog[i] == -1) break;
		prog[i] = 0; if(simulate()) return 0; //Case 0: -1 is replaceable with 0, apparently the best solution
		for(prog[i] = -1, i = top = 0; i < n; ++ i){ //Run the program with -1 not being 0, but some constant; s[i].k stores whether s[i] contains the constant
			if(prog[i] == -1){
				s[++ top].var(1, 0);
				continue;
			}
			if(!prog[i]){
				if(top < 2) continue;
				s[top - 1].k += s[top].k;
				s[top - 1].b += s[top].b;
				-- top;
			}else s[++ top].var(0, prog[i]);
		} if(!top) s[top = 1].var(0, 0);
		if(s[top].k == 0){ //Case 1: -1 not included in the top, so its value is irrelevant
			if(s[top].b == target) return 1; //Solution exists, return the smallest positive integer
			return -1; //Solution doesn't exist
		} //Case 2: -1 included in the top, unique solution exists
		if(target - s[top].b <= 0 || target - s[top].b > 1000000000) //Solution exists but is out of range
			return -1;
		return target - s[top].b;
	}
};
