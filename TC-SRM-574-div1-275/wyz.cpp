// BEGIN CUT HERE

// END CUT HERE
#line 5 "TheNumberGame.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;


class TheNumberGame{
	bool check(int a,int b){
		int x=1;
		while (x<=b) x*=10;
		while (a)
			if (a%x==b) return 1;
			else a/=10;
		return 0;
	}
	public:
	string determineOutcome(int A, int B){
		bool ret=check(A,B);
		int tmp=A;
		A=0;
		for (A=0;tmp;tmp/=10) A=A*10+tmp%10;
		ret=ret||check(A,B);
		return ret?"Manao wins":"Manao loses";
	}
};
