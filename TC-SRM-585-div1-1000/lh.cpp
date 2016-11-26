#include<cmath>
#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const double eps=1e-8;

struct point{
	double x,y;
	point (double a=0,double b=0):x(a),y(b){};
	point operator + (const point &a)const{
		return point(x+a.x,y+a.y);
	}
	point operator - (const point &a)const{
		return point(x-a.x,y-a.y);
	}
	double operator * (const point &a)const{
		return x*a.y-y*a.x;
	}
};

struct Tr{
	long long a[60000<<2],b[60000<<2];
	int top;
	void inca(int x,int y){
		while(x<=top){
			a[x]+=y;
			x+=x&(-x);
		}
		return;
	}
	void incb(int x,int y){
		while(x<=top){
			b[x]+=y;
			x+=x&(-x);
		}
		return;
	}
	long long ask(long long *x,int t){
		long long ret=0;
		while(t){
			ret+=x[t];
			t^=t&(-t);
		}
		return ret;
	}
	void init(int n){
		top=n;
		memset(a,0,sizeof(a[0])*(n+1));
		memset(b,0,sizeof(b[0])*(n+1));
		return;
	}
	void insert(int l,int r){
		if (l>r) return;
		inca(l,1);
		incb(l,l);
		inca(r+1,-1);
		incb(r+1,-r-1);
		return;
	}
	void erase(int l,int r){
		if (l>r) return;
		inca(l,-1);
		incb(l,-l);
		inca(r+1,1);
		incb(r+1,r+1);
		return;
	}
	long long ask(int l,int r){
		if (l>r) return 0;
		return (r+1)*(ask(a,r)-ask(a,l-1))-(ask(b,r)-ask(b,l-1))+(r-l+1)*ask(a,l-1);
	}
}tree;

class EnclosingTriangle{
	static const int maxn=60000<<2;
	point edg[maxn],nod[30];
	int top,n;
	int ins[maxn],as[maxn],head[maxn],list[maxn],nxt[maxn],tot;
	
	bool check(const point &a,const point &b){
		point tmp=b-a;
		for (int i=0;i<n;++i) if (tmp*(nod[i]-a)<-eps) return false;
		return true;
	}
	
	void add(int a,int b){
		++tot;
		nxt[tot]=head[a];
		head[a]=tot;
		list[tot]=b;
		return;
	}
	
	public:
	long long getNumber(int m, vector<int> x, vector<int> y){
		long long ans=0;
		n=x.size();
		for (int i=0;i<n;++i)
			nod[i]=point(x[i],y[i]);
		for (int i=0;i<=m;++i) edg[++top]=point(i,0);
		for (int i=1;i<=m;++i) edg[++top]=point(m,i);
		for (int i=m-1;i>=0;--i) edg[++top]=point(i,m);
		for (int i=m-1;i>0;--i) edg[++top]=point(0,i);
		int fr=top,to=2;
		while(fr>2&&check(edg[fr-1],edg[1])){
			--fr;
		}
		for (int i=1;i<=top;++i){
			while(fr<=top&&!check(edg[fr],edg[i])) ++fr;
			while(to<top&&check(edg[i],edg[to+1])) ++to;
			add(to,fr);
			ins[i]=fr;
			as[i]=to;
		}
		tree.init(top);
		for (int i=1;i<=top;++i){
			ans+=tree.ask(i+1,as[i]);
			tree.insert(ins[i],top);
			for (int j=head[i];j;j=nxt[j]) tree.erase(list[j],top);
		}
		return ans;
	}
};
