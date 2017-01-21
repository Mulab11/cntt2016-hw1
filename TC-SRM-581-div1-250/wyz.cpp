// BEGIN CUT HERE

// END CUT HERE
#line 5 "SurveillanceSystem.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn=55;

class SurveillanceSystem{
	int n;
	int cnt[maxn],a[maxn],b[maxn];
	int s[maxn];
	public:
	string getContainerInfo(string containers, vector <int> reports, int L){
		memset(cnt,0,sizeof(cnt));
		for (int i=0;i<reports.size();++i) ++cnt[reports[i]];
		n=containers.size();
		s[L]=0;
		for (int i=0;i<L;++i) s[L]+=containers[i]=='X';
		for (int i=L;i<n;++i) s[i+1]=s[i]+(containers[i]=='X')-(containers[i-L]=='X');
		string ret="";
		for (int i=1;i<=n;++i){
			memset(a,0,sizeof(a));
			memset(b,0,sizeof(b));
			for (int j=L;j<=n;++j)
				if (j-L+1<=i&&i<=j) ++a[s[j]];
				else ++b[s[j]];
			bool fa=0,fb=1;
			for (int i=0;i<=L;++i) if (a[i]&&cnt[i]) fa=1;
			for (int i=0;i<=L;++i) if (b[i]<cnt[i]) fb=0;
			if (fa&&fb) ret.push_back('?');
			else if(fa) ret.push_back('+');
			else if(fb) ret.push_back('-');
			else return "wyzsb";
		}
		return ret;
	}
};
