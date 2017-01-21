// BEGIN CUT HERE

// END CUT HERE
#line 5 "LittleElephantAndBoard.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
#define N 1000006
const int P=1000000007;

int fast_pow(int x,int y){
	int ret=1;
	while (y){
		if (y&1) ret=(ll)ret*x%P;
		x=(ll)x*x%P;
		y>>=1;
	}
	return ret;
}

int fact[N],inv[N],bin[N];
void prepare(int n){
	for (int i=fact[0]=1;i<=n;++i) fact[i]=(ll)fact[i-1]*i%P;
	for (int i=0;i<=n;++i) inv[i]=fast_pow(fact[i],P-2);
	for (int i=bin[0]=1;i<=n;++i) bin[i]=2*bin[i-1]%P;
//	for (int i=0;i<=n;++i)printf("%d %d %d\n",fact[i],inv[i],bin[i]);
}

class LittleElephantAndBoard{
	int calc(int b,int i,int j,int K){
		if (K<=0) return 0;
		int k=K-i-j;
		if (k<0||b-j-k<0) return 0;
		return (ll)bin[k]*fact[b-j-k+K-1]%P*inv[K-1]%P*inv[b-j-k]%P*fact[K]%P*inv[i]%P*inv[j]%P*inv[k]%P;
	}
	public:
	int getNumber(int M, int R, int G, int B){
		int a=M-R,b=M-G,c=M-B,ret=0;
		if (a<0||b<0||c<0) return 0;
		prepare(M);
		
		for (int i=max(0,c-b);i+max(0,b-c)<=M;++i){
			int j=i+b-c;
			ret=(2LL*calc(b,i,j,a)+calc(b,i,j,a-1)+calc(b,i,j,a+1)+ret)%P;
		}
		return 2*ret%P;
	}
};

//this is for test
/*
int main(){
	LittleElephantAndBoard test;
	printf("%d\n",test.getNumber(2,2,1,1));
//	test.run_test(-1);
	return 0;
}
*/
//test end
