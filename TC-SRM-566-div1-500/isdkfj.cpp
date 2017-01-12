#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
const int mo=1000000007;
int f[355][355],a[355],b[355],c[355],n;
void mul(int*a,int*b){
	memset(c,0,sizeof c);
	for(int i=0;i<n;++i)
		for(int j=0;j<n;++j)
		c[(i+j)%n]=(c[(i+j)%n]+LL(a[i])*b[j])%mo;
	memcpy(a,c,sizeof c);
}

class PenguinEmperor {
public:
	int countJourneys(int numCities, long long daysPassed) {
		n=numCities; LL m=daysPassed;
		f[0][0]=1;
		for(int i=0;i<n;++i)//dp出第i天到j的方案数 
			for(int j=0;j<n;++j)
			if(f[i][j]){
				int k1=(j+i+1)%n,k2=(j-i-1+n)%n;
				f[i+1][k1]=(f[i+1][k1]+f[i][j])%mo;
				if(k1!=k2)f[i+1][k2]=(f[i+1][k2]+f[i][j])%mo;
			}
		int t1=m%n;
		for(int i=0;i<n;++i)a[i]=f[n][i],b[i]=f[t1][i];//初始化 
		for(LL k=m/n;k;k>>=1){//快速幂 
			if(k&1)mul(b,a);
			mul(a,a);
		}
		return b[0];
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
