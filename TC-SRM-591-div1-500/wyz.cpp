// BEGIN CUT HERE

// END CUT HERE
#line 5 "PyramidSequences.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
inline int gcd(int a,int b){return b?gcd(b,a%b):a;}

class PyramidSequences{
	public:
	long long distinctPairs(int N, int M){
		ll d=gcd(2*N-2,2*M-2);
/*		if (d==2) return (ll)N*M/2;
		return 0;*/
		ll a=(N-1)/d,b=(M-1)/d,x=a+((N-1)%d!=0),y=b+((M-1)%d!=0),ret=x*y+a*b+(d/2-1)*(x+a)*(y+b);
		if ((N-1)%d!=0) ++a,ret+=b;
		else ++x,ret+=y;
		if ((M-1)%d!=0) ++b,ret+=a;
		else ++y,ret+=x;
		return ret;
	}
};

//this is for test
/*
int main(){
	PyramidSequences test;
//	test.run_test(-1);
	return 0;
}
*/
//test end
