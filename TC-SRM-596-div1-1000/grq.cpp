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

const int N=1000005;
int m,k,u,tot,p[8],g[8],cnt[8],si[8];
vector<int> num[8],nex[8];
int c[N],a[N];

void change(int x){
	x++;
	while(x<=k) c[x]++,x+=x&(-x);
}
int get(int x){
	x++;
	int ans=0;
	while(x) ans+=c[x],x-=x&(-x);
	return ans;
}//树状数组维护满足条件模数(模divisior)个数 
void cov(int x,int y){
	for(int i=y;i<k;i+=g[x]){
		a[i]|=1<<x-1;
		if(a[i]==u) change(i);
	}
}//更新对所有模g[x]余y的数 
void ins(int x,int y){
	int k=y%p[x],last=k;
	while(~nex[x][k]){
		last=k,k=nex[x][k];
		int t=k-p[x]-y+g[x];
		while(t%p[x]==0) num[x][k]++,t/=p[x];
		if(num[x][k]>=cnt[x]) cov(x,k-p[x]),nex[x][last]=nex[x][k],k=last;
	}
}//更新(n%g[x]-y)是p[x]的倍数且为满足条件的数 
ll count(ll x,ll y){
	return (y/k-x/k)*get(k-1)-get(x%k-1)+get(y%k);
}

ll solve(ll n){
	memset(c,0,sizeof(c));
	memset(a,0,sizeof(a));
	for(int i=1;i<=tot;i++){
		num[i].clear();nex[i].clear();
		for(int j=0;j<p[i]+g[i];j++) num[i].pb(0),nex[i].pb(0);
		for(int j=0;j<p[i];j++)
			for(int k=j;;k+=p[i])
				if(k<g[i]) nex[i][k]=k+p[i]; else{nex[i][k]=-1;break;}
	}//建立模g[i]未满足条件的链 
	ll ans=0;
	for(ll i=0;i*i<n;i++){
		for(int j=1;j<=tot;j++)
			ins(j,i*i%g[j]);
		ans+=count(i*i+1,min((i+1)*(i+1),n));
	}
	return ans;
}

class SparseFactorial{
public:
	long long getCount(long long lo, long long hi, long long divisor){
		k=divisor;
		ll t=k;tot=0;
		for(int i=2;i*i<=t;i++)
			if(t%i==0){
				p[++tot]=i;cnt[tot]=0;g[tot]=1;
				while(t%i==0) t/=i,g[tot]*=i,cnt[tot]++;
			}
		if(t>1) p[++tot]=t,cnt[tot]=1,g[tot]=t;//质因数分解 
		u=(1<<tot)-1;
		ll ans=solve(hi)-solve(lo-1);
		return ans;
	}
};