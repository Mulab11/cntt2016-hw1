// BEGIN CUT HERE

// END CUT HERE
#line 5 "BitwiseAnd.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
const int maxn=77;
#define lowbit(u) ((u)&-(u))

class BitwiseAnd{
	ll bin[maxn],b[maxn];
	int n,need;
	ll stk[maxn];int top;
	public:
	vector<long long> lexSmallest(vector<long long> subset, int N){
		vector<ll> NoSolution;
		need=N-(n=subset.size());
		for (int i=0;i<n;++i)
			for (int j=i+1;j<n;++j)
				if ((subset[i]&subset[j])==0) return NoSolution;
		for (int i=0;i<n;++i)
			for (int j=i+1;j<n;++j)
				for (int k=j+1;k<n;++k)
					if (subset[i]&subset[j]&subset[k]) return NoSolution;

		for (int i=0;i<60;++i) bin[i]=1LL<<i;
		top=0;
		for (int i=59;i>=0;--i){
			bool found=0;
			for (int j=0;j<n&&!found;++j)
				if (subset[j]&bin[i]) found=1;
			if (!found) stk[top++]=bin[i];
		}
		
		for (int i=0;i<n;++i){
			b[i]=0;
			for (int j=0;j<n;++j)if (j!=i)
				b[i]|=subset[j];
			b[i]=(b[i]&subset[i])^subset[i];
		}

		while (need--){
			ll now=0;
			for (int j=0;j<n;++j){
				if (!b[j]) return NoSolution;
				now^=lowbit(b[j]);
				b[j]^=lowbit(b[j]);
			}
			if (top<need) return NoSolution;
			b[n]=0;
			for (int j=0;j<need;++j) b[n]^=stk[--top];
			subset.push_back(now^b[n]);
			++n;
		}
		sort(subset.begin(),subset.end());
		return subset;
	}
};

//this is for test
/*
int main(){
	BitwiseAnd test;
//	test.run_test(-1);
	return 0;
}
*/
//test end
