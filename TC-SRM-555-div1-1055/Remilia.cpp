// by ξ
// program sky  :)

#include <vector>
#include <stdio.h>
#include <algorithm>

#define Rin register int
#define oo (c=getchar())
#define For(i,l,r) for(int _r=r,i=l;i<=_r;++i)
#define rep(i,l,r) for(int _r=r,i=l;i<_r;++i)
#define dto(i,r,l) for(int _l=l,i=r;i>=_l;--i)
#define ALL(V) V.begin(),V.end()
#define pb push_back
#define mk make_pair
#define x first
#define y second

using namespace std;

typedef double db;
typedef long long LL;
typedef pair<int ,int> PII;
typedef pair<db ,db> cpx;
typedef vector<int> VI;
typedef vector<PII> VII;

int n,a[55],g[55];
LL Ans,G,se[55];
string s;

bool flag;

inline LL gao(int p){
	LL res=0,cur=0,tmp=G;//tmp是当前状态，cur是当前修改过的位置集合
	for(auto c:s){
		if(c=='1')tmp|=1ll<<p,cur|=1ll<<p;
		else if(c=='0'){
			if(tmp>>p&1)tmp-=1ll<<p;
			cur|=1ll<<p;
		}else if(c=='<')--p;else++p;
		if(p<1 || p>n)return -1;
		if(tmp==G)res|=cur;
	}
	flag=1;
	return res;
}

void dfs(int s,LL cur,int con){
	if(s>*g)return;
	LL tmp=cur&se[g[s]];
	if(tmp){
		Ans+=con*((1ll<<__builtin_popcountll(tmp))-1);//方案乘以容斥系数
		dfs(s+1,tmp,-con);
	}
	dfs(s+1,cur,con);
}

LL Main(){
	For(i,1,n)if(a[i])G|=1ll<<i;//全集
	For(i,1,n){
		se[i]=gao(i);//可行集合
		if(se[i]>0)se[i]>>=1;
	}
	if(!flag)return 0;
	For(i,1,n)if(se[i]>0)g[++*g]=i;
	dfs(1,(1ll<<n)-1,1);//爆搜容斥
	return Ans+1;
}

struct MapGuessing{
	long long countPatterns(string goal, vector <string> code){
		n=goal.size();
		For(i,1,n)a[i]=goal[i-1]-48;
		for(auto ss:code)s+=ss;
		return Main();
	}
};