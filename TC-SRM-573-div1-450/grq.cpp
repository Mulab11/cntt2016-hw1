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

const int N=55;
const ll inf=1ll<<60,lim=1ll<<50;
vi a,b;
int n;
ll dp[N][N];
bool vis[N];
queue<int> q;

inline int calc(int x,int p){return abs(a[x]-b[p]);}

class SkiResorts{
public:
	long long minCost(vector<string> road, vector<int> altitude){
		a=b=altitude;n=a.size();
		sort(b.begin(),b.end());
		reverse(b.begin(),b.end());
		ll ans=inf;
		for(int i=0;i<n;i++){
			if(i) for(int j=0;j<n;j++) dp[i][j]=dp[i-1][j]-calc(j,i-1)+calc(j,i);
			else{
				dp[i][0]=calc(0,0);
				for(int j=1;j<n;j++) dp[i][j]=inf;
			}
			for(int j=0;j<n;j++) q.push(j),vis[j]=1;
			while(!q.empty()){
				int x=q.front();q.pop();
				vis[x]=0;
				for(int j=0;j<n;j++){
					if(road[x][j]!='Y') continue;
					if(dp[i][j]>dp[i][x]+calc(j,i)){
						dp[i][j]=dp[i][x]+calc(j,i);
						if(!vis[j]) q.push(j),vis[j]=1;
					}
				}
			}
//			printf("%d\n",dp[i][2]);
			ans=min(ans,dp[i][n-1]);
		}
		
		return ans<lim?ans:-1;
	}
};
