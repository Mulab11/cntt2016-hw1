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

const int N=18;
int m;
ll dp[1<<N][N],vis[N],sum[1<<N];

class PolygonTraversal{
public:
	long long count(int N, vector<int> points){
		m=points.size();
		int zt=0;
		memset(vis,0,sizeof(vis));
		memset(dp,0,sizeof(dp));
		memset(sum,0,sizeof(sum));
		for(int i=0;i<m;i++) zt|=1<<--points[i],vis[points[i]]=1;
		dp[zt][points[m-1]]=1;sum[zt]=1;
		for(int i=0;i<(1<<N);i++){
			if((i&zt)!=zt) continue;
			if(i==zt) continue;
			int k=-1,m=0;
			vi a;a.clear();
			for(int j=0;j<N;j++) if(i&(1<<j)) a.pb(j),m++;
			for(int j=0;j<N;j++){
				if(i&(1<<j)) k++; else continue;
				if(vis[j]) continue;
				dp[i][j]=sum[i^(1<<j)]-dp[i^(1<<j)][a[(k+m-1)%m]]-dp[i^(1<<j)][a[(k+1)%m]];
				sum[i]+=dp[i][j];
			}
		}
		int U=(1<<N)-1;
		return sum[U]-dp[U][(points[0]+1)%N]-dp[U][(points[0]+N-1)%N];
	}
};
