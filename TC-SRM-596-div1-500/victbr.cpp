#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 70; 
class BitwiseAnd{
	public:
		vector<long long> ans;
		bool vist[N];
		int n,cnt[N],len,num[N];
		ll val[N];
		vector<long long> lexSmallest(vector<long long> subset, int N){ 
			n = subset.size();
			memset(cnt,0,sizeof(cnt));//不知道为什么要memset 
			for (int i = 0;i < n;i++){
				val[++len] = subset[i];
				for (int j = 0;j < 60;j++)
					if (subset[i]&(1LL<<j)) {
						cnt[j]++;
						num[j] = i+1;
					}
				
				for (int j = i+1;j < n;j++)
					if (subset[i] & subset[j]) ;else  return ans;//注意else不能漏了 
			}
			
			for (int i = 0;i < 60;i++)
				if (cnt[i] > 2) return ans;
				
			for (int i = n+1;i <= N;i++){
				long long u = 0;
				memset(vist,0,sizeof(vist));
				for (int j = 0;j < 60;j++)
					if (cnt[j] == 1){
						if (vist[num[j]] == 0){
							vist[num[j]] = 1;
							u += 1LL<<j;
							cnt[j]++;
						}
					}
				for (int j = 1;j < i;j++)
					if (!vist[j]) return ans;
				int tot = 0;
				for (int j = 0;j < 60;j++)
					if (cnt[j] == 0 && i+tot < N){
						cnt[j]++;
						num[j] = i;//记录这个位上的是哪个数 
						tot++;
						u += 1LL<<j;
					}
				if (i+tot < N) return ans;
				val[++len] = u;
			}
			sort(val+1,val+1+len);
			for (int i = 1;i <= len;i++) 
				ans.push_back(val[i]);
			return ans;
		}
};
