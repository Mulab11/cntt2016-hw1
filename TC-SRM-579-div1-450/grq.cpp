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

const int N=55,inf=1e9;
int n,m,op[N],cl[N],dur[N],dp[1<<16][N],dis[N][N];
vi make(string s){
	int now=0;
	vi res;res.clear();
	for(int i=0;i<s.length();i++)
		if(s[i]>='0'&&s[i]<='9') now=now*10+s[i]-'0'; else res.pb(now),now=0;
	res.pb(now);
	return res;
}

class TravellingPurchasingMan{
public:
	int maxStores(int N, vector<string> is, vector<string> roads){
		m=is.size();n=N;
		for(int i=0;i<m;i++){
			vi tmp=make(is[i]);
			op[i]=tmp[0];cl[i]=tmp[1];dur[i]=tmp[2];
		}
		for(int i=0;i<n;i++)for(int j=0;j<n;j++)
			if(i==j) dis[i][j]=0; else dis[i][j]=inf;
		for(int i=0;i<roads.size();i++){
			vi tmp=make(roads[i]);
			dis[tmp[0]][tmp[1]]=dis[tmp[1]][tmp[0]]=tmp[2];
		}
		for(int k=0;k<n;k++)
			for(int i=0;i<n;i++)
				for(int j=0;j<n;j++)
					dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
		int ans=0;
		for(int i=0;i<m;i++) if(dis[n-1][i]<=cl[i]) ans=1,dp[1<<i][i]=max(dis[n-1][i],op[i])+dur[i]; else dp[1<<i][i]=inf;
		for(int i=1;i<(1<<m);i++)
			for(int j=0;j<m;j++){
				if(!(i&(1<<j))) continue;
				if(i==(1<<j))continue;
				int a=i^(1<<j);
				dp[i][j]=inf;
				for(int k=0;k<m;k++)
					if((a&(1<<k))&&dp[a][k]+dis[k][j]<=cl[j]) dp[i][j]=min(dp[i][j],max(dp[a][k]+dis[k][j],op[j])+dur[j]);
				if(dp[i][j]<inf) ans=max(ans,__builtin_popcount(i));
			}
		return ans;
	}
};

