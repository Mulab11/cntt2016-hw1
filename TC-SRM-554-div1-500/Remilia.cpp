#include <bits/stdc++.h>

using namespace std;

#define PB push_back
#define MP make_pair
#define ALL(a)  (a).begin(),(a).end()
#define FOR(i,a,b) for(int (i)=(a);(i)<(b);(i)++)

const int INF=2000000000;

/*
答案一定是先递减再递增。
贪心放就行了。
*/

struct TheBrickTowerMediumDivOne{
	vector<int> find(vector<int> h){
		vector<int> res;
		vector<bool> used(h.size(),0);
		int n=h.size(),d=INF;
		FOR(i,0,n)if(h[i]<=d)d=h[i],res.PB(i),used[i]=1;
		vector<pair<int,int> > b;
		FOR(i,0,n)if(!used[i])b.PB(MP(h[i],i));
		sort(ALL(b));
		FOR(i,0,b.size())res.PB(b[i].second);
		return res;
	}
};