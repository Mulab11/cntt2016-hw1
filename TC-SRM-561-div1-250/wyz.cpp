// BEGIN CUT HERE

// END CUT HERE
#line 5 "ICPCBalloons.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;

void Min(int &x,int y){if (x<0||y<x) x=y;}

const int maxn=55;

class ICPCBalloons{
	vector<int> ball[2];
	int ac[maxn],m;
	int bl[maxn];
	int ans;
	void dfs(int u){
		if (u==m){
			vector<int> need[2];
			for (int i=0;i<m;++i) need[bl[i]].push_back(ac[i]);
			int res=0;
			for (int k=0;k<2;++k){
				int now=0;
				for (int i=0;i<need[k].size()&&i<ball[k].size();++i){
					if (need[k][i]>ball[k][i]) res+=need[k][i]-ball[k][i];
					now+=ball[k][i]-need[k][i];
				}
				for (int i=need[k].size();i<ball[k].size();++i) now+=ball[k][i];
				for (int i=ball[k].size();i<need[k].size();++i) res+=need[k][i],now-=need[k][i];
				if (now<0) return;
			}
			Min(ans,res);
			return;
		}
		bl[u]=0;
		dfs(u+1);
		bl[u]=1;
		dfs(u+1);
	}
	public:
	int minRepaintings(vector <int> balloonCount, string balloonSize, vector <int> maxAccepted){
		for (int i=0;i<balloonCount.size();++i)
			ball[balloonSize[i]=='L'].push_back(balloonCount[i]);
		for (int k=0;k<2;++k) sort(ball[k].begin(),ball[k].end(),greater<int>());
		m=maxAccepted.size();
		for (int i=0;i<m;++i) ac[i]=maxAccepted[i];
		sort(ac,ac+m,greater<int>());
		ans=-1;
		dfs(0);
		return ans;
	}
};
