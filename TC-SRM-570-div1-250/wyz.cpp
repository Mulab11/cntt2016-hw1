// BEGIN CUT HERE

// END CUT HERE
#line 5 "RobotHerb.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;


class RobotHerb{
	int n;
	public:
	long long getdist(int T, vector <int> a){
		const ll dx[4]={1,0,-1,0};
		const ll dy[4]={0,1,0,-1};
		n=a.size();
		ll x=0,y=0,d=0;
		for (int j=0;j<4;++j)
			for (int i=0;i<n;++i){
				x+=dx[d]*a[i];
				y+=dy[d]*a[i];
				(d+=a[i])&=3;
			}
		x*=(T>>2);
		y*=(T>>2);
		for (int j=0;j<(T&3);++j)
			for (int i=0;i<n;++i){
				x+=dx[d]*a[i];
				y+=dy[d]*a[i];
				(d+=a[i])&=3;
			}
		return abs(x)+abs(y);
	}
};
