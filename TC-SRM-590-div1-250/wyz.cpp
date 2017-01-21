// BEGIN CUT HERE

// END CUT HERE
#line 5 "FoxAndChess.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
const int maxn=55;


class FoxAndChess{
	int type[maxn];
	int pos[maxn],to[maxn],n;
	public:
	string ableToMove(string begin, string target){
		n=0;
		for (int i=0;i<begin.size();++i)if (begin[i]!='.'){
			pos[++n]=i;
			type[n]=begin[i]=='R';
		}
		int n0=0;
		for (int i=0;i<begin.size();++i)if (target[i]!='.'){
			to[++n0]=i;
			if (n0>n||type[n0]!=(target[i]=='R')) return "Impossible";
		}
		if (n0<n) return "Impossible";
		for (int i=1;i<=n;++i)
			if ((pos[i]<to[i]&&!type[i])||(pos[i]>to[i]&&type[i])) return "Impossible";
		return "Possible";
	}
};

//this is for test
/*
int main(){
	FoxAndChess test;
//	test.run_test(-1);
	return 0;
}
*/
//test end
