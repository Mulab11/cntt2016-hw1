// BEGIN CUT HERE

// END CUT HERE
#line 5 "AlternateColors2.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;


class AlternateColors2{
	public:
	long long countWays(int n, int k){
		ll ret=0;
		if (k%3==1) ret+=((ll)n-k+2)*(n-k+1)/2;//min(G,B)>=k/3
		if (k%3==2) ++ret;//G==B==k/3
		for (int i=0;i<k/3;++i)//i=min(G,B)
			if ((k-i*3)&1) ret+=(n-i*3-(k-i*3)/2)*2-1;
			else ret+=((k-i*3)/2)*2-1;
		return ret;
	}
};

//this is for test
/*
int main(){
	AlternateColors2 test;
//	test.run_test(-1);
	return 0;
}
*/
//test end
