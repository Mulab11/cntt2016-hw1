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
#define pq priority_queue
#define rf random_shuffle
#define np next_permutation
#define lb lower_bound
#define debuge puts("isok")
#define debug(x) cout<<#x<<"="<<x<<endl
#define SS second
#define FF first
using namespace std;

const int M=55,N=1050005,mod=1e9+7;
int n,L,R,S,sum[M],sol[M],res[M];
int a[M][M],c[M][M];
pii l[N],r[N];
vi g[2];

inline int inv(int x){
	int ans=1,y=mod-2;
	while(y){
		if(y&1) ans=(ll)x*ans%mod;
		x=(ll)x*x%mod;y>>=1;
	}
	return ans;
}
int gauss(){
	int ans=1,flag=0;
	for(int i=1;i<n;i++){
		int t=0;
		for(int j=i;j<n;j++) if(a[j][i]){t=j;break;}
		if(!t) return 0;
		if(t!=i){
			for(int j=i;j<n;j++) swap(a[i][j],a[t][j]);
			flag^=1;
		}
		for(int j=i+1;j<n;j++){
			if(!a[j][i]) continue;
			int t=(ll)a[j][i]*inv(a[i][i])%mod;
//			if(n<=5) printf("%d\n",t);
			for(int k=i;k<n;k++)
				a[j][k]=((a[j][k]-(ll)a[i][k]*t%mod)%mod+mod)%mod;
		}
		ans=(ll)ans*a[i][i]%mod;
	}
	if(flag) ans=mod-ans;
	return ans;
}
int build(int x,int y){
	memset(a,0,sizeof(a));
	for(int i=1;i<=x;i++){
		for(int j=1;j<=x;j++) a[i][j]=(a[i][j]+mod-1)%mod;
		for(int j=x+y+1;j<=n;j++) a[i][j]=(a[i][j]+mod-1)%mod;
		a[i][i]=(a[i][i]+n-y)%mod;
	}
	for(int i=x+1;i<=x+y;i++){
		for(int j=x+y+1;j<=n;j++)
			a[i][j]=(a[i][j]+mod-1)%mod;
		a[i][i]=(a[i][i]+n-x-y)%mod;
	}
	for(int i=x+y+1;i<=n;i++){
		for(int j=1;j<=n;j++)
			a[i][j]=(a[i][j]+mod-1)%mod;
		a[i][i]=(a[i][i]+n)%mod;
	}
	return gauss();
}

void solve(pii ans[],int &cnt,vi a){
	cnt=0;int n=a.size();
	for(int i=0;i<(1<<n);i++){
		int tmp=0,ti=0;
		for(int j=0;j<n;j++)
			if(i&(1<<j)) ti++,tmp+=a[j];
		if(tmp<=S) ans[cnt++]=mp(tmp,ti);
	}
	sort(ans,ans+cnt);
}
void meet_in_the_middle(){
	memset(sum,0,sizeof(sum));
	memset(sol,0,sizeof(sol));
	int k=R-1;
	for(int i=0;i<R;i++) sum[r[i].SS]++;
	for(int i=0;i<L;i++){
		while(k>=0&&r[k].FF+l[i].FF>S) sum[r[k].SS]--,k--;
		for(int j=0;j<21;j++) sol[j+l[i].SS]=(sum[j]+sol[j+l[i].SS])%mod;
	}
}

class SweetFruits{
public:
	int countTrees(vector <int> a,int maxs){
		n=a.size();S=maxs;
		int si=0,t=0,ans=0;
		g[0].clear();g[1].clear();
		for(int i=0;i<n;i++) if(a[i]!=-1){
			g[t].pb(a[i]);t^=1;
			si++;
		}
		solve(l,L,g[0]),solve(r,R,g[1]);
		meet_in_the_middle();
//		for(int i=0;i<=si;i++) printf("%d ",sol[i]);puts("");
		for(int i=0;i<=si;i++){
			c[i][i]=c[i][0]=1;
			for(int j=1;j<i;j++)
				c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;
		}
		for(int i=0;i<=si;i++) res[i]=build(i,si-i);
		for(int i=1;i<=si;i++)
			for(int j=0;j<i;j++)
				res[i]=(res[i]-(ll)res[j]*c[i][j]%mod+mod)%mod;
		for(int i=0;i<=si;i++) ans=(ans+(ll)sol[i]*res[i]%mod)%mod;
		return ans;
	}
};
