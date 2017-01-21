// BEGIN CUT HERE

// END CUT HERE
#line 5 "YamanoteLine.cpp"

#include <bits/stdc++.h>
#define ll long long
using namespace std;
#define N 55
#define M 233

struct edge{
	int adj,next,x;
	ll len;
	edge(){}
	edge(int _adj,int _next,ll _len,int _x):adj(_adj),next(_next),len(_len),x(_x){}
} e[M];
int n,g[N],m;
void AddEdge(int u,int v,ll w,int x){
//	printf("%d %d %lld %d\n",u,v,w,x);
	e[++m]=edge(v,g[u],w,x);g[u]=m;
}

ll mind[N];
int kx[N],_kx;
bool exist[N],found;

void spfa(int u){
	exist[u]=1;
	for (int i=g[u];i;i=e[i].next){
		int v=e[i].adj;
		if (mind[v]<=mind[u]+e[i].len) continue;
		if (exist[v]){found=1;_kx=kx[u]-kx[v]+e[i].x;return;}
		mind[v]=mind[u]+e[i].len;
		kx[v]=kx[u]+e[i].x;
		spfa(v);
		if (found) return;
	}
	exist[u]=0;
}

int u0[M],v0[M],w0[M],x0[M],m0;
void add(int u,int v,int w,int x){
	++m0;
	u0[m0]=u;v0[m0]=v;w0[m0]=w;x0[m0]=x;
}

int check(ll _x){
	memset(g,0,sizeof(g));m=1;
	for (int i=1;i<=m0;++i)
		AddEdge(u0[i],v0[i],1LL*x0[i]*_x+w0[i],x0[i]);
	found=0;
	memset(mind,63,sizeof(mind));
	memset(exist,0,sizeof(exist));
	mind[n]=0;
	spfa(n);
	if (found&&_kx==0) return -2;
	if (found) return _kx>0?-1:1;
	return 0;
}

const ll inf=1LL<<45;

class YamanoteLine {
	public:
	long long howMany(int _n, vector <int> s1, vector <int> t1, vector <int> l1, vector <int> s2, vector <int> t2, vector <int> l2){
		n=_n;
		m0=0;
		for (int i=0;i<n;++i) add(i+1,i,-1,0);
		add(0,n,0,1);
		for (int i=0;i<s1.size();++i)
			if (s1[i]<t1[i]) add(t1[i],s1[i],-l1[i],0);
			else add(t1[i],s1[i],-l1[i],1);
		for (int i=0;i<s2.size();++i)
			if (s2[i]<t2[i]) add(s2[i],t2[i],l2[i],0);
			else add(s2[i],t2[i],l2[i],-1);
		
//		check(2);
//		return 0;
		
		ll _l=n-1,_r=inf,mid;
		while (_l+1<_r){
			mid=(_l+_r)>>1;
			int res=check(mid);
			if (res==-2) return 0;
			if (res<0) _l=mid;
			else _r=mid;
		}
		ll lb=_r;
		
		_l=n-1;_r=inf;
		while (_l+1<_r){
			mid=(_l+_r)>>1;
			int res=check(mid);
			if (res==-2) return 0;
			if (res>0) _r=mid;
			else _l=mid;
		}
		
//		printf("%d %d %d\n",check(2),check(3),check(4));
//		printf("%lld %lld\n",_r,lb);
		if (_r==inf) return -1;
		return max(_r-lb,0LL);
	}
};
