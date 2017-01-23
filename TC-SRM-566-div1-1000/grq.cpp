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

const ld pi=acos(-1);
const int mod=1e5+7,N=233;
inline void ch(int &x,int y){x+=y;if(x>=mod) x-=mod;}
struct node{ld x,y;}p[N];
ll u,zt[N][N],bel[N][N];
bitset<233> go[N][N];
bool a[N][N];
int n,vis[100],dp[N][N][4];
ld cross(ld px,ld py,ld qx,ld qy){return px*qy-py*qx;}

bool check(int x,int y,int z){
	if(x==y||y==z||x==z) return 1;
	return go[x][y][z];
}
bool check(int x,int y,int z,int w){
	return check(x,y,z)&&check(y,z,w)&&check(z,w,x)&&check(w,x,y);
}
int solve(int l,int r,int k){
	int &ans=dp[l][r][k];
	if(~ans) return ans;
	ans=0;
	if(!k){
		if(!bel[l][r]) return ans=1;
		for(int i=l;i<=r;i++)
			if(i==r||check(l,i,i+1,r)) ch(ans,(ll)solve(l,i,1)*solve(i+1,r,0)%mod);
		return ans;
	}
	if(k==1){
		if(!bel[l][r]) return 0;
		if(l+1<r){
			if(a[l][r]) ch(ans,solve(l,r,2));
			if(check(l,l+1,r)) ch(ans,solve(l+1,r,1));
		}
		return ans;
	}
	
	if(k==3&&a[l][r]&&check(l,l+1,r-1,r)) ans=solve(l+1,r-1,0);
	for(int i=l+1;i<r;i++)
		if(a[l][i]&&check(l,l+1,i-1,i)){
			int kp=k;
			if((bel[l][i]|bel[i][r])!=bel[l][r]) kp=3;
			ch(ans,(ll)solve(i,r,kp)*solve(l+1,i-1,0)%mod);
		}
	return ans;
}

class FencingPenguins{
public:
	int countWays(int np, int R, vector<int> x, vector<int> y, string color){
		n=np;int m=x.size();
		for(int i=0;i<n;i++)
			p[i]=(node){(double)R*cos(pi*2/n*i),(double)R*sin(pi*2/n*i)};
		for(int k=0;k<m;k++){
			bool a=0,b=0;
			for(int i=0;i<n;i++)
				if(cross(p[i].x-x[k],p[i].y-y[k],p[(i+1)%n].x-x[k],p[(i+1)%n].y-y[k])>0) a=1; else b=1;
			if(a&&b) return 0;
		}
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++){
				if(i==j) continue;
				zt[i][j]=0;
				memset(vis,0,sizeof(vis));
				for(int k=0;k<m;k++)
					if(cross(p[i].x-x[k],p[i].y-y[k],p[j].x-x[k],p[j].y-y[k])>0)  vis[color[k]-'A']|=1,zt[i][j]|=1ll<<k;
					else vis[color[k]-'A']|=2;
				a[i][j]=1;
				for(int k=0;k<100;k++) if(vis[k]==3) a[i][j]=0;
			}
		u=(1ll<<m)-1;
		for(int l=0;l<n;l++)
			for(int r=l+1;r<n;r++){
				ll aa=u,bb=u;
				for(int i=l;i<r;i++)
					aa&=zt[i][i+1],bb&=u^zt[i][i+1];
				aa&=zt[r][l],bb&=u^zt[r][l];
				bel[l][r]=aa|bb;
			}
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++){
				if(i==j) continue;
				for(int k=0;k<n;k++){
					if(i==k||j==k) continue;
					if(!(zt[i][j]&zt[j][k]&zt[k][i])&&(zt[i][j]|zt[j][k]|zt[k][i])==u) go[i][j][k]=1; else go[i][j][k]=0;
				}
			}
//		debug(go[0][1][3]);
		int ans=0;
		memset(dp,-1,sizeof(dp));
		for(int i=1;i<n;i++)
			if(i==n-1||check(0,i,i+1,n-1)) ch(ans,(ll)solve(0,i,1)*solve(i+1,n-1,0)%mod);
		return ans;
	}
};
