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

double ans;
int n,m,s,dp[22][1405][2];
vector<string> a;
void solve(int *b,int cnt,int use){
	memset(dp,0,sizeof(dp));
	dp[0][0][0]=1;
	for(int i=1;i<=m;i++)
		for(int j=0;j<=s-cnt;j++)
			for(int k=0;k<2;k++)
				dp[i][j][k]=dp[i-1][j][k]+(j>=b[i]?dp[i-1][j-b[i]][k^1]:0);
	for(int j=(cnt==0);j<=s-cnt;j++)
		for(int k=0;k<2;k++)
			if((k+use)&1) ans+=dp[m][j][k]*s/(double)(cnt+j); else ans-=dp[m][j][k]*s/(double)(cnt+j);
}

class RandomPaintingOnABoard{
public:
	double expectedSteps(vector <string> prob){
		a=prob;n=a.size();m=a[0].size();
		ans=0.0;
		if(n>m){
			vector<string> b;
			for(int j=0;j<m;j++){
				b.pb("");
				for(int i=0;i<n;i++)
					b[j]=b[j]+a[i][j];
			}
			a=b;swap(n,m);
		}
		s=0;
		for(int i=0;i<n;i++) for(int j=0;j<m;j++)
			s=s+a[i][j]-'0';
		debug(s);
		for(int i=0;i<(1<<n);i++){
			int b[25]={0},cnt=0,use=0;
			for(int k=0;k<n;k++)
				if(i&(1<<k)){use++;for(int j=0;j<m;j++) cnt+=a[k][j]-'0';}
				else{for(int j=0;j<m;j++) b[j+1]+=a[k][j]-'0';}
			solve(b,cnt,use);
		}
		return ans;
	}
};
