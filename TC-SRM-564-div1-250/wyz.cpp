// BEGIN CUT HERE

// END CUT HERE
#line 5 "KnightCircuit2.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;


class KnightCircuit2{
	public:
	int maxSize(int w, int h){
		if (w>h) swap(w,h);//let w<=h
		if (w==1) return 1;
		if (w==2) return (h+1)>>1;
		if (w==3&&h==3) return 8;
		return w*h;
	}
};

//this is for test
/*
int main(){
	KnightCircuit2 test;
//	test.run_test(-1);
	return 0;
}
*/
//test end
