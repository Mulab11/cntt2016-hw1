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
#define debuge puts("isok")
#define debug(x) cout<<#x<<"="<<x<<endl
#define SS second
#define FF first
using namespace std;

int vis[105];

class BitwiseAnd{
public:
	vector<ll> a,ans,empty;
	int n;
	vector<long long> lexSmallest(vector<long long> subset, int N){
		a=subset;n=a.size();
		memset(vis,0,sizeof(vis));
		sort(a.begin(),a.end());
		ans=a;empty.clear();
		
		if(N>=12) return empty;
		
		for(int i=0;i<n;i++)
			for(int j=i+1;j<n;j++) if(!(a[i]&a[j])) return empty;
		for(int i=0;i<n;i++) if(a[i]>=(1ll<<60)) return empty;
		for(int i=0;i<n;i++)
			for(int j=0;j<60;j++)
				if(a[i]&(1ll<<j)) vis[j]++;
		for(int i=0;i<60;i++) if(vis[i]>2) return empty;//判断原来非法的情况 
		for(int i=n;i<N;i++){
			ll t=0;bool isok=1;
			for(int j=0;j<n;j++){
				bool find=0;
				for(int k=0;k<60;k++)
					if((ans[j]&(1ll<<k))&&vis[k]<2){find=1;t|=1ll<<k;vis[k]++;break;}
				isok&=find;
			}
			if(!isok) return empty;
			ans.pb(t);
		}//处理新加和原来的要求
		if(N-n>1){
			int x=n,y=n+1;
			for(int i=0;i<N;i++) printf("%lld ",ans[i]);puts("");
			for(int i=0;i<60;i++){
				if(vis[i]||y>=N) continue;
				ans[x]|=1ll<<i;ans[y]|=1ll<<i;
				y++;if(y>=N) x++,y=x+1;
			}
			if(y<N) return empty;
		}//处理新加之间的要求 
		sort(ans.begin(),ans.end());
		return ans;
	}
};
