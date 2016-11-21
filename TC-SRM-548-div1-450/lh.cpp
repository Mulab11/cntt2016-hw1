#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class KingdomAndDice{
	private:
		static const int maxn=55, maxm=2510;
		int dp[maxm],g[maxm];
		bool tag[maxn<<1];
		int use[maxn<<1], top;
		int que[maxm],he,ta;
		void solve(int num,int w){
			for (int i=0;i<w;++i){
				he=ta=0;
				for (int j=i;j<maxm;j+=w){
					while(ta>he&&(j-que[he])/w>num) ++he;
					g[j]=dp[j]-j/w;
					if (ta>he&&(dp[j]>j/w+g[que[he]])) dp[j]=j/w+g[que[he]];
					while(ta>he&&g[j]<=g[que[ta-1]]) --ta;
					que[ta++]=j;
				}
			}
			return;
		}

	public:
		double newFairness(vector <int> firstDie, vector <int> secondDie, int X){
			int n = firstDie.size();
			for (int i=0;i<n;++i) use[++top]=firstDie[i];
			for (int i=0;i<n;++i) use[++top]=secondDie[i];
			sort(use+1,use+1+top);
			use[++top]=X+1;
			for (auto &i:secondDie)
				tag[lower_bound(use+1,use+1+top,i)-use]=true;
			int cnt=0;
			dp[0]=0;
			for (int i=1;i<maxm;++i) dp[i]=10000000;
			for (int i=1;i<top;++i){
				int nn=use[i+1]-use[i]-1;
				if (tag[i]) ++cnt;
				if (nn>0&&cnt>0){
//					printf("%d__,get(%d,%d)\n",use[i],nn,cnt);
					solve(nn,cnt);
				}
			}
			int tt=0;
			for (auto i :firstDie)
			for (auto j :secondDie) if (i>j) ++tt;
			int rr=0;
			for (auto i:firstDie) if (i==0) ++rr;
			double ans=1.0*tt/n/n;
//			printf("tt=%d\n",tt);
			for (int i=0;i<maxm;++i) if (dp[i]<=rr){
//				printf("i=%d\n",i);
				double tmp=(tt+i)*1.0/n/n;
				if (abs(ans-0.5)>abs(tmp-0.5)) ans=tmp;
			}
			return ans;
		}
};
