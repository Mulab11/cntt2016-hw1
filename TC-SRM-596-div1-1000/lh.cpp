#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class SparseFactorial{
	static const int maxn=1000000,maxm=40;
	int use[maxn];
	int ans[maxn],A[maxn],cnt[maxn],top;
	
	int power(int a,int b){
		int ret=1;
		while(b){
			if (b&1) ret*=a;
			a*=a;
			b>>=1;
		}
		return ret;
	}
	
	void make(int p,int r,int lim){
		printf("make(%d,%d,%d)\n",p,r,lim);
		int tmp=power(p,r);
		memset(A,-1,sizeof(A[0])*tmp);
		memset(cnt,0,sizeof(cnt[0])*tmp);
		for (int k=0;k<=lim&&k<p*r;++k){
			int tt=(long long)k*k%tmp;
			for (int i=(long long)k*k%p;i<tmp;i+=p){
				int x=(i-tt+tmp)%tmp;
				if (x==0) cnt[i]+=r;
				else{
					while(x%p==0){
						++cnt[i];
						x/=p;
					}
				}
				if (A[i]==-1&&cnt[i]>=r) A[i]=k;
			}
		}
		
		int now=tmp*top;
		for (int i=0;i<now;++i){
			if (A[i%tmp]==-1) use[i]=-1;
			else if (ans[i%top]==-1) use[i]=-1;
			else use[i]=max(A[i%tmp],ans[i%top]);
		}
		memcpy(ans,use,sizeof(ans[0])*now);
		top=now;
		return;
	}
	
	void pre(int D,long long lim){
		lim=sqrt(lim);
		for (int i=2;i<=D;++i) if (D%i==0){
			int cnt=1;
			D/=i;
			while(D%i==0){
				D/=i;
				++cnt;
			}
			make(i,cnt,lim);
		}
		return;
	}
	
	long long calc(long long a,int i,int b){
//		printf("%lld %d %d= %lld\n",a,i,b,(a-i)/b+1);
		
		return (a-i)/b+1;
	}
	
	public:
		long long getCount(long long lo, long long hi, long long D){
			top=1;
			pre(D,hi);
			long long ret=0;
			--lo;
			for (int i=0;i<D;++i) if (ans[i]!=-1){
				if (hi>=i){
					ret+=calc(hi,i,D);
					long long tt=min(max(lo,(long long)ans[i]*ans[i]),hi);
					if (tt>=i) ret-=calc(tt,i,D);
					
//					if (ret){
//						printf("ans=%d:",ans[i]);
//						printf("(%lld,%lld],i=%d  ret=%lld\n",tt,hi,i,ret);
//					}
				}
			}
			return ret;
		}
};
