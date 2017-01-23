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

const int N=2505,mod=1e9+7;
int n,m,fa[N],vis[N],dp[2];

inline int find(int x){
	if(fa[x]!=x) fa[x]=find(fa[x]);
	return fa[x];
}
inline void merge(int x,int y){
	x=find(x);y=find(y);
	fa[x]=y;
}


class GooseInZooDivOne{
public:
	int count(vector<string> field, int dist){
		n=field.size();m=field[0].size();
		for(int i=0;i<n*m;i++) fa[i]=i;
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++){
				if(field[i][j]!='v') continue;
				for(int ai=0;ai<n;ai++)
					for(int aj=0;aj<m;aj++)
						if(field[ai][aj]=='v'&&abs(i-ai)+abs(j-aj)<=dist) merge(i*m+j,ai*m+aj);
			}
		memset(vis,0,sizeof(vis));
		for(int i=0;i<n;i++)
		for(int j=0;j<m;j++){
			if(field[i][j]=='.') continue;
			int k=i*m+j;
			vis[find(k)]++;
		}
		int ans=0;vi a;a.clear();
		for(int i=0;i<n*m;i++) if(vis[i]) ans++,a.pb(vis[i]&1);
		dp[0]=1;dp[1]=0;
		for(int i=0;i<a.size();i++){
			int x=dp[0],y=dp[1];
			if(a[i]&1) dp[0]=dp[1]=(x+y)%mod; else dp[0]=x*2%mod,dp[1]=y*2%mod;
		}
		return (dp[0]+mod-1)%mod;
	}
};

