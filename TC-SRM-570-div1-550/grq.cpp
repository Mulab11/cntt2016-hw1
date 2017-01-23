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
struct node{
	int to,next;
}p[N<<1];
int n,head[N],tot,si[N];
ll dp[N][N<<2][2],tmp[N<<2][2];
bool vis[N];

void add(int x,int y){
	p[++tot]=(node){y,head[x]};head[x]=tot;
	p[++tot]=(node){x,head[y]};head[y]=tot;
}
void dfs(int x){
	vis[x]=1;si[x]=1;
	dp[x][101][0]=dp[x][100][1]=1;
	for(int i=head[x];i;i=p[i].next){
		int y=p[i].to;
		if(vis[y]) continue;
		dfs(y);
		memset(tmp,0,sizeof(tmp));
		for(int a=-si[x]*2;a<=si[x]*2;a++)
			for(int k=0;k<2;k++){
				if(!dp[x][a+100][k]) continue;
				for(int ap=-si[y]*2;ap<=si[y]*2;ap++)
					for(int kp=0;kp<2;kp++)
						tmp[a+ap-(!k&&!kp)*2+100][k]+=dp[x][a+100][k]*dp[y][ap+100][kp];
			}
		memcpy(dp[x],tmp,sizeof(tmp));
		si[x]+=si[y];
	}
}

class CentaurCompany{
public:
	double getvalue(vector<int> A, vector<int> B){
		n=A.size()+1;
		memset(head,0,sizeof(head));tot=0;
		for(int i=0;i<A.size();i++) add(A[i],B[i]);
		memset(dp,0,sizeof(dp));
		memset(vis,0,sizeof(vis));
		dfs(1);
		ll ans=0;
		for(int a=2;a<=72;a++)
				for(int k=0;k<2;k++)
					ans+=dp[1][a+100][k]*(a-2);
//		debug(ans);
		double res=ans;
		for(int i=1;i<n;i++) res=res/2.0;
		return res;
	}
};

