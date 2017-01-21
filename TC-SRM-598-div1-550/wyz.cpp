// BEGIN CUT HERE

// END CUT HERE
#line 5 "FoxAndFencing.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;


class FoxAndFencing{
	public:
	string WhoCanWin(int mov1, int mov2, int rng1, int rng2, int d){
		if (mov1+rng1>=d) return "Ciel";
		if (mov2+rng2>=mov1+d) return "Liss";
		if (mov1>mov2&&mov2+mov2+rng2<mov1+rng1) return "Ciel";
		if (mov2>mov1&&mov1+mov1+rng1<mov2+rng2) return "Liss";
		return "Draw";
	}
};

//this is for test
/*
int main(){
	FoxAndFencing test;
//	test.run_test(-1);
	return 0;
}
*/
//test end
