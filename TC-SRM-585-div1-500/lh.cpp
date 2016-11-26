#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class LISNumber{
	static const int maxn=1300<<1,mod=1000000007;
	long long frac[maxn],inv[maxn],sav[maxn];
	
	long long power(long long a,int b){
		long long ret=1;
		while(b){
			if (b&1) ret=ret*a%mod;
			a=a*a%mod;
			b>>=1;
		}
		return ret;
	}
	
	long long C(int a,int b){
		if (a<b) return 0;
		return frac[a]*inv[b]%mod*inv[a-b]%mod;
	}
	
	public:
		int count(vector<int> cardsnum, int K){
			frac[0]=inv[0]=1;
			for (int i=1;i<maxn;++i){
				frac[i]=frac[i-1]*i%mod;
				inv[i]=power(frac[i],mod-2);
			}
			int sum=0;
			for (auto &a:cardsnum) sum+=a;
			for (int i=0;i<=K;++i){
				sav[i]=1;
				for (auto &a:cardsnum)
				sav[i]=sav[i]*C(i,a)%mod;
			}
			for (int i=1;i<=K;++i){
				for (int j=1;j<i;++j){
					sav[i]=(sav[i]-sav[j]*C(sum+i-j,i-j)%mod +mod)%mod;
				}
			}
			return sav[K];
		}
};
