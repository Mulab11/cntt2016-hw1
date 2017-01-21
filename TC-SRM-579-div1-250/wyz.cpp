// BEGIN CUT HERE

// END CUT HERE
#line 5 "UndoHistory.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;


class UndoHistory{
	public:
	int minPresses(vector <string> lines){
		int ret=0;
		for (int i=0;i<lines.size();++i){
			int now=0,mx=0;
			for (int j=0;j<i;++j){
				now=0;
				for (int k=0;k<min(lines[i].size(),lines[j].size());++k)
					if (lines[i][k]==lines[j][k]) ++now;
					else break;
				mx=max(mx,now);
			}
			if (i>0&&lines[i-1].size()!=now) ret+=lines[i].size()-mx+3;
			else ret+=min(lines[i].size()-mx+3,lines[i].size()-now+1);
		}
		return ret;
	}
};
