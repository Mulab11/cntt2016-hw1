#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class XorBoard{
	static const int mod=555555555,maxn=2800;
	int C[maxn][maxn];
	long long cnt(int num,int a,int b){
		long long ret=C[num][b];
		ret*=C[(a-b)/2+num-1][num-1];
		return ret%mod;
	}
	
	public:
	int count(int H, int W, int Rt, int Ct, int S){
		long long ans=0;
		C[0][0]=1;
		for (int i=1;i<=2700;++i){
			C[i][0]=1;
			for (int j=1;j<=i;++j) C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
		}
		for (int i=(Rt&1);i<=H&&i<=Rt;i+=2){
			for (int j=(Ct&1);j<=Ct&&j<=W;j+=2){
				if (i*W+j*H-2*i*j==S){
					ans=(ans+cnt(H,Rt,i)*cnt(W,Ct,j))%mod;
				}
			}
		}
		return ans;
	}
};
