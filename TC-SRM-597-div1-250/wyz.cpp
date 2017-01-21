// BEGIN CUT HERE

// END CUT HERE
#line 5 "LittleElephantAndString.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;


class LittleElephantAndString{
	int n;
	int cnt[233];
	public:
	int getNumber(string A, string B){
		n=A.length();
		memset(cnt,0,sizeof(cnt));
		for (int i=0;i<n;++i) ++cnt[(int)A[i]];
		for (int i=0;i<n;++i)
			if ((--cnt[(int)B[i]])<0) return -1;
		int k=n;
		for (int i=n-1;i>=0;--i){
			for (--k;k>=0&&A[k]!=B[i];--k);
			if (k<0) return i+1;
		}
		return 0;
	}
};

//this is for test
/*
int main(){
	LittleElephantAndString test;
//	test.run_test(-1);
	return 0;
}
*/
//test end
