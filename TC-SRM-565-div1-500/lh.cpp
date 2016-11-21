#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class TheDivisionGame{
	private:
		static const int maxn=1000000;
		bool notp[maxn];
		int pr[maxn],top;
		void pre(int lim){
			if (lim>maxn) lim=maxn;
			for (int i=2;i<lim;++i){
				if (!notp[i]){
					pr[top++]=i;
				}
				for (int j=0;j<top;++j){
					long long k=(long long)i*pr[j];
					if (k>=lim) break;
					notp[k]=true;
					if (i%pr[j]==0) break;
				}
			}
//			for (int i=0;i<top;++i) printf("pr[%d]=%d\n",i,pr[i]);
			return;
		}
		int num[1000500],cnt[1000500],su[5000];
	public:
		long long countWinningIntervals(int L, int R){
			pre(R+1);
//			for (int i=0;i<top;++i) printf("%d\n",pr[i]);
			for (int i=L;i<=R;++i) num[i-L]=i;
			for (int i=0;i<top;++i){
//				printf("%d\n",pr[i]);
				int p=pr[i];
				for (int j=((L+pr[i]-1)/pr[i])*pr[i];j<=R;j+=pr[i]){
					int k=j-L;
					num[k]/=pr[i];
					++cnt[k];
					while(num[k]%pr[i]==0){
						++cnt[k];
						num[k]/=pr[i];
					}
				}
			}
			int sum=0;
			long long ans=0;
			su[0]=1;
			for (int i=0;i<=R-L;++i){
				if (num[i]>1) ++cnt[i];
				sum^=cnt[i];
				ans+=i+1-su[sum];
				++su[sum];
			}
			return ans;
		}
};
