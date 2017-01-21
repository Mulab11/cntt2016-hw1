// BEGIN CUT HERE

// END CUT HERE
#line 5 "IncrementAndDoubling.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;


class IncrementAndDoubling{
	public:
	int getMin(vector <int> desiredArray){
		int cnt=0,maxl=0;
		for (int i=0;i<desiredArray.size();++i){
			int j=0;
			for (int k=1;k<=desiredArray[i];(k<<=1),++j)
				if (desiredArray[i]&k) ++cnt;
			maxl=max(maxl,j-1);
		}
		return cnt+maxl;
	}
};

//this is for test
/*
int main(){
	IncrementAndDoubling test;
//	test.run_test(-1);
	return 0;
}
*/
//test end
