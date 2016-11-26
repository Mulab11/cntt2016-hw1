#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class TrafficCongestion{
	static const int mod=1000000007;
	long long power(long long a,int b){
		long long ret=1;
		while(b){
			if (b&1) ret=ret*a%mod;
			a=a*a%mod;
			b>>=1;
		}
		return ret;
	}
	public:
		int theMinCars(int H){
			int ans=(H&1)?0:1,tmp=power(2,H-1);
			long long mul=power(4,mod-2);
			for (int i=H-1;i>=0;i-=2,tmp=tmp*mul%mod){
				ans=(ans+tmp)%mod;
			}
			return ans;
		}
};
