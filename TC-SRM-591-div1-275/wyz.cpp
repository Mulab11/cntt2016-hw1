// BEGIN CUT HERE

// END CUT HERE
#line 5 "TheTree.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;


class TheTree{
	int d;
	public:
	int maximumDiameter(vector <int> cnt){
		d=cnt.size();
		int last=-1,ret=0;
		for (int i=0;i<d;++i){
//			printf("%d %d\n",i,(i-last)*2+d-i-1-(cnt[i]==1));
			ret=max(ret,(i-last)*2+d-i-1-(cnt[i]==1));
			if (cnt[i]==1) last=i;
		}
		return ret;
	}
};

//this is for test
/*
int main(){
	TheTree test;
//	test.run_test(-1);
	return 0;
}
*/
//test end
