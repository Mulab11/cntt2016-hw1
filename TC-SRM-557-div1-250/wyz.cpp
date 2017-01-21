// BEGIN CUT HERE

// END CUT HERE
#line 5 "FoxAndMountainEasy.cpp"

#include <bits/stdc++.h>
#define ll long long
using namespace std;

class FoxAndMountainEasy {
	public:
	string possible(int n, int h0, int hn, string history){
		if ((h0^hn^n)&1) return "NO";
		int s=0,mn=0;
		for (int i=0;i<history.size();++i){
			s+=2*(history[i]=='U')-1;
			mn=min(mn,s);
		}
		if (h0+n-(int)history.size()+s<hn) return "NO";
		if (h0-n+(int)history.size()+s>hn) return "NO";
		int x=hn-h0-s,y=0;
		if (x<0) swap(x=-x,y);
		int tmp=(n-(int)history.size()-x-y)/2;
		x+=tmp;y+=tmp;
//		printf("%d %d\n",x,y);
		if (x<-h0-mn) return "NO";
		if (y<s-hn) return "NO";
		return "YES";
	}
};
