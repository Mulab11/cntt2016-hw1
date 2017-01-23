#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
const int MAXN = 37;

class MapGuessing{
public:
	string code; LL freepos[MAXN], ans; int tot, n, m;
	inline int bitcount(LL x){
		int ret = 0;
		while(x) ret += x & 1, x >>= 1;
		return ret;
	}
	void dfs(int pos, LL fp, int cnt){ //Inclusion-exclusion principle: determined positions 0..pos-1, selected cnt positions from them, their common free set is fp
		if(pos == tot){
			if(!cnt) return;
			if(cnt & 1) ans += 1LL << bitcount(fp);
			else ans -= 1LL << bitcount(fp);
			return;
		} if(!fp) return;
		dfs(pos + 1, fp, cnt);
		dfs(pos + 1, fp & freepos[pos], cnt + 1);
	}
	LL countPatterns(string goal, vector <string> co){
		int i, j, pos; LL written, correct, best;
		n = goal.length();
		for(i = 0; i < int(co.size()); ++ i)
			code += co[i];
		m = code.length();
		for(i = 0; i < n; ++ i){ //Enumerate all initial positions
			for(j = written = correct = best = 0, pos = i; j < m; ++ j){ //written: all bits that code[0..j] has written in; correct: all bits that code[0..j] has correctly written in
				if(code[j] == '<' && (-- pos) < 0) break;
				else if(code[j] == '>' && (++ pos) >= n) break;
				else if(code[j] == '0' || code[j] == '1'){
					if((written & (1LL << pos)) == 0){
						written |= 1LL << pos;
						if(goal[pos] == code[j]) correct |= 1LL << pos;
					}else if((goal[pos] == code[j]) != bool(correct & (1LL << pos)))
						correct ^= 1LL << pos;
				} if(written == correct) best = written;
			} if(j == m) freepos[tot ++] = best;
		} dfs(0, (1LL << n) - 1, 0);
		return ans;
	}
};
