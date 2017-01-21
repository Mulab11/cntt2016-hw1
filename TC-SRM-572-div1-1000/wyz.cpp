// BEGIN CUT HERE

// END CUT HERE
#line 5 "NextAndPrev.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
void Min(int &x,int y){if (x<0||y<x) x=y;}

class NextAndPrev{
	pair<int,int> p[26];
	int _to[26];
	bool _exist[26];
	int n;
	public:
	int getMinimum(int nextCost, int prevCost, string start, string goal){
		if (start==goal) return 0;
		memset(_exist,0,sizeof(_exist));
		int not_exist=26;
		for (int i=0;i<goal.size();_exist[goal[i++]-'a']=1)
			if (!_exist[goal[i]-'a']) --not_exist;
		if (!not_exist) return -1;
		memset(_to,-1,sizeof(_to));
		for (int i=0;i<start.size();++i)
			if (_to[start[i]-'a']<0) _to[start[i]-'a']=goal[i]-'a';
			else if (_to[start[i]-'a']!=goal[i]-'a') return -1;
		n=0;
		for (int i=0;i<26;++i)if (_to[i]>=0)
			p[n++]=make_pair(i,_to[i]);//,printf("%d %d\n",i,_to[i]);
		int ret=-1;
		for (int i0=0;i0<n;++i0,p[0].first+=26){
			sort(p,p+n);
//			for (int i=0;i<n-1;++i) swap(p[i],p[i+1]);
			bool valid=1;
			for (int i=0;valid&&i<n-1;++i)
				if (p[i].second>p[i+1].second) valid=0;
			if (!valid) continue;
			for (int k=-1;k<=2;++k){
				for (int i=0;i<n;++i) p[i].second+=k*26;
				int res=0,mn=p[0].second,mx=p[0].second;
				for (int i=0;i<n;++i){
					mn=min(mn,p[i].first);
					mx=max(mx,p[i].first);
					if (i==n-1||p[i].second!=p[i+1].second){
						res+=nextCost*(p[i].second-mn)+prevCost*(mx-p[i].second);
						mn=mx=p[i+1].second;
					}
				}
				Min(ret,res);
				for (int i=0;i<n;++i) p[i].second-=k*26;
			}
		}
		return ret;
	}
};
