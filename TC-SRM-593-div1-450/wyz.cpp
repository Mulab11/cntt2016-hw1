// BEGIN CUT HERE

// END CUT HERE
#line 5 "MayTheBestPetWin.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
const int maxm=(1e6)+3;

class MayTheBestPetWin{
	bool f[maxm];
	int n;
	public:
	int calc(vector <int> A, vector <int> B){
		n=A.size();
		int sa=0,sb=0;
		memset(f,0,sizeof(f));f[0]=1;
		for (int i=0;i<n;++i){
			for (int j=sa+sb;j>=0;--j)if (f[j])
				f[j+A[i]+B[i]]=1;
			sa+=A[i];sb+=B[i];
		}
		int ret=maxm;
		for (int i=sa+sb;i>=0;--i)if (f[i])
			ret=min(ret,max(abs(i-sa),abs(i-sb)));
		return ret;
	}
};

//this is for test
/*
int main(){
	MayTheBestPetWin test;
//	test.run_test(-1);
	return 0;
}
*/
//test end
