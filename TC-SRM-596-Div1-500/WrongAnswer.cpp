#include <vector>
#include <algorithm>
using namespace std;
class BitwiseAnd{
public:
	vector<long long> lexSmallest(vector<long long> subset, int N){
		vector<long long>em;
		if(N>11)return em;
		int cnt[60]={0},belong[60];
		for(int i=0;i<subset.size();i++){
			for(int j=0;j<60;j++)if(subset[i]>>j&1)if(++cnt[j]>2)return em;else belong[j]=i;
			for(int j=i+1;j<subset.size();j++)if(!(subset[i]&subset[j]))return em;
		}
		for(int i=subset.size();i<N;i++){
			long long x=0,sel=0;
			int tot=N-i-1;
			for(int j=0;j<60;j++)if(cnt[j]<2){
				if(cnt[j]==1&&!(sel>>belong[j]&1))cnt[j]++,x|=1ll<<j,sel|=1<<belong[j];
				else if(!cnt[j]&&tot)cnt[j]++,belong[j]=i,x|=1ll<<j,tot--;
			}
			if(sel!=(1<<i)-1)return em;
			subset.push_back(x);
		}
		sort(subset.begin(),subset.end());
		return subset;
	}
};
