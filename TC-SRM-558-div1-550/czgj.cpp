/*
	Simple counting.
	Go over pairs of blue points.
	Ans += left * right
*/

#include <bits/stdc++.h>
using namespace std;

class Ear {
	public:
	void getparam(vector<string> st, vector<int>& ret){
		int t = 0;
		for (int i = 0; i < st.size(); ++i)
			for (int j = 0; j < st[i].length(); ++j)
				if (st[i][j] == ' ') ret.push_back(t), t = 0;
					else t = t * 10 + st[i][j] - '0';
		ret.push_back(t);
	}
	vector<int> redX, blueX, blueY;
	int cnt[23333];
	long long getCount(vector <string> _redX, vector <string> _blueX, vector <string> _blueY) {
		redX.clear(); blueX.clear(); blueY.clear(); memset(cnt, 0, sizeof cnt);
		getparam(_redX, redX); getparam(_blueX, blueX); getparam(_blueY, blueY);
		int n = redX.size(), m = blueX.size(); long long ret = 0;
		for (int i = 0; i < n; ++i) cnt[redX[i]] = 1;
		for (int i = 1; i <= 10000; ++i) cnt[i] += cnt[i - 1];
		for (int i = 0; i < m; ++i) for (int j = 0; j < i; ++j){ // P & Q
			int ti = i, tj = j, left = 0, right = 0;
			if (blueY[i] < blueY[j]) swap(ti, tj); // ti the upper
			for (int k = 0; k < n; ++k) // all possible point A
				if (redX[k] < blueX[ti] && (blueX[tj] - redX[k]) * blueY[ti] > (blueX[ti] - redX[k]) * blueY[tj])
					left += cnt[blueX[tj] - 1] - cnt[redX[k]];
			for (int k = 0; k < n; ++k) // all possible point D
				if (redX[k] > blueX[ti] && (blueX[tj] - redX[k]) * blueY[ti] < (blueX[ti] - redX[k]) * blueY[tj])
					right += cnt[redX[k] - 1] - cnt[blueX[tj]];
			ret += left * right;
		}
		return ret;
	}
};

/*
	I was able to meet you at last
	I was able to meet you by chance
	Taikutsu na monokuro no hibi
	Awaku someru sakura
		- My Dear Friend
*/
