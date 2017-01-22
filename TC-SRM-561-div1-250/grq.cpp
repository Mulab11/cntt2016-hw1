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
const int inf=1<<20;
using namespace std;

vi a,b,ball;
string col;
int dp[2][1<<16];
int n,m,f[1<<16],g[1<<16],si[1<<16];
void solve(int *f,char p){
	b.clear();
	int sum=0;
	for(int i=0;i<m;i++)
		if(col[i]!=p) sum+=ball[i],b.pb(ball[i]);
	sort(b.begin(),b.end());
	reverse(b.begin(),b.end());
	for(int i=0;i<n;i++) b.pb(0);
	for(int i=0;i<(1<<n);i++){
		int k=0;f[i]=0;
		if(si[i]>sum){f[i]=inf;continue;}
		for(int j=0;j<n;j++)
			if(i&(1<<j)) f[i]+=max(0,a[j]-b[k]),k++;
	}
}

class ICPCBalloons{
public:
	int minRepaintings(vector <int> BALL, string COL, vector <int> A){
		ball=BALL;col=COL;a=A;
		sort(a.begin(),a.end());
		reverse(a.begin(),a.end());
		n=a.size();m=ball.size();
		printf("%d %d\n",n,m);
		for(int i=0;i<(1<<n);i++){
			si[i]=0;
			for(int j=0;j<n;j++)
				if(i&(1<<j)) si[i]+=a[j];
		}
//		printf("%d\n",si[7]);
		solve(f,'M');
		solve(g,'L');
//		debug(f[7]);
		int ans=inf;
		for(int i=0;i<(1<<n);i++) ans=min(ans,f[i]+g[((1<<n)-1)^i]);
		if(inf<=ans) return -1;
		return ans;
	}
};
