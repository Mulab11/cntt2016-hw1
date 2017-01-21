// BEGIN CUT HERE

// END CUT HERE
#line 5 "BinPacking.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int cap=300;

class BinPacking{
	public:
	int minBins(vector <int> item){
		int ret=0;
		
		sort(item.begin(),item.end());
		for (int i=item.size()-1;i>=0;--i)if (item[i]){
			++ret;
			int k=-1;
			for (int j=0;j<i;++j)
				if (item[j]&&item[i]+item[j]<=cap)
					k=j;
			if (k==-1) continue;
			if (item[k]==100&&item[i]==100)
				for (int j=0;j<i;++j)
					if (j!=k&&item[j]==100){
						item[j]=0;
						break;
					}
			item[i]=item[k]=0;
		}
		return ret;
	}
};

//this is for test
/*
int main(){
	BinPacking test;
//	test.run_test(-1);
	return 0;
}
*/
//test end
