#include <bits/stdc++.h>
using namespace std;
const int MAXM = 13;

class EllysBulls{
public:
	map <vector <int>, vector <string> > prev; int n, m, M;
	string cur, ans; vector <int> match, occur[MAXM][10], cnt;
	vector <string> guess;
	void dfsGen(int dep){
		if(dep == M){
			prev[match].push_back(cur);
			return;
		} int i, j;
		for(i = 0; i < 10; ++ i){
			cur[dep] = i + '0';
			for(j = 0; j < int(occur[dep][i].size()); ++ j)
				++ match[occur[dep][i][j]];
			dfsGen(dep + 1);
			for(j = 0; j < int(occur[dep][i].size()); ++ j)
				-- match[occur[dep][i][j]];
		}
	}
	void dfsGet(int dep){
		if(ans[0] == 'A') return;
		int i;
		for(i = 0; i < n; ++ i)
			if(match[i] > cnt[i])
				return;
		if(dep < M){
			for(i = 0; i < n; ++ i)
				match[i] = cnt[i] - match[i];
			if(prev.find(match) != prev.end()){
				if(ans[0] != 'L' || prev[match].size() > 1) ans = "Ambiguity";
				else ans = prev[match][0] + cur;
			}
			for(i = 0; i < n; ++ i)
				match[i] = cnt[i] - match[i];
			return;
		} int j;
		for(i = 0; i < 10; ++ i){
			cur[dep - M] = i + '0';
			for(j = 0; j < int(occur[dep][i].size()); ++ j)
				++ match[occur[dep][i][j]];
			dfsGet(dep - 1);
			for(j = 0; j < int(occur[dep][i].size()); ++ j)
				-- match[occur[dep][i][j]];
		}
	}
	string getNumber(vector <string> guess_, vector <int> cnt_){
		int i, j;
		guess = guess_, cnt = cnt_;
		n = guess.size(), m = guess[0].length();
		for(i = 0; i < m; ++ i)
			for(j = 0; j < n; ++ j)
				occur[i][guess[j][i] - '0'].push_back(j);
		M = m >> 1; while(M --) cur += '\0';
		M = m >> 1; match.resize(n); dfsGen(0);
		cur = ""; for(M = n - M; M; -- M) cur += '\0';
		M = m >> 1; ans = "Liar"; dfsGet(m - 1);
		return ans;
	}
};
