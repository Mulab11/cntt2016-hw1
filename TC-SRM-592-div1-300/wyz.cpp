// BEGIN CUT HERE

// END CUT HERE
#line 5 "LittleElephantAndBalls.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
const int maxn=66;

class LittleElephantAndBalls{
	public:
	int getNumber(string S){
		int l[233],r[233],ret=0;
		memset(l,0,sizeof(l)*2+4);
		for (int i=0;i<S.length();++i){
			for (int j='A';j<='Z';++j) ret+=l[j]+r[j];
			if (!l[S[i]]) l[S[i]]=1;
			else r[S[i]]=1;
		}
		return ret;
	}
};

//this is for test
/*
int main(){
	LittleElephantAndBalls test;
//	test.run_test(-1);
	return 0;
}
*/
//test end
