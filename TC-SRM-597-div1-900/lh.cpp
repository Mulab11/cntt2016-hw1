#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class LittleElephantAndBoard{
	static const int mod=1000000007,maxn=2001000;
	long long frac[maxn],inv[maxn];
	
	inline long long power(long long a,int b){
		long long ret=1;
		while(b){
			if (b&1) ret=ret*a%mod;
			b>>=1;
			a=a*a%mod;
		}
		return ret;
	}
	
	inline long long P(int a,int b,int c){
		return frac[a+b+c]*inv[a]%mod*inv[b]%mod*inv[c]%mod;
	}
	
	inline long long calc(int a,int b){
		if (b<0) return 0;
		return frac[a+b-1]*inv[a-1]%mod*inv[b]%mod;
	}
	
	inline long long solve(int m,int b,int c){
		if (b>c) swap(b,c);
		long long ret=0;
		//printf("solve(%d,%d,%d)\n",m,b,c);
		long long tmp=((m+c+b)&1)?2:1;
		for (int i=(m+c+b)&1;i<=m;i+=2,tmp=tmp*4%mod){
			int x=(m+c-i-b)/2,y=(m+b-i-c)/2;
			if (x<0||y<0) continue;
			//printf("x=%d,y=%d,i=%d\n",x,y,i);
			(ret+=P(x,y,i)*calc(m,b-y-i)%mod*tmp)%=mod;
			//printf("ret=%lld\n",ret);
		}
		//printf("return %lld\n",ret);
		return ret;
	}
	
	public:
	
	inline int getNumber(int M, int R, int G, int B){
		int a,b,c;
		if (R>M||G>M||B>M) return 0;
		frac[0]=inv[0]=1;
		for (int i=1;i<=M*2;++i){
			frac[i]=frac[i-1]*i%mod;
			inv[i]=power(frac[i],mod-2);
		}
		a=M-R;
		b=M-G;
		c=M-B;
		return (solve(a+1,b,c)+solve(a-1,b,c)+solve(a,b,c)*2)%mod*2%mod;
	}
};