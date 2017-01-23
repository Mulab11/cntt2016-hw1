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

const int N=55,mod=1e9+7;
int n,k,dp[2][40][20],a[N][N],d[N][N];
bool vis[N][N],u[N];

void ch(int &x,int y){x+=y;if(x>=mod) x-=mod;}
queue<int>q;

class EqualSums{
public:
	int count(vector<string> board){
		memset(vis,0,sizeof(vis));
		memset(d,0,sizeof(d));
		memset(u,0,sizeof(u));
		n=board.size();
		for(int i=0;i<n;i++) for(int j=0;j<n;j++)
			if(board[i][j]=='-') a[i][j]=-1; else a[i][j]=board[i][j]-'0';
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)	
				for(int k=0;k<n;k++)
					if(a[j][i]!=-1&&a[k][i]!=-1){
						int t=a[j][i]-a[k][i];
						if(!vis[j][k]) vis[j][k]=1,d[j][k]=t; else if(d[j][k]!=t) return 0;
					}
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++) if(a[j][i]!=-1) q.push(j);
			while(!q.empty()){
				int j=q.front();q.pop();
				for(int k=0;k<n;k++){
					if(a[k][i]!=-1||!vis[k][j]) continue;
					if(d[k][j]+a[j][i]<0) return 0;
					a[k][i]=d[k][j]+a[j][i];
					q.push(k);
				}
			}
		}
		for(int i=0;i<n;i++){
			int mx=-1,mn=-1;
			for(int j=0;j<n;j++){
				if(a[i][j]==-1) continue;
				if(mn==-1||a[i][mn]>a[i][j]) mn=j;
				mx=max(mx,a[i][j]);
			}
			for(int j=0;j<n;j++) if(a[i][j]!=-1&&mn!=j) u[j]=1;
		}
		k=0;memset(dp,0,sizeof(dp));
		dp[k][0][18]=1;
		for(int i=0;i<n;i++){
			if(u[i]) continue;
			int mn=-1;
			for(int j=1;j<n;j++)
				if(a[j][i]!=-1&&(mn==-1||mn>a[j][i])) mn=a[j][i];
			k^=1;
			memset(dp[k],0,sizeof(dp[k]));
			for(int aa=-18;aa<=18;aa++)
				for(int b=0;b<=18;b++){
					if(!dp[k^1][aa+18][b]) continue;
					for(int c=max(0,aa);c<=(mn!=-1?b+mn:18)&&c<=18;c++){
						if(a[0][i]!=-1&&c!=a[0][i]) continue;
						ch(dp[k][max(c-(mn!=-1?mn:18),aa)+18][min(b,c)],dp[k^1][aa+18][b]);
					}
				}
		}
		int ans=0;
		for(int a=0;a<=36;a++) for(int b=0;b<=18;b++) ch(ans,dp[k][a][b]);
		return ans;
	}
};
