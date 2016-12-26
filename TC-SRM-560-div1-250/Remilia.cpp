#include <bits/stdc++.h>

using namespace std;

int tot[55];

struct TomekPhone{
	int minKeystrokes(vector <int> a, vector <int> b){
		int ans=0,sum=0;
		sort(a.begin(),a.end());
		int n=a.size(),m=b.size();
		for(int i=0;i<m;++i){
			for(int j=1;j<=b[i];++j)++tot[j];
			sum+=b[i];
		}
		// 边界
		if(sum<n) return -1;
		// 贪心大的放前面
		for(int i=n-1;~i;--i)
		for(int j=1;;++j)
		if(tot[j]){
			--tot[j],ans+=j*a[i];
			break;
		}
		return ans;
	}
};