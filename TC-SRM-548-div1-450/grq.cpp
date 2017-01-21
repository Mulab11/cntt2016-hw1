#include<bits/stdc++.h>
#define sqr(x) (x)*(x)
#define ll long long
#define ull unsigned long long
#define ui unsigned int
#define vi vector<int>
#define pb push_back
#define ld long double
#define mp make_pair
#define pii pair<int,int>
#define pq priority_queue
#define rf random_shuffle
#define np next_permutation
#define lb lower_bound
#define debuge puts("isok")
#define debug(x) cout<<#x<<"="<<x<<endl
#define SS second
#define FF first
using namespace std;

int n,g[55];
bitset<2505> dp[2][55];

class KingdomAndDice{
public:
	double newFairness(vector <int> first, vector <int> second, int X){
		n=first.size();
		sort(first.begin(),first.end());
		sort(second.begin(),second.end());
		second.pb(++X);
		int t=0,s=n-1;
		for(int i=0;i<n;i++)
			if(first[i]){s=i-1;break;}
		for(int i=1;i<=n;i++) g[i]=second[i]-second[i-1];
		for(int i=++s;i<n;i++){
			if(!first[i]) continue;
			int tmp=lb(second.begin(),second.end(),first[i])-second.begin();
			t+=tmp;g[tmp]--;
		}//printf("%d\n",t);
		//if(s) return (double)t/(double)(n*n);
		
//		printf("%d\n",s);
		int k=0;
		memset(dp,0,sizeof(dp));
		dp[0][0][t]=1;
		for(int j=0;j<=n;j++){
			k^=1;
			memset(dp[k],0,sizeof(dp[k]));
//			if(j) printf("%d ",g[j]);
			for(int i=0;i<=s;i++){
				for(int ip=i;~ip;ip--){
					if(j&&i-ip>=max(1,g[j])) break;
//					printf("%d %d\n",i,ip);
					dp[k][i]|=dp[k^1][ip]<<((i-ip)*j);
				}
			}
//			printf("%d:",j);for(int i=0;i<=n*n;i++) if(dp[k][s][i]) printf("%d ",i);puts("");
		}
//	puts("");
		int ans=-1;
		for(int i=0;i<=n*n;i++){
			if(!dp[k][s][i]) continue;
//			printf("%d\n",i);
			if(fabs(ans-0.5*n*n)>fabs(i-0.5*n*n))
				ans=i;
		}
		return  (double)ans/(double)(n*n);
	}
};
