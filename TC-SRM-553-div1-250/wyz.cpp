// BEGIN CUT HERE

// END CUT HERE
#line 5 "Suminator.cpp"

#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int maxn=55;

class Suminator {
	ll stk[maxn];int top;
	ll doit(const vector<int> &a){
		top=0;
		for (int i:a)
			if (i) stk[top++]=i;
			else if (top>1){
				--top;
				stk[top-1]+=stk[top];
			}
		return top?stk[top-1]:0;
	}
	public:
	int findMissing(vector <int> program, int wantedResult){
		int k=0;
		for (int i=1;i<program.size();++i)if (program[i]<0)k=i;
		ll res,last;
		program[k]=0;res=doit(program);
		if (res==wantedResult) return 0;
		program[k]=1;res=doit(program);
		if (res==wantedResult) return 1;
		if (res>wantedResult) return -1;
		last=res;
		program[k]=2;res=doit(program);
		if (last+1==res) return wantedResult-last+1;
		return -1;
	}
};
