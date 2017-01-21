// BEGIN CUT HERE

// END CUT HERE
#line 5 "TomekPhone.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn=55;

class TomekPhone{
	int cnt[maxn];
	public:
	int minKeystrokes(vector <int> frequencies, vector <int> keySizes){
		sort(frequencies.begin(),frequencies.end(),greater<int>());
		memset(cnt,0,sizeof(cnt));
		for (int sz:keySizes) ++cnt[sz];		
		for (int i=49;i;--i) cnt[i]+=cnt[i+1];
		int ret=0,p=1;
		for (int i:frequencies){
			while (p<=50&&!cnt[p]) ++p;
			if (p>50) return -1;
			--cnt[p];
			ret+=p*i;
		}
		return ret;
	}
};
