// BEGIN CUT HERE

// END CUT HERE
#line 5 "TheDivisionGame.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxDlt=(1e6)+7;


class TheDivisionGame{
	int a[maxDlt];
	int cnt[maxDlt];
	int last[233];
	public:
	long long countWinningIntervals(int L, int R){
		int stamp=0;
		for (int i=L;i<=R;++i)
			a[stamp++]=i;
		for (int i=2;i*i<=R;++i)
			for (int j=(L-1)/i+1,k;(k=i*j)<=R;++j)
				for (;a[k-L]%i==0;a[k-L]/=i) ++cnt[k-L];
		ll ret=0;
		memset(last,0,sizeof(last));
		last[0]=1;
		for (int i=0;i<stamp;++i){
			cnt[i]+=(a[i]>1);
			a[i]=cnt[i]^a[i-1];
			ret+=1LL+i-last[a[i]];
			++last[a[i]];
		}
		return ret;
	}
};
