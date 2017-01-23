#include <bits/stdc++.h>
using namespace std;

class FoxAndChess{
public:
	int getNext(int i, string &x){
		while(i < int(x.length()) && x[i] == '.') ++ i;
		return i;
	}
	string ableToMove(string st, string ed){
		int i, j, n = st.length();
		for(i = getNext(0, st), j = getNext(0, ed); i < n && j < n; i = getNext(i + 1, st), j = getNext(j + 1, ed))
			if(st[i] != ed[j] || (st[i] == 'L' && j > i) || (st[i] == 'R' && j < i)) return "Impossible";
		return i == n && j == n ? "Possible" : "Impossible";
	}
};
