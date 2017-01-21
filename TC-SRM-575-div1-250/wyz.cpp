// BEGIN CUT HERE

// END CUT HERE
#line 5 "TheNumberGameDivOne.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;


class TheNumberGameDivOne{
	public:
	string find(long long n){
		if (n==1) return "Brus";
		if (n&1) return "Brus";
		int cnt=0;
		while (1^n&1) ++cnt,n>>=1;
		if (n==1&&(cnt&1)) return "Brus";
		return "John";
	}
};
