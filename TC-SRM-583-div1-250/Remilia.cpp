#include <bits/stdc++.h>

#define rep(x,a,b) for (int x=a;x<=(int)b;x++)
#define drp(x,a,b) for (int x=a;x>=(int)b;x--)
#define cross(x,a) for (int x=hd[a];~x;x=nx[x])
#define ll long long
#define inf (1<<29)
#define PII pair<int,int>
#define PDD pair<double,double>
#define mk(a,b) make_pair(a,b)
#define fs first
#define sc second
#define pb push_back
#define VI vector<int>
using namespace std;
const int maxn=55;
int que[maxn],head,tail;
int dist[maxn],n;
int pre(int x){return !x?n-1:x-1;}
int suf(int x){return (x+1)%n;}

/*
按照题意建图模拟即可。
*/

class TravelOnMars{
public:
	int minTimes(vector<int>rng,int st,int en){
		n=rng.size();
		memset(dist,-1,sizeof dist);
		dist[st]=0;
		head=1,tail=0;que[++tail]=st;
		while (head<=tail){
			int u=que[head++],l=u,r=u;
			rep(i,1,rng[u]){
				l=pre(l),r=suf(r);
				if (dist[l]==-1) dist[l]=dist[u]+1,que[++tail]=l;
				if (dist[r]==-1) dist[r]=dist[u]+1,que[++tail]=r;
			}
		}
		return dist[en];
	}
};
