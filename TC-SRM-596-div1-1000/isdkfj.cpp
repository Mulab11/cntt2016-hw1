#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
LL a[1000005],b[1000005];
int f=1,cnt[1000005];

void work(int p,int r){//求p^r 
	int m=1;for(int i=1;i<=r;++i)m*=p;
	memset(b,0,m<<3);
	memset(cnt,0,m<<3);
	for(int k=0;k<r*p;++k){ 
		LL t=LL(k)*k;int s=t%m;
		for(int i=t%p;i<m;i+=p){
			if(b[i])continue;
			int j=i-s;
			if(j<0)j+=m;
			if(j==0)cnt[i]=r;
			else while(j%p==0)++cnt[i],j/=p;//看有几个p 
			if(cnt[i]>=r)b[i]=t+1;//p的个数够了 
		}
	}
	for(int i=0;i<m;++i)if(!b[i])b[i]=999999999999999ll;
	for(int i=f*m-1;i>=0;--i)a[i]=max(a[i%f],b[i%m]);//合并答案 
	f*=m;
}

class SparseFactorial {
public:
	long long getCount(long long lo, long long hi, long long divisor) {
		int p=divisor;
		for(int i=2;i<=p;++i)
		if(p%i==0){
			int j=0;
			while(p%i==0)++j,p/=i;//分解质因数 
			work(i,j);
		}
		--lo;p=divisor;
		LL ret=0,j;
		for(int i=0;i<p;++i){
			j=a[i]/p*p+i;
			if(j<a[i])j+=p;//求出最小的大于等于a_i的mod p=i的数 
			if(j<=lo)ret-=(lo-j)/p+1;//减去[1,L-1]里的 
			if(j<=hi)ret+=(hi-j)/p+1;//加上[1,R]里的 
		}
		return ret;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
