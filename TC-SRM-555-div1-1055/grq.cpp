#include<bits/stdc++.h>
#define sqr(x) (x)*(x)
#define ll long long
#define ull unsigned long long
#define ui unsigned int
#define vi vector<int>
#define pb push_back
#define ld long double
#define mp make_pair
#define pii pair<int,int>
#define debuge puts("isok")
#define debug(x) cout<<#x<<"="<<x<<endl
#define SS second
#define FF first
using namespace std;


string s;
ll u,a[44],b[44];
int n,m,c[1<<18];
bool vis[40][1<<18];
ll get(int p,string c){
	string now="";ll zt=0,right=0,ans=0;
	for(int i=0;i<c.size();i++){
		if(c[i]=='<') p--; else if(c[i]=='>') p++;
		else{
			zt|=1ll<<p;
			if(s[p]==c[i]) right|=1ll<<p; else right&=u^(1ll<<p);
		}
		if(p<0||p>=n) return -1;
		if(right==zt) ans=right;
	}
	return ans;
}
int size(ll x){
	int ans=0;
	while(x) ans++,x-=x&-x;
	return ans;
}
ll solve1(){
	ll ans=0;
	for(int i=1;i<(1<<m);i++){
		ll t=u,si=0;
		for(int j=0;j<m;j++) if(i&(1<<j)) si++,t&=a[b[j]];
		if(si&1) ans+=1ll<<size(t); else ans-=1ll<<size(t);
	}
	return ans;
}
inline int get(ll x){
	if(x>(1ll<<17)) return c[x>>18]+18;
	return c[x];
}
ll solve2(){
	memset(vis,0,sizeof(vis));
	for(int i=0;i<18;i++) c[1<<i]=i;
	for(int i=0;i<n;i++){
		if(a[i]==-1) continue;
		ll u=a[i];
		for(ll x=a[i];x;x=(x-1)&u){
			int k=get(x&(-x));
			vis[k][x>>k]=1;
		}
	}
	ll ans=0;
	for(int i=0;i<n;i++)
		for(int j=0;j<(1<<n-m+1);j++)
			ans+=vis[i][j];
	return ans+1;
}

class MapGuessing{
public:
	long long countPatterns(string goal, vector <string> code){
		s=goal;n=s.length();
		u=(1ll<<n)-1;m=0;
		string Code="";
		for(int i=0;i<code.size();i++) Code=Code+code[i];
		for(int i=0;i<n;i++) a[i]=get(i,Code);
		for(int i=0;i<n;i++)
			if(a[i]!=-1) b[m++]=i;
		if(m<=20) return solve1();
		return solve2();
	}
};
