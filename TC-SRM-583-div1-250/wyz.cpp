// BEGIN CUT HERE

// END CUT HERE
#line 5 "TravelOnMars.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
const int maxn=55;

class TravelOnMars{
	int n;
	int q[maxn],qh,qt;
	int mind[maxn];
	public:
	int minTimes(vector <int> range, int startCity, int endCity){
		n=range.size();
		memset(mind,-1,sizeof(mind));
		qh=qt=0;
		q[++qt]=startCity;
		mind[startCity]=0;
		while (qh<qt){
			int u=q[++qh];
			for (int i=-range[u];i<=range[u];++i){
				int v=(u+i+n)%n;
				if (mind[v]>=0) continue;
				mind[v]=mind[u]+1;
				q[++qt]=v;
			}
		}
		return mind[endCity];
	}
};
