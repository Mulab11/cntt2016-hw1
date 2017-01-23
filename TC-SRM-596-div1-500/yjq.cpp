#include<bits/stdc++.h>
using namespace std;typedef long long LL;class BitwiseAnd{public:vector<LL>lexSmallest(vector<LL>mask,int n){vector<LL>emp,ans=mask;ans.resize(n);int m=mask.size();bool used[65];LL v;memset(used,false,sizeof(used));for(int i=0;i<m;++i){for(int k=0;k<60;++k)if(mask[i]&(1LL<<k))used[k]=true;for(int j=i+1;j<m;++j){if((mask[i]&mask[j])==0LL)return emp;for(int k=j+1;k<m;++k)if(mask[i]&mask[j]&mask[k])return emp;}}for(int i=0;i<m;++i)for(int j=i+1;j<m;++j){v=mask[i]&mask[j];mask[i]^=v,mask[j]^=v;}for(int i=1;i<=n-m;++i){for(int j=0;j<m;++j){if(!mask[j])return emp;int k=0;for(;!(mask[j]&(1LL<<k));++k);mask[j]^=1LL<<k,ans[m+i-1]|=1LL<<k;}for(int j=i+1;j<=n-m;++j){int k=0;for(;k<60;++k)if(!used[k])break;if(k==60)return emp;used[k]=true;ans[m+i-1]|=1LL<<k;ans[m+j-1]|=1LL<<k;}}sort(ans.begin(),ans.end());return ans;}} sol ; 

vector<LL> g ; 

int main() { 
		g.push_back( 14), g.push_back(20) ; 
		vector<LL> res = sol.lexSmallest(g, 3) ; 
		for (int i = 0; i < res.size(); i ++) printf("%d ", res[i]) ; 
}

