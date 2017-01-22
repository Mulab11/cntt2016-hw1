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

const int N=100005;
bool vis[N];
int n,tot,p[N],f[N*10],rem[N*10];

class TheDivisionGame{
public:
	long long countWinningIntervals(int L, int R){
		memset(vis,0,sizeof(vis));tot=0;
		memset(f,0,sizeof(f));
		for(int i=2;i<=100000;i++){
			if(!vis[i]) p[++tot]=i;
			for(int j=1;j<=tot&&p[j]*i<=100000;j++){
				vis[i*p[j]]=1;
				if(i%p[j]==0) break;
			}
		}
		for(int i=L;i<=R;i++) rem[i-L]=i;
		for(int i=1;i<=tot;i++){
			int st=(L/p[i])*p[i];
			if(st<L) st+=p[i];
			for(int j=st;j<=R;j+=p[i])
				while(rem[j-L]%p[i]==0) rem[j-L]/=p[i],f[j-L]++;
		}
		n=R-L;
		for(int i=0;i<=n;i++) if(rem[i]>1) f[i]++;
		for(int i=1;i<=n;i++) f[i]^=f[i-1];
		f[n+1]=0;
		sort(f,f+n+2);
		ll ans=(ll)(n+2)*(n+1)/2;
		int last=-1,now=0;
		for(int i=0;i<=n+1;i++)
			if(last!=f[i]) last=f[i],now=1; else ans-=now,now++;
		return ans;
	}
};
