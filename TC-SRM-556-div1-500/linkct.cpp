#include <bits/stdc++.h>
using namespace std;
const int MAXN = 55;

class LeftRightDigitsGame2{
public:
	bool vis[MAXN][MAXN][3]; string dp[MAXN][MAXN][3], deck, lb;
	inline int comp(char a, char b){return a == b ? 1 : (a < b ? 0 : 2);}
	inline void update(string &a, string b, char c){
		if(b.empty()) return;
		b += c;
		if(a.empty() || a > b) a = b;
	}
	inline void update(string &a, char b, string c){
		if(c.empty()) return;
		c = b + c;
		if(a.empty() || a > c) a = c;
	}
	string solve(int l, int r, int cp){ //Current cards on the table correspond to range [l..r] of the lowerbound; their relation with lowerbound is cp(0 for smaller, 1 for equal, 2 for larger)
		if(vis[l][r][cp]) return dp[l][r][cp];
		vis[l][r][cp] = true;
		string &f = dp[l][r][cp]; f = "";
		char add = deck[r - l];
		if(l == r) return f = (comp(add, lb[r]) == cp ? (string("") + add) : "");
		if(cp == 1){
			if(add == lb[r])
				update(f, solve(l, r - 1, cp), add);
			if(add == lb[l])
				update(f, add, solve(l + 1, r, cp));
		}else{
			//Put the last card to the right end
			update(f, solve(l, r - 1, cp), add);
			if(comp(add, lb[r]) == cp) update(f, solve(l, r - 1, 1), add);
			//Put the last card to the left end
			if(comp(add, lb[l]) == cp){
				update(f, add, solve(l + 1, r, 0));
				update(f, add, solve(l + 1, r, 1));
				update(f, add, solve(l + 1, r, 2));
			}else if(add == lb[l])
				update(f, add, solve(l + 1, r, cp));
		} return f;
	}
	string minNumber(string deck_, string lb_){
		deck = deck_, lb = lb_;
		memset(vis, false, sizeof(vis));
		int n = deck.length();
		return solve(0, n - 1, 1).length() ? lb : solve(0, n - 1, 2);
	}
};
