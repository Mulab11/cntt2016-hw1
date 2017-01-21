// BEGIN CUT HERE

// END CUT HERE
#line 5 "JumpFurther.cpp"

#include <bits/stdc++.h>
#define ll long long
using namespace std;

class JumpFurther {
	public:
	int furthest(int N, int badStep){
		for (int i=0;i<=N;++i){
			bool flag=1;
			for (int j=0,k=0;flag&&k<=N;++k)
				if (k!=i)if ((j+=k)==badStep)flag=0;
			if (flag) return (1+N)*N/2-i;
		}
	}
};
