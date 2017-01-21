// BEGIN CUT HERE

// END CUT HERE
#line 5 "TeamContest.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;


class TeamContest{
	public:
	int worstRank(vector <int> strength){
		int a=strength[0],b=strength[1],c=strength[2];
		int val=max(a,max(b,c))+min(a,min(b,c));
		sort(strength.begin()+3,strength.end());
		int h=3,t=strength.size()-1,ret=1;
		while (h<t){
			if (strength[h]+strength[t]>val) h+=2,--t,++ret;
			else h+=3;
		}
		return ret;
	}
};
