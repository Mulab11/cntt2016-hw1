// BEGIN CUT HERE

// END CUT HERE
#line 5 "SemiPerfectPower.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
inline int gcd(int a,int b){return b?gcd(b,a%b):a;}
const int maxn2=300000000;
const int maxn3=431000;
const int maxn4=20000;
int mu[maxn3+3];
bool flag[maxn4+4];
vector<int> fac[maxn3+3],s[maxn3+3];

int pri[maxn3+3],cnt_prime;
bool is_prime[maxn3+3];
void init(){
	cnt_prime=0;
	memset(is_prime,1,sizeof(is_prime));
	mu[1]=1;
	for (int i=2;i<=maxn3;++i){
		if (is_prime[i]) mu[pri[++cnt_prime]=i]=-1;
		for (int j=1;i*pri[j]<=maxn3;++j){
			is_prime[i*pri[j]]=0;
			if (i%pri[j]==0){
				mu[i*pri[j]]=0;
				break;
			}
			mu[i*pri[j]]=-mu[i];
		}
	}
	memset(flag,1,sizeof(flag));
	for (int i=2;i*i*i<=maxn4;++i)if (is_prime[i])
		for (int j=i*i*i;j<=maxn4;j+=i*i*i)flag[j]=0;
	for (int i=1;i<=maxn4;++i){
		s[i].push_back(0);
		for (int j=i;j<=maxn3;j+=i) s[i].push_back(s[i].back()+mu[j]*mu[j]);
		for (int j=i;j<=maxn4;j+=i) fac[j].push_back(i);
	}
}

int Sqrt(ll x){
	int ret=sqrt(x);
	while (1LL*ret*ret<x) ++ret;
	while (1LL*ret*ret>x) --ret;
	return ret;
}

int sqrt3(ll x){
	int ret=pow(x,1.0/3.0);
	while (1LL*ret*ret*ret<x) ++ret;
	while (1LL*ret*ret*ret>x) --ret;
	return ret;
}

class SemiPerfectPower{
	ll solve(ll n){
		ll ret=0;
		for (int a=1;1LL*a*a*a<n;++a)if (mu[a])
			ret+=1LL*max(0,Sqrt(n/a)-a);
		for (int a=1;1LL*a*a*a*a<n;++a)if (flag[a])
			for (int k=1;k*k*k<=a;++k){
				int GCD=gcd(a,k*k),t=k*k/GCD,x=a/GCD;
				int l=a/t,r=sqrt3(n/a)/t;
				if (!mu[x]||l>=r) continue;
				for (int d:fac[x])
					ret+=1LL*mu[d]*(s[d][r/d]-s[d][l/d]);
			}
		return ret;
	}
	public:
	long long count(long long L, long long R){
		init();
		return solve(R)-solve(L-1);
	}
};
