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

const int N=55,mod=1e9+9,inf=mod;

inline void ch(int &x,int y){x+=y;if(x>=mod) x-=mod;}
inline int s1(vi a){
	int n=a.size(),ans=1,k=0;
	sort(a.begin(),a.end());
	for(int i=1;i<n;i++){
		while(k<n&&a[k]<a[i]) k++;
		ans=(ll)ans*k%mod;
	}
	return ans;
}
int vis[N];
inline int s2(vector<pii> a){
	int d=a[0].FF+a[0].SS,n=a.size(),ans=1;
	memset(vis,0,sizeof(vis));
	for(int i=0;i<n;i++){
		if(a[i].FF+a[i].SS>d) continue;
		if(a[i].FF+a[i].SS<d) return 0;
		vi tmp(0);
		for(int j=0;j<n;j++)
			if(a[j].FF-a[i].FF>=0&&a[j].FF-a[i].FF==a[j].SS-a[i].SS) vis[j]++,tmp.pb(a[j].FF-a[i].FF);
		ans=(ll)ans*s1(tmp)%mod;
	}
	for(int j=0;j<n;j++) if(vis[j]^1) return 0;
	return ans;
}
int Y(vi a,vi b,vi c,int p){
	int n=a.size();
	vi o(0);
	vector<pii> A,B,C;
	A.pb(mp(0,a[p]));A.pb(mp(a[p],0));
	B.pb(mp(0,b[p]));B.pb(mp(b[p],0));
	C.pb(mp(0,c[p]));C.pb(mp(c[p],0));
	o.pb(0);
	for(int i=0;i<n;i++){
		if(i==p) continue;
		int da=a[i]-a[p],db=b[i]-b[p],dc=c[i]-c[p];
		if(da==db&&db==dc) o.pb(da);
		else if(da>0&&da==db) C.pb(mp(da,c[i]));
		else if(da>0&&da==dc) B.pb(mp(da,b[i]));
		else if(db>0&&db==dc) A.pb(mp(db,a[i]));
		else return 0;
	}
	return (ll)s1(o)*s2(A)%mod*s2(B)%mod*s2(C)%mod;
}
set<pii> s;
set<pii>::iterator it;
void push(int ac,int bc){
	if(ac>0&&bc>0) s.insert(mp(ac,bc));
}
int seg(vi a,vi b,vi c){
	int ans=0,n=a.size();s.clear();
	for(int i=0;i<n;i++){
		push(a[i]-c[i],b[i]-c[i]);
		push(a[i]+c[i],b[i]-c[i]);
		push(c[i]-a[i],b[i]-c[i]);
		push(a[i]-c[i],b[i]+c[i]);
		push(a[i]-c[i],c[i]-b[i]);
	}
	for(it=s.begin();it!=s.end();it++){
		vi C(0);
		vector<pii> A(0),B(0);
		int isok=1,ac=(*it).FF,bc=(*it).SS;
		A.pb(mp(ac,0));A.pb(mp(0,ac));
		B.pb(mp(bc,0));B.pb(mp(0,bc));
		C.pb(0);
		for(int i=0;i<n;i++){
			int da=a[i]-c[i],db=b[i]-c[i];
			if(da==ac&&db==bc) C.pb(c[i]);
			else if(db==bc) A.pb(mp(a[i],c[i]));
			else if(da==ac) B.pb(mp(b[i],c[i]));
			else{isok=0;break;}
		}
		if(isok) /*printf("%d %d %d %d %d\n",ac,bc,s1(C),s2(A),s2(B)),*/ch(ans,(ll)s1(C)*s2(A)%mod*s2(B)%mod);
	}
	return ans;
}

class UnknownTree{
public:
	int getCount(vector<int> distancesA, vector<int> distancesB, vector<int> distancesC){
		vi a,b,c;
		a=distancesA;b=distancesB;c=distancesC;
		int ans=0,n=a.size();
		ch(ans,seg(a,b,c));
		ch(ans,seg(b,c,a));
		ch(ans,seg(c,a,b));
		int minx=inf,id=-1;
		for(int i=0;i<n;i++) 
			if(a[i]+b[i]+c[i]<minx) minx=a[i]+b[i]+c[i],id=i;
		ch(ans,Y(a,b,c,id));
		return ans;
	}
};

