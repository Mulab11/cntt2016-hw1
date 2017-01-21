// BEGIN CUT HERE

// END CUT HERE
#line 5 "TheJediTest.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;


class TheJediTest{
	public:
	int minimumSupervisors(vector <int> students, int K){
		int last=0,ret=0;
		for (int i=0;i<students.size();++i){
			ret+=(students[i]+last)/K;
			if ((students[i]+last)%K<=students[i]) last=(students[i]+last)%K;
			else{
				if (i<students.size()) students[i+1]-=min(students[i+1],K-(students[i]+last)%K);
				last=0;
				++ret;
			}
		}
		if (last) ++ret;
		return ret;
	}
};
