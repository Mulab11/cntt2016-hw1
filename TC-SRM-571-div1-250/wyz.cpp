// BEGIN CUT HERE

// END CUT HERE
#line 5 "FoxAndMp3.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;


string int_to_string(int x){
	string ret="";
	for (;x;x/=10) ret=(char)(x%10+48)+ret;
	return ret;
}

class FoxAndMp3{
	vector<string> a;
	public:
	vector <string> playList(int n){
		vector<string> ret;
		if (n<=50){
			for (int i=1;i<=n;++i) a.push_back(int_to_string(i));
			sort(a.begin(),a.end());
			for (int i=0;i<a.size();++i) ret.push_back(a[i]+".mp3");
			return ret;
		}
		int u=1;
		ret.push_back("1.mp3");
		for (int i=1;i<50;++i,ret.push_back(int_to_string(u)+".mp3"))
			if (10LL*u<=n) u*=10;
			else if ((++u)%10==0) u/=10;
			else while (u>n&&u%10!=0) if ((++u)%10==0) u/=10;
		return ret;
	}
};
