// BEGIN CUT HERE

// END CUT HERE
#line 5 "BigFatInteger.cpp"
#include <bits/stdc++.h>
using namespace std;
#define ll long long
class BigFatInteger{
	public:
	int minOperations(int A, int B){
		int cnt=0,maxt=1;
		for (int i=2;i*i<=A;++i)if (A%i==0){//分解A
			++cnt;
			int now=0;
			for (;A%i==0;A/=i) ++now;
			maxt=max(maxt,now);//求A质因子中的最高次数
		}
		if (A>1) ++cnt;//统计大于sqrt(A)的质因子
		for (ll i=1;i<maxt*B;i<<=1) ++cnt;//统计操作2的使用次数
		return cnt;
	}
};

//this is for test
/*
int main(){
	BigFatInteger test;
//	test.run_test(-1);
	return 0;
}
*/
//test end
