// BEGIN CUT HERE

// END CUT HERE
#line 5 "LittleElephantAndIntervalsDiv1.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
const int maxn=1003;

class LittleElephantAndIntervalsDiv1{
	bool vis[maxn];
	public:
	long long getNumber(int M, vector <int> L, vector <int> R){
		ll ret=1;
		memset(vis,0,sizeof(vis));
		for (int i=L.size()-1;i>=0;--i){
			bool found=0;
			for (int j=L[i];j<=R[i];++j)
				if (!vis[j]) vis[j]=found=1;
			if (found) ret<<=1;
		}
		return ret;
	}
};

//this is for test
/*
int main(){
	LittleElephantAndIntervalsDiv1 test;
//	test.run_test(-1);
	return 0;
}
*/
//test end
