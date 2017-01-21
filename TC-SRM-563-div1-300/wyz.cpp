// BEGIN CUT HERE

// END CUT HERE
#line 5 "FoxAndHandle.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn=55;

class FoxAndHandle{
	int n;
	int cnt[maxn][26];
	int need[26];
	public:
	string lexSmallestName(string S){
		n=S.size();
		memset(cnt[n],0,sizeof(cnt[n]));
		for (int i=n-1;i>=0;--i)
			for (int j=0;j<26;++j)
				cnt[i][j]=cnt[i+1][j]+(S[i]-'a'==j);
		for (int j=0;j<26;++j) need[j]=cnt[0][j]>>1;
		string ret="";
		for (int i0=(n>>1),p=0,q;i0;--i0,p=q+1){
			q=-1;
			for (int i=p;i<n;++i)if ((q<0||S[i]<S[q])&&need[S[i]-'a']){
				bool found=0;
				for (int j=0;j<26&&!found;++j)
					if (need[j]>cnt[i][j])
						found=1;
				if (found) break;
				q=i;
			}
			ret+=S[q];
			--need[S[q]-'a'];
		}
		return ret;
	}
};
